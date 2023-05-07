#include <iostream>
#include <string>
#include <time.h>
#include <cassert>
#include "Personnage.h"

using namespace std;

//CLASSE ETAT

Etat::Etat()
{
    faim=1;
    energie=1;
    amusement=1;
}

Etat::~Etat()
{
    faim=0;
    energie=0;
    amusement=0;
}

unsigned int Etat::getFaim() const
{
    return faim;
}

unsigned int Etat::getEnergie() const
{
    return energie;
}

unsigned int Etat::getAmusement() const
{
    return amusement;
}

void Etat::setAmusement(unsigned int am)
{
    if (am<=5){amusement=am;}
    else {amusement=5;}
}

//Utilisation des fonctions dans la boucle de jeu, tant que le jeu n'est pas fini, diminuer tourne en boucle

void Etat::diminuerFaim(time_t &heure_depart, time_t &heure_actuelle)
{
/*Les variables heure_depart et heure_actuelle en D/R doivent avoir été initialisées AVANT = au début de la boucle de jeu.cpp */
    if (difftime(heure_actuelle,heure_depart) == 100) // Toutes les 10 minutes de jeu
    {
        faim -- ;
		cout<<"Niveau de faim du Capri :"<<faim<<endl<<"Niveau de d'energie du Capri :"<<energie<<endl<<"Niveau d'amusement du Capri :"<<amusement<<endl;
        heure_depart = time(NULL) ; // on réinitialise l'heure de départ pour mettre le compteur à zéro
    }

}

void Etat::diminuerEnergie(time_t &heure_depart, time_t &heure_actuelle)
{
    if (difftime(heure_actuelle,heure_depart) == 100)
    {
        energie -- ;
		cout<<"Niveau de faim du Capri :"<<faim<<endl<<"Niveau de d'energie du Capri :"<<energie<<endl<<"Niveau d'amusement du Capri :"<<amusement<<endl;
        heure_depart = time(NULL) ;
    }
}

void Etat::diminuerAmusement(time_t &heure_depart, time_t &heure_actuelle)
{
    if (difftime(heure_actuelle,heure_depart) == 100)
    {
        amusement -- ;
		cout<<"Niveau de faim du Capri :"<<faim<<endl<<"Niveau de d'energie du Capri :"<<energie<<endl<<"Niveau d'amusement du Capri :"<<amusement<<endl;
        heure_depart = time(NULL) ;
    }
}

void Etat::etatTestReg()
{
    Etat();
    unsigned int a, f, e;
    a=getAmusement();
    f=getFaim();
    e=getEnergie();
    assert((e>=0) && (e<=5));
    assert((f>=0) && (f<=5));
    assert((a>=0) && (a<=5));
    cout<<endl<<"-> Test de régréssion effectué pour la classe Etat"<<endl;
}

//CLASSE COULEUR

Couleur::Couleur()
{
    rouge = 0 ;
    vert = 0 ;
    bleu = 0 ;
}

Couleur::Couleur(unsigned char nr, unsigned char nv, unsigned char nb)
{
    rouge=nr;
    vert=nv;
    bleu=nb;
}

unsigned char Couleur::getRouge() const
{
    return rouge;
}

unsigned char Couleur::getVert() const
{
     return vert;
}

unsigned char Couleur::getBleu() const
{
    return bleu;
}

void Couleur::setRouge (unsigned char nr)
{
    rouge=nr;
}

void Couleur::setVert (unsigned char nv)
{
    vert=nv;
}

void Couleur::setBleu (unsigned char nb)
{
    bleu=nb;
}
void Couleur::choisirCouleur()
{
    char c;
    cout<<endl<<"Veuillez saisir une couleur parmis les 6 disponibles!"<<endl;
    cout<<"Couleurs disponibles : 1:blanc, 2:rose, 3:rouge, 4:bleu, 5:vert, 6:violet"<<endl;
    cout<<"Entrez la chiffre correspondant à la couleur : "<<endl;
    cin>>c;
    bool saisi;
    saisi = false;
    while(!saisi)
   {
       switch(c)
        {
            case '1' : rouge=255 ; vert=255; bleu=255;      saisi = true; break;
            case '2' : rouge=255 ; vert=153; bleu=255;      saisi = true; break;
            case '3' : rouge=255 ; vert=0;   bleu=0;        saisi = true; break;
            case '4' : rouge=0 ; vert=0; bleu=255;          saisi = true; break;
            case '5' : rouge=0 ; vert=255; bleu=0;          saisi = true; break;
            case '6' : rouge=102 ; vert=0; bleu=255; ;      saisi = true; break;
            default :cout<<"Cette couleur n'est pas disponible ou non reconnue :("<<endl;
                    cout<<"Veuillez la saisir à nouveau : ";
                    cin>>c;
                    break;
        }
    }
}

//CLASSE PERSONNAGE

Personnage::Personnage()
{
    nom = "no_name";
    Couleur blanc(255, 255, 255);
    couleur = blanc;
    actif = false ;
    vivant = true ;
    finPartie = false ;

}

Personnage::Personnage(const string &nv_nom, const Couleur &nv_couleur)
{
    nom = nv_nom ;
    couleur = nv_couleur ;
    actif = false ;
    vivant = true ;
    finPartie = false ;

}

Personnage::~Personnage()
{
    actif = false ;
    vivant = false ;
    finPartie = true ;
}

string Personnage::getNom() const
{
    return nom ;
}

bool Personnage::getActif() const
{
    return actif ;
}

bool Personnage:: getVivant() const
{
    return vivant ;
}

void Personnage::setNom(const string &nomChoisi)
{
    nom = nomChoisi ;
}

void Personnage::setCouleur(const Couleur &couleurChoisie)
{
    couleur.setRouge(couleurChoisie.getRouge()) ;
    couleur.setBleu(couleurChoisie.getBleu()) ;
    couleur.setVert(couleurChoisie.getVert()) ;
}


/* Il faudra aussi tester les conditions (etats=5/0)dans la boucle de jeu.cpp pour appeler cette
fonction au moment adéquat (pour qu'elle soit appelée automatiquement) */
void Personnage::finJeu()
{
    unsigned int faimCapri = etat.getFaim() ;
    unsigned int energieCapri = etat.getEnergie() ;
    unsigned int amusementCapri = etat.getAmusement() ;
// Cas où la partie est gagnée :

    if  ( (faimCapri==5) && (energieCapri==5) && (amusementCapri==5)  )
    {
        cout<<"Bravo, vous avez pris soin du Capri : la partie est gagnée ! ";
        finPartie=true ;
    }

// Cas où la partie se termine pour cause de mort du Capri
    if(faimCapri==0)
        {

            cout<<"Le capri "<<nom<<" est mort de faim : partie perdue :(";
            vivant = false ;
            finPartie=true ;
        }

 if(energieCapri==0)
        {

            cout<<"Le capri "<<nom<<" est mort de fatigue : partie perdue :(";
            vivant = false ;
            finPartie=true ;
        }

    if(amusementCapri==0)
        {
            cout<<"Le capri "<<nom<<" est mort d'ennui : partie perdue :(";
            vivant = false ;
            finPartie=true ;
        }
}


void Personnage::personnageTestRegression()
{

    // initialisation d'un personnage avec son nom et sa couleur :

    Couleur couleurTest(26,21,244) ;
    string nomPerso = "le_nom" ;
    Personnage persoTest(nomPerso,couleurTest) ;

    // vérification des données membres et des accesseurs


    string recupNom = persoTest.getNom() ;
    // comparaison de chaînes de caractères avec strcmp
    int comparaison = recupNom.compare("le_nom") ;
    assert(comparaison==0) ;

    unsigned char R = persoTest.couleur.getRouge() ;
    unsigned char G = persoTest.couleur.getVert() ;
    unsigned char B = persoTest.couleur.getBleu() ;

    assert(R==26) ;
    assert(G==21) ;
    assert(B==244) ;
    bool estActif = persoTest.getActif()  ;
    bool estVivant = persoTest.getVivant() ;
    assert(estActif ==false) ;
    assert(estVivant == true) ;


    // vérification de la fonction finJeu avec l'affichage des messages : d'abord test diminuer


    cout<<endl<<"-> Test de régréssion effectué pour la classe Personnage"<<endl;

}

