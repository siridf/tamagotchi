#include <iostream>
#include "sdlJeu.h"
using namespace std ;


const int TAILLE_SPRITE = 32;
//pour le memory
const int DIMX_CARTE = 200;
const int DIMY_CARTE = 270;


//CLASSE IMAGE

Image::Image () : surface(nullptr), texture(nullptr), aChange(false) {}

Image::~Image()
{
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    surface = nullptr;
    texture = nullptr;
    aChange = false;
}

void Image::chargerDepuisFichier (const char* nomFichier, SDL_Renderer * renderer)
{
    surface = IMG_Load(nomFichier);
    if (surface == nullptr) {
        string nfn = string("../") + nomFichier;
        cout << "Error: cannot load "<< nomFichier <<". Trying "<<nfn<<endl;
        surface = IMG_Load(nfn.c_str());
        if (surface == nullptr) {
            nfn = string("../") + nfn;
            surface = IMG_Load(nfn.c_str());
        }
    }
    if (surface == nullptr) {
        cout<<"Error: cannot load "<< nomFichier <<endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;

    texture = SDL_CreateTextureFromSurface(renderer,surfaceCorrectPixelFormat);
    if (texture == NULL) {
        cout << "Error: problem to create the texture of "<< nomFichier<< endl;
        SDL_Quit();
        exit(1);
    }
}


void Image::chargerDepuisSurface(SDL_Renderer * renderer)
{
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    if (texture == nullptr) {
        cout << "Error: problem to create the texture from surface " << endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::dessiner(SDL_Renderer * renderer, int x, int y, int w, int h)  {


    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?surface->w:w;
    r.h = (h<0)?surface->h:h;

    if (aChange) {
        ok = SDL_UpdateTexture(texture,nullptr,surface->pixels,surface->pitch);
        assert(ok == 0);
        aChange = false;
    }

    ok = SDL_RenderCopy(renderer,texture,nullptr,&r);
    assert(ok == 0);


    ok = SDL_RenderCopy(renderer,texture,nullptr,&r);
    assert(ok == 0);

    posX=x;
    posY=y;

}

void Image::dessinerArrierePlan(SDL_Renderer * renderer, int x, int y, int w, int h)  {


    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = 30*TAILLE_SPRITE;
    r.h =30*TAILLE_SPRITE;

    if (aChange) {
        ok = SDL_UpdateTexture(texture,nullptr,surface->pixels,surface->pitch);
        assert(ok == 0);
        aChange = false;
    }

    ok = SDL_RenderCopy(renderer,texture,nullptr,&r);
    assert(ok == 0);



    ok = SDL_RenderCopy(renderer,texture,nullptr,&r);
    assert(ok == 0);

    posX=x;
    posY=y;

}

SDL_Texture * Image::getTexture() const {return texture;}

void Image::setSurface(SDL_Surface * surf) {surface = surf;}


//CLASSE Timer


Timer::Timer()
{
    //Initialisation des variables
    debutTimer = 0;
    pauseTics = 0;
    enPause = false;
    started = false;
}

void Timer::demarrerTimer()
{
    //On demarre le timer
    started = true;

    //On enlève la pause du timer
    enPause = false;

    //On récupére le temps courant
    debutTimer = SDL_GetTicks();
}

void Timer::arreterTimer()
{
    //On stoppe le timer
    started = false;

    //On enlève la pause
    enPause = false;
}

int Timer::getTics()
{
    //Si le timer est en marche
    if( started == true )
    {
        //Si le timer est en pause
        if( enPause == true )
        {
            //On retourne le nombre de ticks quand le timer a été mis en pause
            return pauseTics;
        }
        else
        {
            //On retourne le temps courant moins le temps quand il a démarré
            return SDL_GetTicks() - debutTimer;
        }
    }

    //Si le timer n'est pas en marche
    return 0;
}

void Timer::pause()
{
    //Si le timer est en marche et pas encore en pause
    if( ( started == true ) && ( enPause == false ) )
    {
        //On met en pause le timer
        enPause = true;

        //On calcul le pausedTicks
        pauseTics = SDL_GetTicks() - debutTimer;
    }
}

void Timer::dePause()
{
    //Si le timer est en pause
    if( enPause == true )
    {
        //on enlève la pause du timer
        enPause = false;

        //On remet à zero le debutTimer
        debutTimer = SDL_GetTicks() - pauseTics;

        //Remise à zero du pauseTics
        pauseTics = 0;
    }
}

bool Timer::estEnMarche()
{
    return started;
}

bool Timer::estEnPause()
{
    return enPause;
}


//CLASSE JeuModeGraphique


JeuModeGraphique::JeuModeGraphique() // constructeur : toutes les initialisations
{
    boolBleu=false;
    boolRose=false;
    boolVert=false;
    boolJaune=false;

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }



    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image n'a pas pu être initialisé : " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

   if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        cout << "SDL_mixer n'a pas pu être initialisé :" << Mix_GetError() << endl;
        cout << "Pas de son " << endl;
        avecSon = false;
    }
    else avecSon = true;  

    int dimx, dimy; // dimensions de la fenêtre

    dimx = 30 ;
    dimy = 30 ;
    dimx = dimx * TAILLE_SPRITE;
    dimy = dimy * TAILLE_SPRITE ;

    // Creation de la fenetre
    fenetre = SDL_CreateWindow("Capri", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (fenetre == nullptr) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_ACCELERATED);

    // INITILISATION DES IMAGES

    nbImages = 4  ;
    nbImagesCartes = 9 ;


    // Initialisation des tableaux d'images
    tabImagesRose = new Image[nbImages] ;
    tabImagesBleu= new Image[nbImages] ;
    tabImagesVert = new Image[nbImages] ;
    tabImagesJaune = new Image[nbImages] ;
    tabImagesMemory = new Image[nbImagesCartes] ;

    // On remplit chaque tableau d'images de Capri avec les images des fichiers

    // Capri rose
    tabImagesRose[0].chargerDepuisFichier("./data/rose/rose1.png",renderer);
    tabImagesRose[1].chargerDepuisFichier("./data/rose/rose2.png",renderer);
    tabImagesRose[2].chargerDepuisFichier("./data/rose/rose3.png",renderer);
    tabImagesRose[3].chargerDepuisFichier("./data/rose/rose4.png",renderer);

    // Capri vert
    tabImagesVert[0].chargerDepuisFichier("./data/vert/vert1.png",renderer);
    tabImagesVert[1].chargerDepuisFichier("./data/vert/vert2.png",renderer);
    tabImagesVert[2].chargerDepuisFichier("./data/vert/vert3.png",renderer);
    tabImagesVert[3].chargerDepuisFichier("./data/vert/vert4.png",renderer);

    // Capri bleu
    tabImagesBleu[0].chargerDepuisFichier("./data/bleu/bleu1.png",renderer);
    tabImagesBleu[1].chargerDepuisFichier("./data/bleu/bleu2.png",renderer);
    tabImagesBleu[2].chargerDepuisFichier("./data/bleu/bleu3.png",renderer);
    tabImagesBleu[3].chargerDepuisFichier("./data/bleu/bleu4.png",renderer);

    // Capri jaune
    tabImagesJaune[0].chargerDepuisFichier("./data/jaune/jaune1.png",renderer);
    tabImagesJaune[1].chargerDepuisFichier("./data/jaune/jaune2.png",renderer);
    tabImagesJaune[2].chargerDepuisFichier("./data/jaune/jaune3.png",renderer);
    tabImagesJaune[3].chargerDepuisFichier("./data/jaune/jaune4.png",renderer);

    /* Memory (les cartes d'une même paire ont la même image mais pas les mêmes posX, posY donc
    on stocke une image par case, paires comprises */
    tabImagesMemory[0].chargerDepuisFichier("./data/memory/paire1.png",renderer) ;
    tabImagesMemory[1].chargerDepuisFichier("./data/memory/paire1.png",renderer) ;
    tabImagesMemory[2].chargerDepuisFichier("./data/memory/paire2.png",renderer) ;
    tabImagesMemory[3].chargerDepuisFichier("./data/memory/paire2.png",renderer) ;
    tabImagesMemory[4].chargerDepuisFichier("./data/memory/paire3.png",renderer) ;
    tabImagesMemory[5].chargerDepuisFichier("./data/memory/paire3.png",renderer) ;
    tabImagesMemory[6].chargerDepuisFichier("./data/memory/paire4.png",renderer) ;
    tabImagesMemory[7].chargerDepuisFichier("./data/memory/paire4.png",renderer) ;
    tabImagesMemory[8].chargerDepuisFichier("./data/memory/dosCarte.png",renderer) ;

    //chargement des images des oeufs
    oeufBleu.chargerDepuisFichier("./data/bleu/oeufBleu.png",renderer);
    oeufRose.chargerDepuisFichier("./data/rose/oeufRose.png",renderer);
    oeufJaune.chargerDepuisFichier("./data/jaune/oeufJaune.png",renderer);
    oeufVert.chargerDepuisFichier("./data/vert/oeufVert.png",renderer);

     //Boutons + aliment
    boutons = new Image[3] ;
    boutons[0].chargerDepuisFichier("./data/bouton/boutonDormir.png",renderer);
    boutons[1].chargerDepuisFichier("./data/bouton/boutonJouer.png",renderer);
    boutons[2].chargerDepuisFichier("./data/bouton/boutonNourrir.png",renderer);

    boutons[0].dimX=110;  boutons[1].dimX=110;   boutons[2].dimX=110;
    boutons[0].dimY=110;  boutons[1].dimY=110;   boutons[2].dimY=110;

    boutons[0].posX=250;  boutons[1].posX=450;   boutons[2].posX=650;
    boutons[0].posY=800;  boutons[1].posY=800;   boutons[2].posY=800;

    SDL_RenderPresent(renderer);


    // SON 
    if (avecSon)
    {
        son = Mix_LoadWAV("data/son.wav");
        if (son == nullptr)
            son = Mix_LoadWAV("../data/son.wav");
        if (son == nullptr) {
                cout << "son.wav n'a pas pu être chargé, erreur :  " << Mix_GetError() << endl;
                SDL_Quit();
                exit(1);
        }
    }
    

}


JeuModeGraphique::~JeuModeGraphique()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    delete [] tabImagesBleu ;
    delete [] tabImagesRose ;
    delete [] tabImagesVert ;
    delete [] tabImagesJaune ;
    delete [] tabImagesMemory ;
    delete [] boutons ;



}

bool JeuModeGraphique::verifClicImage(const Image &im)
{
    int xSouris, ySouris;
    int quit=0;
    bool clic = false ;


    SDL_Event events ;
    while(!quit )
    {
        SDL_PollEvent(&events); // Pour attendre que l'utilisateur ait quitté
        switch(events.type)
        {
            case SDL_QUIT:
            quit = 1 ;
            break ;

            case SDL_MOUSEBUTTONDOWN: // si il a cliqué, l'action dépend du bouton donc re-switch
                switch(events.button.button)
                {
                case SDL_BUTTON_LEFT: // clic gauche : on teste si le clic se fait dans la zone de l'image

                        xSouris = events.button.x ;
                        ySouris = events.button.y ;
                        SDL_GetMouseState(&xSouris, &ySouris);
                        quit = 1 ;
                 break;
                }
            break;
        }
    }

    if ( (xSouris>=im.posX) && (xSouris<im.posX+im.dimX) &&  (ySouris>=im.posY) && (ySouris<im.posY+im.dimY) )
    {
            clic = true  ;
    }

    return clic ;
}

void JeuModeGraphique::memoryGraphiqueInit()
{
    jeu.memory.repartirCartes() ;  // on répartit les cartes de Memory::tabCartes
    // maintenant, chaque carte a une position dans la grille mode texte, qui est stockée dans idCarte
    // on associe chaque idCarte a une position à l'écran
    int i ;
    for (i=0; i<8; i++)
    {
        // Pour nous faciliter la gestion du clic, les images de cartes doivent toutes avoir la même dimension : 200x270
        tabImagesMemory[i].dimX= DIMX_CARTE ;
        tabImagesMemory[i].dimY= DIMY_CARTE ;

        switch(jeu.memory.tabCartes[i].idCarte) // selon idCarte (=selon la position de la carte dans la grille mode texte)
        {
            // on affichera l'image correspondante à une certaine position de l'écran
        case 0:
            tabImagesMemory[i].posX = 30 ;
            tabImagesMemory[i].posY = 180 ;
        break ;

        case 1:
            tabImagesMemory[i].posX = 260 ;
            tabImagesMemory[i].posY = 180 ;
        break;

        case 2:
            tabImagesMemory[i].posX = 490 ;
            tabImagesMemory[i].posY = 180 ;
        break;

        case 3:
            tabImagesMemory[i].posX = 720 ;
            tabImagesMemory[i].posY = 180 ;
        break;

        case 4:
            tabImagesMemory[i].posX = 30 ;
            tabImagesMemory[i].posY = 480 ;
        break;

        case 5:
            tabImagesMemory[i].posX = 260 ;
            tabImagesMemory[i].posY = 480 ;
        break;

        case 6:
            tabImagesMemory[i].posX = 490 ;
            tabImagesMemory[i].posY = 480 ;
        break;

        case 7:
            tabImagesMemory[i].posX = 720 ;
            tabImagesMemory[i].posY = 480 ;
        break;

            default : cout<<endl<<"erreur lors de la répartition des positions de cartes à l'écran"<<endl;
            break;

        }

    }
}

void JeuModeGraphique::solutionMemoryGraphique()
{
    SDL_RenderClear(renderer) ;
    int i ;
    jeu.memory.afficherSolution() ;
    for (i=0; i<nbImagesCartes-1; i++) // tout sauf dosCarte
    {

        int x,y ;
        x = tabImagesMemory[i].posX ;
        y = tabImagesMemory[i].posY ;
        tabImagesMemory[i].dessiner(renderer, x, y, DIMX_CARTE, DIMY_CARTE) ;
    }

    SDL_RenderPresent(renderer) ;
    SDL_Delay(3000) ;
}

void JeuModeGraphique::retournerImagesCartes(int indiceImage1, int indiceImage2)
{
    // pour retourner temporairement : affichage dos carte, puis les images pendant 2sec, puis de nouveau le dos carte
    SDL_RenderClear(renderer) ;
    int i ;
    for (i=0; i<nbImagesCartes-1; i++)
    {
        int x,y ;
        x = tabImagesMemory[i].posX ;
        y = tabImagesMemory[i].posY ;


        if(i==indiceImage1 || i==indiceImage2 || jeu.memory.tabCartes[i].visible == true ||  jeu.memory.tabCartes[i].visible == true)
        {
            int x,y ;
            x = tabImagesMemory[i].posX ;
            y = tabImagesMemory[i].posY ;
            tabImagesMemory[i].dessiner(renderer, x, y, DIMX_CARTE, DIMY_CARTE) ;
        }
        else
        {
            tabImagesMemory[nbImagesCartes-1].dessiner(renderer, x, y, DIMX_CARTE, DIMY_CARTE) ;
        }
    }
        SDL_RenderPresent(renderer) ;
        SDL_Delay(2000) ;

}

void JeuModeGraphique::afficherImagesCartes()
{
        SDL_RenderClear(renderer) ;
        int i ;
        int nombreCartes = jeu.memory.nbCartes ;
        for (i=0 ; i<nombreCartes ; i++)
        {
            int x,y ;
            x = tabImagesMemory[i].posX ;
            y = tabImagesMemory[i].posY ;

            if (jeu.memory.tabCartes[i].visible==true)
            {
                tabImagesMemory[i].dessiner(renderer,x,y,DIMX_CARTE, DIMY_CARTE) ;

            }
            else
            {
                tabImagesMemory[nombreCartes].dessiner(renderer,x,y,DIMX_CARTE, DIMY_CARTE) ;
            }
        }
       // SDL_RenderPresent(renderer) ;
        //SDL_Delay(3000) ;
}

void JeuModeGraphique::memoryGraphiqueBoucle()
{
    SDL_RenderClear(renderer) ;
    jeu.memory.memoryGagne = false ;
    jeu.memory.nbPairesTrouvees = 0 ;
    memoryGraphiqueInit(); // répartition aléatoire des positions des images etc

    //jeu.memory.afficherSolution() ; // test : afficher la solution en console

    ////////////// Image de bienvenue ////////////////////////
    Image bienvenue ;
    bienvenue.chargerDepuisFichier("./data/memory/bienvenue.png", renderer) ;
    bienvenue.dessinerArrierePlan(renderer,0,0,210,210);
    SDL_RenderPresent(renderer) ;
    SDL_Delay(3000) ;
    afficherImagesCartes() ;  SDL_RenderPresent(renderer) ;


    int quit=0;
    SDL_Event events ;
    int nombreCartes = jeu.memory.nbCartes ; cout<<endl<<nombreCartes;
    int indiceCarteChoisie1, indiceCarteChoisie2 ; // stockera les positions des deux cartes choisies dans la grille mode texte (donc leur idCarte)
    int indiceImage1, indiceImage2 ; // la position, dans tabImagesMemory, de l'image à afficher
    int nbCartesChoisies ;
    int i=0 ;

    // Tant que la partie n'est pas finie et que le joueur n'a pas quitté
    while ( (!jeu.memory.memoryGagne) && (!quit) )
    {
        SDL_PollEvent(&events);
        nbCartesChoisies = 0 ;
        // On ne peut pas se contenter des boucles if car il se peut qu'elles se terminent avant que le joueur ait cliqué sur ses cartes
        // => Pour lui laisser le temps : boucle while
        while ( nbCartesChoisies < 2)
        {
           // afficherImagesCartes() ;

            // Pour chaque image de tabImagesMemory, on regarde si le joueur a cliqué dessus
            if (verifClicImage(tabImagesMemory[i]))
            {
                switch(nbCartesChoisies)
                {
                    case 0: // première carte

                            indiceCarteChoisie1 = jeu.memory.tabCartes[i].idCarte ;
                            indiceImage1 = i ; // il faudra afficher (brièvement ou non) la i-ième image de tabImagesMemory
                            nbCartesChoisies ++ ;

                            // test
                            cout<<endl<<" nbCartesChoisies: "<<nbCartesChoisies ;
                            cout<<endl<<"choix 1 dans tabcartes/images = "<<i<<endl ;
                            cout<<endl<<"choix 1, dans la grille  = "<<indiceCarteChoisie1<<" "<<jeu.memory.tabCartes[i].idCarte <<endl ;


                    break ;
                    case 1: // deuxième carte

                        indiceImage2 = i ;
                        indiceCarteChoisie2 = jeu.memory.tabCartes[i].idCarte ;
                        nbCartesChoisies ++ ;

                        // test
                        cout<<endl<<" nbCartesChoisies: "<<nbCartesChoisies ;
                        cout<<endl<<"choix 2  dans tabcartes/images = "<<i<<endl ;
                        cout<<endl<<"choix 2, dans la grille  = "<<indiceCarteChoisie2<<" "<<jeu.memory.tabCartes[i].idCarte <<endl ;

                    break ;
                }


             }

            // test
            if (nbCartesChoisies==2)
            {
                cout<<endl<<"choix fini "<<endl ;
                cout<<endl<<"cartes choisies : "<<indiceImage1<<indiceImage2 ;

            }

            i++ ;
            if (i==nombreCartes) i= 0 ; // pour que la boucle tourne en laissant le temps au joueur de cliquer
        }

        cout<<endl<<"Fin du choix des cartes :";
        cout<<endl<<" images cartes choisies : "<<indiceImage1<<indiceImage2 ;
        cout<<endl<<" grille cartes choisies : "<<indiceCarteChoisie1<<indiceCarteChoisie2 ;
        cout<<endl<<" motifs correspondant : "<<jeu.memory.tabCartes[indiceImage1].motif;
        cout<<endl<<" motifs correspondant : "<<jeu.memory.tabCartes[indiceImage2].motif;



        //En sortie de cette boucle, on enregistré les images à retourner (indiceImage1,2) et leur position dans la grille mode
        // texte (indiceCarteChoisie1,2)afin d'appeler les fonctions du memory texte avec ces indices en paramètres :

        //jeu.memory.choixCartes(indiceCarteChoisie1+1,indiceCarteChoisie2+1) ;

        cout<<endl<<"motifs identiques : "<<(jeu.memory.grille[indiceCarteChoisie1].motif == jeu.memory.grille[indiceCarteChoisie2].motif) ;
        if(jeu.memory.grille[indiceCarteChoisie1].motif == jeu.memory.grille[indiceCarteChoisie2].motif  )
        {
                jeu.memory.tabCartes[indiceImage1].visible = true  ;
                jeu.memory.tabCartes[indiceImage2].visible = true  ;
                cout<<endl<<"tabCartes[indiceImage1].visible "<<jeu.memory.tabCartes[indiceImage1].visible<<endl;
                cout<<endl<<"tabCartes[indiceImage2].visible "<<jeu.memory.tabCartes[indiceImage2].visible<<endl;
                jeu.memory.nbPairesTrouvees++ ;
                cout<<endl<<"paire trouvée";     cout<<endl<<" nb paires trouvées : "<<jeu.memory.nbPairesTrouvees<<endl ;
                if(jeu.memory.nbPairesTrouvees==4)
                {
                    jeu.memory.memoryGagne = true ;
                }
                afficherImagesCartes() ;  SDL_RenderPresent(renderer) ;
        }
       else
        {    // Si les cartes sont différentes, il faut les retourner temporairement :
            cout<<endl<<"cartes différentes ";     cout<<endl<<" nb paires trouvées : "<<jeu.memory.nbPairesTrouvees<<endl ;
            retournerImagesCartes(indiceImage1, indiceImage2) ; SDL_RenderPresent(renderer) ;


        }

        afficherImagesCartes() ; SDL_RenderPresent(renderer) ;

        if (events.type==SDL_KEYDOWN&&events.key.keysym.sym==SDLK_ESCAPE)
        {
             quit = 1 ;
            afficheJeu();
        }

        if(jeu.memory.memoryGagne)
        {
            solutionMemoryGraphique(); SDL_RenderPresent(renderer) ;
            //cout<<endl<<"gagné" ;
             ////////////// Image de félicitations  ////////////////////////
            Image felicitations ;

            felicitations.chargerDepuisFichier("./data/memory/felicitations.png", renderer) ;
            felicitations.dessinerArrierePlan(renderer, 0, 0, 210, 210);
            SDL_RenderPresent(renderer);
            SDL_Delay(3000);
            afficheJeu();

        }

    } // fin while

        for(i=0; i<8; i++)
        {
            jeu.memory.tabCartes[i].visible = false ;
        }
        SDL_RenderClear(renderer) ;
        SDL_RenderPresent(renderer);
        cout<<endl<<"sortie de la fct";
}
void JeuModeGraphique::testRegMemoryGraphique()
 {
    JeuModeGraphique jeuTest;
    int i, j;
    jeuTest.memoryGraphiqueInit();

    for (i=0; i<8; i++)
    {
        assert(jeuTest.tabImagesMemory[i].dimX == DIMX_CARTE );
        assert(jeuTest.tabImagesMemory[i].dimY == DIMY_CARTE );
    }


    for (j=0; j<8; j++)
    {
        switch(jeu.memory.tabCartes[j].idCarte)
        {
            case 0:
                assert(tabImagesMemory[j].posX == 30);
                assert(tabImagesMemory[j].posY == 180);
            break ;

            case 1:
                assert(tabImagesMemory[j].posX == 260);
                assert(tabImagesMemory[j].posY == 180);
            break ;

            case 2:
                assert(tabImagesMemory[j].posX == 490);
                assert(tabImagesMemory[j].posY == 180);
            break ;

            case 3:
                assert(tabImagesMemory[j].posX == 720);
                assert(tabImagesMemory[j].posY == 180);
            break ;

            case 4:
                assert(tabImagesMemory[j].posX == 30);
                assert(tabImagesMemory[j].posY == 480);
            break ;

            case 5:
                assert(tabImagesMemory[j].posX == 260);
                assert(tabImagesMemory[j].posY == 480);
            break ;

            case 6:
                assert(tabImagesMemory[j].posX == 490) ;
                assert(tabImagesMemory[j].posY == 480);
            break;

            case 7:
                assert(tabImagesMemory[j].posX == 720) ;
                assert(tabImagesMemory[j].posY == 480);
            break;
        }
    }

    JeuModeGraphique jeuTest2;
    jeuTest2.memoryGraphiqueBoucle();
    int k;

    for(k=0; k<8; k++)
    {
        assert(jeuTest2.jeu.memory.tabCartes[k].visible == false) ;
    }

    assert(jeuTest2.jeu.memory.memoryGagne == true) ;
    assert(jeuTest2.jeu.memory.nbPairesTrouvees == 4) ;

    cout<<endl<<"Test effectué avec succes"<<endl;
}

void JeuModeGraphique::introductionJeu()
{
    Image arrierePlan1;
    //affichage de l'arriere plan
    arrierePlan1.chargerDepuisFichier("./data/arrierePlan/arrierePlanIntro.png",renderer);
    arrierePlan1.dessinerArrierePlan(renderer,0,0,210,210);

    //chargement des images des textes
    Image texteIntro1, texteIntro2, texteIntro3;
    texteIntro1.chargerDepuisFichier("./data/texte/texteIntro1.png",renderer);
    texteIntro2.chargerDepuisFichier("./data/texte/texteIntro2.png",renderer);
    texteIntro3.chargerDepuisFichier("./data/texte/texteIntro3.png",renderer);

    //affichage des oeufs
    oeufBleu.dessiner(renderer,440,660,180,180) ;
    oeufRose.dessiner(renderer,480,100,180,180) ;
    oeufJaune.dessiner(renderer,330,360,200,200) ;
    oeufVert.dessiner(renderer,660,450,200,200) ;

    //affichage des textes
    texteIntro1.dessiner(renderer,250,0,480,120);
    texteIntro2.dessiner(renderer,30,200,450,200);
    texteIntro3.dessiner(renderer,10,570,420,330);

    SDL_RenderPresent(renderer);

    int xSouris, ySouris;

    int quit=0;

    //position de l'oeuf rose
    SDL_Rect rRose;
    rRose.x = 480;
    rRose.y = 100;
    rRose.w = 180;
    rRose.h =180;

    //position de l'oeuf jaune
    SDL_Rect rJaune;
    rJaune.x = 330;
    rJaune.y = 360;
    rJaune.w = 200;
    rJaune.h =200;

    //position de l'oeuf vert
    SDL_Rect rVert;
    rVert.x = 660;
    rVert.y = 450;
    rVert.w = 200;
    rVert.h =200;

    //position de l'oeuf bleu
    SDL_Rect rBleu;
    rBleu.x = 440;
    rBleu.y = 660;
    rBleu.w = 180;
    rBleu.h =180;

    SDL_Event events;
    while(!quit)
    {
        SDL_PollEvent(&events);

            switch(events.type)
            {
                case SDL_QUIT:
                    quit=1;
                    // Appui de la croix pour quitter
                    boolBleu=false;
                    boolRose=false;
                    boolVert=false;
                    boolJaune=false;
                break;

                case SDL_MOUSEBUTTONDOWN:
                    switch(events.button.button)
                    {
                        case SDL_BUTTON_LEFT:

                            xSouris = events.button.x;
                            ySouris = events.button.y;
                            SDL_GetMouseState(&xSouris, &ySouris);
                            quit=1;
                        break;
                    }

                break;
            }

    }


    if (xSouris>=rBleu.x && xSouris<rBleu.x+rBleu.w && ySouris>=rBleu.y && ySouris<=rBleu.y+rBleu.h)
    {
        //si l'utilisateur clique sur l'oeuf bleu, boolBleu prend la valeur true
        boolBleu=true;
        boolRose=false;
        boolVert=false;
        boolJaune=false;
    }
    if (xSouris>=rRose.x && xSouris<rRose.x+rRose.w && ySouris>=rRose.y && ySouris<=rRose.y+rRose.h)
    {
        //si l'utilisateur clique sur l'oeuf rose, boolRose prend la valeur true
        boolBleu=false;
        boolRose=true;
        boolVert=false;
        boolJaune=false;
    }
    if (xSouris>=rVert.x && xSouris<rVert.x+rVert.w && ySouris>=rVert.y && ySouris<=rVert.y+rVert.h)
    {
        //si l'utilisateur clique sur l'oeuf vert, boolVert prend la valeur true
        boolBleu=false;
        boolRose=false;
        boolVert=true;
        boolJaune=false;
    }
    if (xSouris>=rJaune.x && xSouris<rJaune.x+rJaune.w && ySouris>=rJaune.y && ySouris<=rJaune.y+rJaune.h)
    {
        //si l'utilisateur clique sur l'oeuf jaune, boolJaune prend la valeur true
        boolBleu=false;
        boolRose=false;
        boolVert=false;
        boolJaune=true;
    }

    SDL_Delay(6000) ;
}

void JeuModeGraphique::introductionJeu2()
{
    introductionJeu();

    Image arrierePlan2, coussin, texteIntro4;

    if (boolBleu==true) //si l'utilisateur a cliqué sur l'oeuf bleu
    {
        //affichage de l'arriere2 plan, de l'oeuf et du coussin
        arrierePlan2.chargerDepuisFichier("./data/arrierePlan/arrierePlanIntro2.png",renderer);
        arrierePlan2.dessinerArrierePlan(renderer,0,0,210,210);
        coussin.chargerDepuisFichier("./data/coussin/coussinBleu.png",renderer);
        coussin.dessiner(renderer,150,260,700,700);
        oeufBleu.dessiner(renderer,260,160,500,500) ;

        SDL_RenderPresent(renderer);
        SDL_Delay(3000) ;


        //affichage de l'arriere plan bleu, du Capri bleu et du texte
        arrierePlan2.chargerDepuisFichier("./data/arrierePlan/arriereBleu.png",renderer);
        arrierePlan2.dessinerArrierePlan(renderer,0,0,210,210);
        texteIntro4.chargerDepuisFichier("./data/texte/nomBleu.png",renderer);
        texteIntro4.dessiner(renderer,80,5,860,250);
        tabImagesBleu[0].dessiner(renderer,100,150,800,800) ;
    }
    else if (boolRose==true) //si l'utilisateur a clique sur l'oeuf rose
    {
        //affichage de l'arriere2 plan, de l'oeuf et du coussin
        arrierePlan2.chargerDepuisFichier("./data/arrierePlan/arrierePlanIntro2.png",renderer);
        arrierePlan2.dessinerArrierePlan(renderer,0,0,210,210);
        coussin.chargerDepuisFichier("./data/coussin/coussinRose.png",renderer);
        coussin.dessiner(renderer,150,260,700,700);
        oeufRose.dessiner(renderer,270,150,500,500) ;

        SDL_RenderPresent(renderer);
        SDL_Delay(3000) ;

        //affichage de l'arriere plan rose, du Capri rose et du texte
        arrierePlan2.chargerDepuisFichier("./data/arrierePlan/arriereRose.png",renderer);
        arrierePlan2.dessinerArrierePlan(renderer,0,0,210,210);
        texteIntro4.chargerDepuisFichier("./data/texte/nomRose.png",renderer);
        texteIntro4.dessiner(renderer,80,5,800,250);
        tabImagesRose[0].dessiner(renderer,100,150,800,800) ;
    }
    else if (boolJaune==true) //si l'utilisateur a clique sur l'oeuf jaune
    {
        //affichage de l'arriere2 plan, de l'oeuf et du coussin
        arrierePlan2.chargerDepuisFichier("./data/arrierePlan/arrierePlanIntro2.png",renderer);
        arrierePlan2.dessinerArrierePlan(renderer,0,0,210,210);
        coussin.chargerDepuisFichier("./data/coussin/coussinJaune.png",renderer);
        coussin.dessiner(renderer,150,260,700,700);
        oeufJaune.dessiner(renderer,260,180,500,500) ;

        SDL_RenderPresent(renderer);
        SDL_Delay(3000) ;

        //affichage de l'arriere plan jaune, du Capri jaune et du texte
        arrierePlan2.chargerDepuisFichier("./data/arrierePlan/arriereJaune.png",renderer);
        arrierePlan2.dessinerArrierePlan(renderer,0,0,210,210);
        texteIntro4.chargerDepuisFichier("./data/texte/nomJaune.png",renderer);
        texteIntro4.dessiner(renderer,80,10,800,250);
        tabImagesJaune[0].dessiner(renderer,100,150,800,800) ;

    }else //si l'utilisateur a clique sur l'oeuf vert
    {
        //affichage de l'arriere2 plan, de l'oeuf et du coussin
        arrierePlan2.chargerDepuisFichier("./data/arrierePlan/arrierePlanIntro2.png",renderer);
        arrierePlan2.dessinerArrierePlan(renderer,0,0,210,210);
        coussin.chargerDepuisFichier("./data/coussin/coussinVert.png",renderer);
        coussin.dessiner(renderer,150,260,700,700);
        oeufVert.dessiner(renderer,260,180,500,500) ;

        SDL_RenderPresent(renderer);
        SDL_Delay(3000) ;

        //affichage de l'arriere plan vert, du Capri vert et du texte
        arrierePlan2.chargerDepuisFichier("./data/arrierePlan/arriereVert.png",renderer);
        arrierePlan2.dessinerArrierePlan(renderer,0,0,210,210);
        texteIntro4.chargerDepuisFichier("./data/texte/nomVert.png",renderer);
        texteIntro4.dessiner(renderer,80,5,800,250);
        tabImagesVert[0].dessiner(renderer,100,180,800,800) ;
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(5000) ;

}
void JeuModeGraphique::afficheJeu()
{
  //  Affichage background, personnage, boutons

   arrierePlan.chargerDepuisFichier("./data/arrierePlan/arrierePlan.png",renderer);
   arrierePlan.dessinerArrierePlan(renderer,0.5,0,210,210);

   boutons[2].dessiner(renderer,650,800,110,110);
   boutons[0].dessiner(renderer,250,800,110,110);
   boutons[1].dessiner(renderer,450,800,110,110);

      if(boolBleu==true)
        {tabImagesBleu[0].dessiner(renderer,320,390,400,400)  ;}
    else if(boolRose==true)
        {tabImagesRose[0].dessiner(renderer,280,415,500,500) ;}
    else if(boolVert==true)
        {tabImagesVert[0].dessiner(renderer,280,390,500,500)  ;}
    else tabImagesJaune[0].dessiner(renderer,280,350,500,500)  ;

    affAmusement();
    affEnergie();
    affFaim();

   SDL_RenderPresent(renderer);
}

void JeuModeGraphique::affFaim()
{
    Image texteFaim;
    texteFaim.chargerDepuisFichier("./data/texte/texteFaim.png",renderer);

    int faim = jeu.getPersonnage().etat.getFaim();
    switch(faim)
    {
        case 0 :
            barreFaim.chargerDepuisFichier("./data/bouton/barre0.png",renderer);
            barreFaim.dessiner(renderer,650,890,110,110);
            break;

        case 1 :
            barreFaim.chargerDepuisFichier("./data/bouton/barre1.png",renderer);
            barreFaim.dessiner(renderer,650,890,110,110);

            texteFaim.dessiner(renderer, 400, 300, 200, 200);

            if(boolBleu==true)
                {tabImagesBleu[1].dessiner(renderer,320,390,400,400)  ;}
            else if(boolRose==true)
                {tabImagesRose[1].dessiner(renderer,280,415,500,500) ;}
            else if(boolVert==true)
                {tabImagesVert[1].dessiner(renderer,280,390,500,500)  ;}
            else tabImagesJaune[1].dessiner(renderer,280,350,500,500)  ;

        break;

        case 2 :
            barreFaim.chargerDepuisFichier("./data/bouton/barre2.png",renderer);
            barreFaim.dessiner(renderer,650,890,110,110);
        break;

        case 3 :
            barreFaim.chargerDepuisFichier("./data/bouton/barre3.png",renderer);
            barreFaim.dessiner(renderer,650,890,110,110);
        break;

        case 4 :
            barreFaim.chargerDepuisFichier("./data/bouton/barre4.png",renderer);
            barreFaim.dessiner(renderer,650,890,110,110);
        break;

        case 5 :
            barreFaim.chargerDepuisFichier("./data/bouton/barre5.png",renderer);
            barreFaim.dessiner(renderer,650,890,110,110);
        break;

    }
}

void JeuModeGraphique::affEnergie()
{
    int energie = jeu.getPersonnage().etat.getEnergie();

    Image texteEnergie;
    texteEnergie.chargerDepuisFichier("./data/texte/texteEnergie.png",renderer);

    switch(energie)
    {
        case 0 :
            barreEnergie.chargerDepuisFichier("./data/bouton/barre0.png",renderer);
            barreEnergie.dessiner(renderer,250,890,110,110);
        break;

        case 1 :
            barreEnergie.chargerDepuisFichier("./data/bouton/barre1.png",renderer);
            barreEnergie.dessiner(renderer,250,890,110,110);

            texteEnergie.dessiner(renderer, 200, 450, 200, 200);

            if(boolBleu==true)
                {tabImagesBleu[2].dessiner(renderer,320,390,400,400)  ;}
            else if(boolRose==true)
                {tabImagesRose[2].dessiner(renderer,280,415,500,500) ;}
            else if(boolVert==true)
                {tabImagesVert[2].dessiner(renderer,280,390,500,500)  ;}
            else tabImagesJaune[2].dessiner(renderer,280,350,500,500)  ;

        break;

        case 2 :
            barreEnergie.chargerDepuisFichier("./data/bouton/barre2.png",renderer);
            barreEnergie.dessiner(renderer,250,890,110,110);
        break;

        case 3 :
            barreEnergie.chargerDepuisFichier("./data/bouton/barre3.png",renderer);
            barreEnergie.dessiner(renderer,250,890,110,110);
        break;

        case 4 :
            barreEnergie.chargerDepuisFichier("./data/bouton/barre4.png",renderer);
            barreEnergie.dessiner(renderer,250,890,110,110);
        break;

        case 5 :
            barreEnergie.chargerDepuisFichier("./data/bouton/barre5.png",renderer);
            barreEnergie.dessiner(renderer,250,890,110,110);
        break;

    }
}

void JeuModeGraphique::affAmusement()
{
    int amusement = jeu.getPersonnage().etat.getAmusement();

    Image texteAmusement;
    texteAmusement.chargerDepuisFichier("./data/texte/texteAmusement.png",renderer);

    switch(amusement)
    {
        case 0 :
            barreAmusement.chargerDepuisFichier("./data/bouton/barre0.png",renderer);
            barreAmusement.dessiner(renderer,450,890,110,110);
        break;


        case 1 :
            barreAmusement.chargerDepuisFichier("./data/bouton/barre1.png",renderer);
            barreAmusement.dessiner(renderer,450,890,110,110);

            texteAmusement.dessiner(renderer, 600, 400, 200, 200);

            if(boolBleu==true)
                {tabImagesBleu[1].dessiner(renderer,320,390,400,400)  ;}
            else if(boolRose==true)
                {tabImagesRose[1].dessiner(renderer,280,415,500,500) ;}
            else if(boolVert==true)
                {tabImagesVert[1].dessiner(renderer,280,390,500,500)  ;}
            else tabImagesJaune[1].dessiner(renderer,280,350,500,500)  ;

            break;

        case 2 :
            barreAmusement.chargerDepuisFichier("./data/bouton/barre2.png",renderer);
            barreAmusement.dessiner(renderer,450,890,110,110);
        break;

        case 3 :
            barreAmusement.chargerDepuisFichier("./data/bouton/barre3.png",renderer);
            barreAmusement.dessiner(renderer,450,890,110,110);
        break;

        case 4 :
            barreAmusement.chargerDepuisFichier("./data/bouton/barre4.png",renderer);
            barreAmusement.dessiner(renderer,450,890,110,110);
        break;

        case 5 :
            barreAmusement.chargerDepuisFichier("./data/bouton/barre5.png",renderer);
            barreAmusement.dessiner(renderer,450,890,110,110);
        break;

    }
}

void JeuModeGraphique::affFinJeuGagne()
{
    Image victoire;

    if(boolBleu==true)
    {
        victoire.chargerDepuisFichier("./data/arrierePlan/victoireBleu.png",renderer);
        victoire.dessinerArrierePlan(renderer,0,0,210,210);
    }
    else if(boolRose==true)
      {
        victoire.chargerDepuisFichier("./data/arrierePlan/victoireRose.png",renderer);
        victoire.dessinerArrierePlan(renderer,0,0,210,210);
    }
    else if(boolVert==true)
    {
        victoire.chargerDepuisFichier("./data/arrierePlan/victoireVert.png",renderer);
        victoire.dessinerArrierePlan(renderer,0,0,210,210);
    }
    else if(boolJaune==true)
    {
        victoire.chargerDepuisFichier("./data/arrierePlan/victoireJaune.png",renderer);
        victoire.dessinerArrierePlan(renderer,0,0,210,210);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(7000) ;

    SDL_Quit();
     return;

}

void JeuModeGraphique::affFinJeuPerdu()
{
    //affichage fond noir
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    //chargement du texte
    Image texteIntro4, aile, aureole;
    texteIntro4.chargerDepuisFichier("./data/texte/finJeu.png",renderer);
    texteIntro4.dessiner(renderer,35,5,860,250);
    aile.chargerDepuisFichier("./data/mort/ailes.png",renderer);
    aureole.chargerDepuisFichier("./data/mort/aureole.png",renderer);

    //affichage du Capri mort
    if(boolBleu==true)
    {
        aureole.dessiner(renderer,250,100,500,500);
        aile.dessiner(renderer,100,100,800,800);
        tabImagesBleu[3].dessiner(renderer,100,150,800,800) ;
    }
    else if(boolRose==true)
    {
        aureole.dessiner(renderer,250,100,500,500);
        aile.dessiner(renderer,100,100,800,800);
        tabImagesRose[3].dessiner(renderer,20,150,1000,1000) ;
    }
    else if(boolVert==true)
    {
        aureole.dessiner(renderer,250,100,500,500);
        aile.dessiner(renderer,100,100,800,800);
        tabImagesVert[3].dessiner(renderer,10,80,1000,1000) ;
    }
    else if(boolJaune==true)
    {
        aureole.dessiner(renderer,250,100,500,500);
        aile.dessiner(renderer,100,100,800,800);
        tabImagesJaune[3].dessiner(renderer,50,100,950,950) ;
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(4000) ;

    SDL_Quit();
     return;

}

void JeuModeGraphique::timerFaimEnergie (Timer chrono)
{
    int a = chrono.getTics();
    if (a == 0)
    {
        return; 
    }
    else 
    { 
        if (chrono.getTics()%15000 == 0)
        {
            jeu.personnage.etat.energie--; 
            jeu.personnage.etat.faim--;
            afficheJeu();  
            timerFaimEnergie(chrono);         
        } 
        return; 
    }
}

void JeuModeGraphique::timerAmusement (Timer chrono)
{
  int a = chrono.getTics();
    if (a == 0)
    {
        return; 
    }
    else 
    { 
        if (chrono.getTics()%25000 == 0)
        {
            jeu.personnage.etat.amusement--; 
            afficheJeu();  
            timerFaimEnergie(chrono); 
        } 
        return; 
    }
}

void JeuModeGraphique::boucleJeuGraph()
{
    introductionJeu2();
    SDL_Event events; 
    Timer chrono; 
    chrono.demarrerTimer(); 
    bool finJeu = false; 
    while(!finJeu)
    {
        Mix_PlayChannel(-1,son,0);
        timerAmusement(chrono);
        timerFaimEnergie(chrono); 
        if ((jeu.personnage.etat.getAmusement()==0) || (jeu.personnage.etat.getEnergie()==0) || (jeu.personnage.etat.getFaim()==0)) {affFinJeuPerdu();}
        if ((jeu.personnage.etat.getAmusement()==5) && (jeu.personnage.etat.getEnergie()==5) && (jeu.personnage.etat.getFaim()==5)) {affFinJeuGagne();}
        while(SDL_PollEvent(&events))
        {
            if(events.type == SDL_QUIT)
            {
                finJeu = true; 
            }
            if (events.type == SDL_MOUSEBUTTONDOWN)
            {
                afficheJeu();
                int i=0 ;
                int indiceBouton ;
                bool clic = false ;
                while(!clic) 
                {
                        if(verifClicImage(boutons[i]))
                        {
                            indiceBouton = i ;
                            clic = true ;
                        
                        }

                    i++ ;
                    if (i==3) i= 0 ;
                }


                cout<<endl<<"bouton choisi "<<indiceBouton;

                switch(indiceBouton)
                {
                    case 0:
                        jeu.dormir();

                        if ((jeu.personnage.etat.getAmusement()==0) || (jeu.personnage.etat.getEnergie()==0) || (jeu.personnage.etat.getFaim()==0)) {affFinJeuPerdu();}
                        if ((jeu.personnage.etat.getAmusement()==5) && (jeu.personnage.etat.getEnergie()==5) && (jeu.personnage.etat.getFaim()==5)) {affFinJeuGagne();}
                    break;

                    case 1:

                        chrono.pause();
                        memoryGraphiqueInit() ;
                        memoryGraphiqueBoucle();
                        chrono.dePause(); 
                        jeu.personnage.etat.setAmusement(jeu.personnage.etat.getAmusement()+2);

                        if ((jeu.personnage.etat.getAmusement()==0) || (jeu.personnage.etat.getEnergie()==0) || (jeu.personnage.etat.getFaim()==0)) {affFinJeuPerdu();}
                        if ((jeu.personnage.etat.getAmusement()==5) && (jeu.personnage.etat.getEnergie()==5) && (jeu.personnage.etat.getFaim()==5)) {affFinJeuGagne();}

                    break;

                    case 2:
                        jeu.nourrir();

                        if ((jeu.personnage.etat.getAmusement()==0) || (jeu.personnage.etat.getEnergie()==0) || (jeu.personnage.etat.getFaim()==0)) {affFinJeuPerdu();}
                        if ((jeu.personnage.etat.getAmusement()==5) && (jeu.personnage.etat.getEnergie()==5) && (jeu.personnage.etat.getFaim()==5)) {affFinJeuGagne();}
                    break ;
                }
                afficheJeu();
            }
        }
        
    }
    SDL_Quit(); 
}
