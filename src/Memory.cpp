#include "Memory.h"
#include <cassert>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

//CLASSE CARTE

Carte::Carte() // constructeur par défaut
{
    idCarte = -1 ;   // l'id d'une carte vaut -1 si elle n'a pas encore été placée dans la grille
    visible = false ;
    motif = '0' ;

}

Carte::Carte(char monMotif)
{
    idCarte = -1 ;
    visible = false ;
    motif = monMotif ;
}

Carte::~Carte()
{

}

Carte& Carte::operator = (const Carte &c2 )
{
    int id2 = c2.getId() ;
    bool visible2 = c2.getVisible();
    char motif2 = c2.getMotif();
    idCarte = id2 ;
    visible = visible2 ;
    motif = motif2 ;
    return *this ;
}

int Carte::getId() const
{
    return idCarte ;
}

char Carte::getMotif() const
{
    return motif ;
}

bool Carte::getVisible() const
{
    return visible ;
}

void Carte::setVisible(bool vis)
{
    if (vis==0)
    {
        visible = false ;
    }
    else
        visible = true ;
}

void Carte::carteTestRegression()
{
    //test constructeur par defaut
    Carte test;
    assert(test.idCarte==-1);
    assert(test.visible==false);
    assert(test.motif=='0');

    //test constructeur avec paramètres
    Carte test2('$');
    assert(test2.idCarte==-1);
    assert(test2.visible==false);
    assert(test2.getMotif()=='$');

    //test operateur surcharge =
    test=test2;
    assert(test.idCarte==-1);
    assert(test.visible==false);
    assert(test.getMotif()=='$');

    //test getId, getMotif et getVisible
    assert(test.getId()==test.idCarte);
    assert(test.getMotif()==test.motif);
    assert(test.getVisible()==test.visible);

    //test setVisible
    test.setVisible(0);
    assert(test.getVisible()==false);
    test.setVisible(1);
    assert(test.getVisible()==true);

    cout<<"Test bien effectué pour la classe Carte"<<endl;

}

//CLASSE MEMORY

// Constructeur par défaut
Memory::Memory()
{
    // initialisation nbCartes, tabCartes, grille sur le tas  :
    nbCartes = 8 ;
    tabCartes = new Carte[nbCartes] ;
    grille = new Carte[nbCartes] ;

    // création des cartes de la partie
    Carte Carte1('*') ; Carte Carte2('*') ;
    Carte Carte3('+') ; Carte Carte4('+') ;
    Carte Carte5('!') ; Carte Carte6('!') ;
    Carte Carte7('#') ; Carte Carte8('#') ;

    // Pour le moment, pour chaque Carte, idCarte = -1 car pas encore dans la grille

    // insertion de ces cartes dans le tableau, rangement par paires

    // (impossible de faire tabCartes = { Carte1, Carte2 .... } )
    tabCartes[0] = Carte1 ; tabCartes[1] = Carte2 ; tabCartes[2] = Carte3 ;
    tabCartes[3] = Carte4 ; tabCartes[4] = Carte5 ; tabCartes[5] = Carte6 ;
    tabCartes[6] = Carte7 ; tabCartes[7] = Carte8 ;

    // Initialisation de la grille avec des cartes dont le motif par défaut est "n"
    int i ;
    for (i=0 ; i<nbCartes ; i++)
    {
        Carte carteInit('n') ;
        grille[i] = carteInit ;
    }

    nbPairesTrouvees = 0 ;
    memoryGagne = false ;

}

Memory::~Memory()
{
    nbCartes = 0 ;
    nbPairesTrouvees = 0 ;
    memoryGagne = false ;
    delete [] tabCartes ;
    delete [] grille ;

}

void Memory::afficherSolution() const
{
    int i;
    for (i=0; i<nbCartes; i++)
    {
        if(i==nbCartes/2)
        {
            cout<<endl;
        }
        cout<<" "<<grille[i].motif<<" ";
    }
    cout<<endl;
}

void Memory::repartirCartes()
{
    srand((int)time(NULL));

    int i ;
        for (i=0 ;i<nbCartes; i++) // pour chaque case du tableau (dont l'id de base est -1)
        {
            while(tabCartes[i].idCarte==-1) // tant que la carte n'a pas été placée
            {
                int aleatoire = (rand()%8) ;
                if(grille[aleatoire].motif=='n') // si la case n'est pas occupée
                    {
                        grille[aleatoire] = tabCartes[i] ; // on affecte la Carte à cette case
                        tabCartes[i].idCarte=aleatoire ; // on met à jour l'idCarte = la position de la carte dans la grille
                    }
            }
        }
}

void Memory::afficherChoix(int case1, int case2) const
{
    int i ;
    for (i=0 ; i<nbCartes ; i++)
    {
        if (i==nbCartes/2) cout<<endl ;

        // on affiche le motif d'une carte ssi elle a été trouvée
        // OU si c'est c1 ou c2
        if ( (grille[i].visible==true) or (i==case1-1)  or ( i==case2-1))
        {
            char motifCourant = grille[i].getMotif() ;
            cout<<" "<<motifCourant<<" " ;
        }
        else
        {
            cout<<" ? ";
        }

    }
}

void Memory::afficherMemory() const
{
    int i ;
    for (i=0 ; i<nbCartes ; i++)
    {
        if (i==nbCartes/2) cout<<endl ;


        if (grille[i].visible==true)
        {
            cout<<" "<<grille[i].motif<<" " ;
        }
        else
        {
            cout<<" ? ";
        }
    }
}

void Memory::retournerCartes(int case1, int case2)
{
    grille[case1].visible=true;
    grille[case2].visible=true;

    int i;
    for (i=0; i<nbCartes; i++)
    {
        if(tabCartes[i].idCarte==case1-1)
        {
            tabCartes[i].idCarte=true;
        }

        if(tabCartes[i].idCarte==case2-1)
        {
            tabCartes[i].idCarte=true;
        }
    }
}

void Memory::choixCartes(int case1, int case2)
{ // Attention, la boucle doit d'abord avoir vérifié que les cartes n'ont pas déjà été trouvées


    if(grille[case1-1].motif==grille[case2-1].motif) // si elles sont identiques
    {
        // on les retourne (dans le tableau et la grille)
        retournerCartes(case1-1, case2-1)  ;
        cout<<endl<<"Félicitations, tu as trouvé une paire ! "<<endl;
        nbPairesTrouvees++;
    }

    else
    {
        cout<<"Les cartes sont différentes :("<<endl;
    }

    if(nbPairesTrouvees==nbCartes/2) memoryGagne = true;
}

bool Memory::sontIdentiques(int case1, int case2)
{

    return (grille[case1-1].motif==grille[case2-1].motif) ;

}

int Memory::getNbPaires() const
{
    return nbPairesTrouvees ;
}

int Memory::getNbCartes() const
{
    return nbCartes ;
}

Carte* Memory::getTabCartes() const
{
    return tabCartes ;
}

Carte* Memory::getGrille() const
{
    return grille ;
}


void Memory::memoryBoucle()
{
    repartirCartes();
    while(!memoryGagne)
    {
        afficherMemory();
        cout<<endl;
        int i,j;

        do {
            cout<<"choisis la premiere carte :"<<endl;
            cin>>i;
            cout<<"choisis la seconde carte :"<<endl;
            cin>>j;

            if (grille[i-1].visible==true or grille[j-1].visible==true) cout<<"L'une des 2 cartes est deja retournee, recommence"<<endl;
            }while(grille[i-1].visible==true or grille[j-1].visible==true);
        cout<<endl;
        choixCartes(i,j);
        cout<<endl;
        afficherChoix(i,j);
        cout<<endl;
        cout<<endl;

        if(memoryGagne) cout<<"FELICITATIONS LE MEMORY EST GAGNE !"<<endl;
    }
}

void Memory::memoryTestRegression() const
{
//test constructeur par defaut
    Memory memTest;
    int nbc = memTest.getNbCartes();
    assert (nbPairesTrouvees == 0);
    assert (memoryGagne == false );

  // test de l'initialisation de la grille avec des cartes dont le motif par défaut est "n"

    int i;
    for (i=0;i<nbc;i++)
    {
        assert (grille[i].getId() == -1 );
        assert (grille[i].getMotif() == 'n');
    }



    //verifie que toutes les cartes ont été assignées a une place : aucune case de la grille a pour motif 'n' et aucun idCarte n'est égal à -1
    memTest.repartirCartes();
    Carte* tableau = memTest.getTabCartes() ;
    Carte* grilleTest = memTest.getGrille() ;
    for (i=0; i<nbc ; i++ )
    {
        assert(  grilleTest[i].motif!='n') ;
        assert(  tableau[i].idCarte!=-1) ;

    }
// Les autres fonctions reposant principalement sur de l'affichage, on les teste directement en lancant une partie
// Si il y a des erreurs, elles seront affichées grâce au assert
    cout<<"Test de régréssion effectué pour la classe Memory"<<endl;
}
