#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Jeu.h"

using namespace std;

#ifndef SDLJEU_H_INCLUDED
#define SDLJEU_H_INCLUDED

class Image
{
    /**
    *@brief JeuModeGraphique est une classe amie de Image.
    */
    friend class JeuModeGraphique ;

    private:

    /**
    *@param La donnée membre surface est un pointeur sur une structure SDL.
    *@param La donnée membre aChange est un booléen indiquant si la suface a été modifiée.
    *@param Les données membres posX, et posY correspondent respectivement aux coordonnées horizontales et verticales de l'image à l'écran.
    *@param Les données membres dimX, et dimY correspondent respectivement aux dimensions de longueur et de largeur de l'image.
    */
    SDL_Surface * surface;
    SDL_Texture * texture;
    bool aChange;
    float  posX,posY;
    float dimX, dimY;



    public:

    /**
    *@brief Constructeur de la classe Image.
    */
    Image() ;

    /**
    *@brief Destructeur de la classe Image.
    */
    ~Image();

    /**
    *@brief La procédure permet de charger une image depuis un fichier.
    *@param Le paramètre nomFichier est un paramètre formel et est un pointeur sur caractère passé par copie.
    *@param Le paramètre renderer est un paramètre formel et est un pointeur sur une structure SDL.
    */
    void chargerDepuisFichier(const char* nomFichier, SDL_Renderer * renderer);

    /**
    *@brief La procédure permet de charger une image depuis une surface.
    *@param Le paramètre renderer est un paramètre formel et est un pointeur sur une structure SDL.
    */
    void chargerDepuisSurface(SDL_Renderer * renderer);

    /**
    *@brief La procédure permet de dessiner une texture à l'écran.
    *@param Le paramètre renderer est un paramètre formel et est un pointeur sur une structure SDL.
    *@param Les paramètres x et y sont des paramètres formels de type entier est représentent les dimensions de la texture à afficher.
    *@param Les paramètres w et h sont des paramètres formels de type entier est représentent respectivement la largeur et la hauteur de la texture à afficher.
    */
    void dessiner(SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);

    /**
    *@brief La procédure permet de dessiner une texture à l'écran qui représente l'aarire plan du jeu et dont les dimensions sont celles de la fenêtre.
    *@param Le paramètre renderer est un paramètre formel et est un pointeur sur une structure SDL.
    *@param Les paramètres x et y sont des paramètres formels de type entier est représentent les dimensions de la texture à afficher.
    *@param Les paramètres w et h sont des paramètres formels de type entier est représentent respectivement la largeur et la hauteur de la texture à afficher.
    */
    void dessinerArrierePlan(SDL_Renderer * renderer, int x, int y, int w, int h);

    /**
    *@brief Accesseur : récupère la donnée membre texture de l'image.
    *@return La fonction retourne un pointeur sur une structure SDL correspondant à la texture de l'image.
    */
    SDL_Texture * getTexture() const;

    /**
    *@brief Mutateur : modifie la donnée membre surface de l'image.
    *@param Le paramètre surf est un pointeur sur une structure SDL passé par copie.
    */
    void setSurface(SDL_Surface * surf);
};

class Timer
{
    private:

    /**
    *@param La donnée membre debutTimer est de type entier et enregistre le temps à partir duquel le timer est lancé.
    *@param La donnée membre pauseTics est de type entier et enregistre l'instant de mise en pause du timer.
    *@param Les données membres paused et started sont des booléens représentant le statut du timer.
    */
    int debutTimer;
    int pauseTics;
    bool enPause;
    bool started;

    public:

    /**
    *@brief Constructeur de la classe Timer.
    */
    Timer();

    /**
    *@brief La procédure demarrerTimer permet de mettre en marche le timer.
    */
    void demarrerTimer();

    /**
    *@brief La procédure arreterTimer permet  d'arrêter le timer.
    */
    void arreterTimer();

    /**
    *@brief La procédure pause permet de mettre en pause le timer.
    */
    void pause();

    /**
    *@brief La procédure dePause permet de remettre en marche le timer.
    */
    void dePause();

    /**
    *@brief La procédure permet de recupérer le nombre de millisecondes qui se sont écoulées depuis que le timer a été lancé.
    *@return La procédure retourne un entier indiquant le nombre de millisecondes qui se sont écoulées.
    */
    int getTics();

    /**
    *@brief La fonction vérifie que le timer est en marche.
    *@return La fonction retourne un booléen indiquant si le timer est en marche.
    */
    bool estEnMarche();

    /**
    *@brief La fonction vérifie que le timer est en pause.
    *@return Le fonction retourne un booléen indiquant si le timer est en pause.
    */
    bool estEnPause();
};

class JeuModeGraphique
{
    /**
    *@brief Personnage, Jeu et Etat sont des classes amies de JeuModeGraphique.
    */
    friend class Jeu;
    friend class Etat;
    friend class Personnage;

    private:

    /**
    *@param La donnée membre jeu est est de type Jeu.
    */
    Jeu jeu;

    /**
    *@param Les données membres fenetre et renderer sont des pointeurs sur des structures SDL.
    */
    SDL_Window * fenetre;
    SDL_Renderer * renderer;

    /**
    *@param Les données membres tabImagesRose, tabImagesVert, tabImagesBleu et tabImagesJaune sont des tableaux, alloués sur le tas, pour chaque Capri,
    nbImages de celui-ci dans différentes postures (Capri heureux, Capri endormi etc). Chaque image est un objet de la classe Image, définie précédemment.
    */
    // Images des Capri
    Image * tabImagesRose;
    Image * tabImagesVert;
    Image * tabImagesBleu;
    Image * tabImagesJaune ;

    /**
    *@param La donnée membre boutons est un tableau, alloués sur le tas, qui contient les Image des boutons dormir, nourrir et jouer.
    */
    //Images des boutons
    Image * boutons ;

    /**
    *@param tabImagesMemory est un tableau alloué sur le tas, contenant des objets de la classe Image, destinés à stocker les images des cartes du Memory,
    * rangées par paire, dans les 8 premières cases, ainsi que le dos de carte dans la dernière case.
    * On précise que dans la version graphique, chaque image de carte de carte de tabImagesMemory est associée à un motif de carte version texte (du tableau tabCartes)
    * rangée exactement au même indice.
    */

    // Images des cartes du Memory
    Image * tabImagesMemory ;

    /**
    *@param Les données membres arrierePlan, texteIntro1, texteIntro2 et texteIntro3 sont de type Image
    * permettant de réaliser l'introduction du jeu.
    */
    Image arrierePlan;

    /**
    *@param Les données membres barreFaim, barreEnergie, barreAmusement, boutonNourrir, boutonJouer, boutonDormir,
    * oeufBleu, oeufRose, oeufJaune et oeufVert sont de type Image. Il s'agit d'images utilisées plusieurs fois au cours du jeu, parfois à des positions différentes, sur lesquelles des interactions sont effectuées
    * (par exemple le clic sur les boutons), d'où l'interêt de les conserver en tant que données membres. 
    */
    Image boutonNourrir;
    Image boutonJouer;
    Image boutonDormir;
    Image barreFaim;
    Image barreEnergie;
    Image barreAmusement;
    Image oeufBleu;
    Image oeufRose;
    Image oeufJaune;
    Image oeufVert;

    /**
    *@param La donnée membre nbImages est un entier indiquant le nombre d'images dans chaque tableau d'images de Capri
    *@param La donnée membre nbImagesCartes est un entier indiquant le nombre d'images dans tabImagesMemory, en comptant l'image de dos de carte.
    */
    int nbImages;
    int nbImagesCartes ;

    /**
    *@param Les données membres boolBleu, boolRose, boolJaune et boolVert sont des booléens indiquant la couleur du Capri choisie par l'utilisateur.
    */
    bool boolBleu;
    bool boolRose;
    bool boolVert;
    bool boolJaune;

    /**
    *@param La donnée membre son est un pointeur sur un objet SDL Mix_Chunck, nécéssaire pour jouer le son d'arrière-plan du jeu. 
    * @param Le booléen "avecSon" détermine si le son sera joué ou non. 
    */
    Mix_Chunk * son;
    bool avecSon ;

    public:

    /**
    *@brief Constructeur de la classe JeuModeGraphique.
    */
    JeuModeGraphique();

    /**
    *@brief Destructeur de la classe JeuModeGraphique.
    */
    ~JeuModeGraphique();

    /**
    *@brief La procédure afficheJeu réalise l'affichage de l'ensemble des images statiques du jeu (arrière-plan, boutons...).
    */
    void afficheJeu();

    /**
    *@brief La procédure introductionJeu réalise l'affichage de la première partie de l'introduction du jeu.
    */
    void introductionJeu() ;

    /**
    *@brief La procédure introductionJeu réalise l'affichage de la seconde partie de l'introduction du jeu.
    */
    void introductionJeu2() ;

    /**
    *@brief La fonction verifClicImagedétermine si un clic du joueur s'est effectué sur une image passée en paramètre.
    *@param im est un paramètre de type Image passé en mode donnée
    *@return  verifClicImage renvoie un booléen indiquant si il y a eu collision entre le clic et la zone de l'image passée en paramètre.
    */
    bool verifClicImage(const Image &im) ;

    /**
    *@brief La procédure initMemoryGraphique permet d'initialiser les images du Memory version graphique, en leur attribuant des dimensions.
    * Elle leur attribue des positions aléatoires à l'écran en utilisant la fonction repartirCartes de la version texte : la position d'une
    * image de Carte à l'écran est determinée en fonction de  sa donnée membre idCarte (qui correspond à sa position dans la grille mode texte).
    */
    void memoryGraphiqueInit() ;

    /**
    * @brief La procédure solutionMemoryGraphique permet d'afficher la solution du memory en mode graphique. Elle est surtout présente dans le code pour nous faciliter les tests.
    */
    void solutionMemoryGraphique() ;

    /**
    *@brief La procédure retournerImagesCartes effectue un affichage permettant de retourner temporairement (2sec) des cartes différentes, sans les laisser affichées
    * tout au long de la partie de Memory.
    */
    void retournerImagesCartes(int indiceImage1, int indiceImage2) ;

    /**
    *@brief La procédure afficherImagesCartes permet d'afficher les images associées aux motifs des cartes de la version texte.
    */
    void afficherImagesCartes() ;

    /**
    * @brief La procédure memoryGraphiqueBoucle permet tout simplement de lancer une partie de Memory en mode graphique.
    * Elle fait pour cela appel aux fonctions de la version texte et à la gestion des évênements souris SDL.
    */
    void memoryGraphiqueBoucle() ;

    /**
    *@brief La procédure permet de lancer la boucle de jeu  et de jouer une partie dans son integralité. 
    */
    void boucleJeuGraph();

    /**
    *@brief La procédure qui permet de verifier le temps passé depuis le lancement du programme.
    * Elle adapte le niveau d'amusement en fonction de ce dernier.
    */
    void timerAmusement(Timer chrono); 

    /**
    *@brief La procédure qui permet de verifier le temps passé depuis le lancement du programme.
    * Elle adapte les niveaux de faim et d'energie en fonction de ce dernier.
    */
    void timerFaimEnergie(Timer chrono);


    /**
    *@brief La procédure effectue l'affichage du personnage en fonction du niveau de son état de faim.
    */
    void affFaim() ;

    /**
    *@brief La procédure effectue l'affichage du personnage en fonction du niveau de son état d'énergie.
    */
    void affEnergie()  ;

    /**
    *@brief La procédure effectue l'affichage du personnage en fonction du niveau de son état d'amusement.
    */
    void affAmusement() ;

    /**
    *@brief La procédure effectue un affichage indiquant que le jeu est perdu.
    */
    void affFinJeuPerdu() ;

    /**
    *@brief La procédure effectue un affichage indiquant que  le jeu est gagné.
    */
    void affFinJeuGagne() ;

    /**
    *@brief Le memory graphique faisant appel aux indices et aux données de la version texte, testRegMemoryGraphique vérifie que ces manipulations s'effectuent correctement. 
    */
    void testRegMemoryGraphique();
};

#endif // SDLJEU_H_INCLUDED
