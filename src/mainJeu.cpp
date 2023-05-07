#include "Jeu.h"
#include "Personnage.h"
#include "Memory.h"
#include <pthread.h>
#include <string>
#include <iostream>
using namespace std ;

int main()
{
    Jeu J;
    string nom;
    Couleur couleurCapri;
    cout<<"Vous venez de trouver un oeuf de Capri, Felicitation!!"<<endl;
    cout<<"L'oeuf va bientôt eclore, depechez vous de donner un nom à votre capri!!"<<endl;
    cout<<"Entrez le nom de votre Capri : ";
    cin>>nom;
    cout<<endl<<"Il semblerait qu'il soit encore possible de choisir une couleur pour votre Capri!!"; 
    couleurCapri.choisirCouleur();
    J.initPerso(nom,couleurCapri);
    cout<<endl<<"Votre Capri vient de sortir de son oeuf!!Bienvenue "<<nom<<"!! Prenez bien soin de votre Capri!"<<endl;
    cout<<"( ^ o ^ )"<<endl;
    cout<<"N'oubliez pas de le nourrir et de jouer avec lui, mais laissez le aussi se reposer une fois de temps en temps ;)"<<endl;
    J.jeuBoucle(); 
    return 0 ;

}
