#include "Jeu.h"
#include "Memory.h"
#include <unistd.h>
#include <time.h>
#include <string>
#include <cassert>
using namespace std ;


//CLASSE JEU


Jeu::Jeu() //constructeur par defaut
{
     //fait appel aux constructeurs de Personnage et Memory
}

Jeu::~Jeu()
{

}

const Personnage& Jeu::getPersonnage() const{return personnage; }

const Memory& Jeu::getMemory() const {return memory; }

void Jeu::initPerso(const string & nomChoisi, const Couleur & couleurChoisie)
{
   personnage.setNom(nomChoisi);
   personnage.setCouleur(couleurChoisie);
}

void Jeu::jeuBoucle()
{
    int id = fork();
    time_t heure_depart = time(NULL);
    time_t heure_actuelle = time (NULL);
    while(!personnage.finPartie)
        {
            if (id == 0)
            {
                if (personnage.getActif() == false)
                {
                    heure_actuelle = time(NULL);
                    personnage.etat.diminuerEnergie(heure_depart,heure_actuelle);
					personnage.etat.diminuerAmusement(heure_depart,heure_actuelle);
                    personnage.etat.diminuerFaim(heure_depart,heure_actuelle);
                    personnage.finJeu();
                }
            }
            else
            {
                if (personnage.getActif()==false)
                {
                    char action;
                    cout<<endl<<"Occupez-vous de votre Capri!!"<<endl;
                    int faim = personnage.etat.getFaim();
                    int energie = personnage.etat.getEnergie();
                    int amusement = personnage.etat.getAmusement();
                    cout<<"Entrez une action afin d'interagir avec votre personnage!"<<endl<<"n = nourrir ;  d = dormir ; j = jouer"<<endl;
                    cout<<"Niveau de faim du Capri :"<<faim<<endl<<"Niveau de d'energie du Capri :"<<energie<<endl<<"Niveau d'amusement du Capri :"<<amusement<<endl;
                    cin>>action;
                    bool act = false;
                    while (!act)
                    {
                        switch(action)
                        {
                            case 'n' : nourrir(); act = true; break;
                            case 'd' : dormir(); act = true; break;
                            case 'j' : jouer(); act = true; break;
                            default : cout<<endl<<"L'action n'est pas possible ou non reconnu. Veuillez la ressaisir : ";
                            cin>>action;
                        }

                    }
                }
            }
        }
}


void Jeu::nourrir()
{
    if (personnage.etat.getFaim() + 1 > 5)
    {
        personnage.etat.faim = 5;
    }
    else
    {
        personnage.etat.faim++;
    }
    cout<<endl<<"Miam!! Votre Capri a bien mangé!!  ( ° o ° )";
    cout<<endl;
}

void Jeu::dormir()
{
    if (personnage.etat.getEnergie() + 1 > 5)
    {
        personnage.etat.energie = 5;
    }
    else
    {
        personnage.etat.energie++;
    }
    cout<<endl<<"Votre Capri a bien dormi!!  ( ^ 3 ^ )";
    cout<<endl;
}

void Jeu::jouer()
{
    personnage.actif = true;
    memory.memoryBoucle();
    if (personnage.etat.getAmusement() + 2 >= 5)
    {
        personnage.etat.amusement = 5;
    }
    else
    {
        personnage.etat.amusement = personnage.etat.amusement + 2;
    }
    cout<<"Votre Capri s'est bien amusé!!  ( ^ - ^ )";
    cout<<endl;
    personnage.actif = false;
}

