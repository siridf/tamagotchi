#include <iostream>
#include <cassert>
#include "Personnage.h"
#include "Memory.h"

//CLASSE JEU

#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

class Jeu
{
    /**
    *@brief JeuModeTexte et JeuModeGraphique sont des classes amies de Jeu.
    */
    friend class JeuModeTexte ;
    friend class JeuModeGraphique ;

    private :

    /**
    *@param La donnée membre personnage est de type Personnage.
    *@param La donnée membre memory est de type Memory.
    */
    Personnage personnage;
    Memory memory;


    public :

    /**
    *@brief Constructeur de la classe Jeu.
    */
    Jeu();

    /**
    *@brief Destructeur de la classe Jeu.
    */
    ~Jeu();

    /**
    *@brief La procédure permet d'initialiser le nom et la couleur du personnage.
    *@param Le paramètre nomChoisi est un paramètre formel et est une chaîne de caractères passé par copie.
    *@param Le paramètre couleurChoisi est un paramètre formel et est de type Couleur passé par copie.
    */
    void initPerso(const string &nomChoisi, const Couleur &couleurChoisi);

    /**
    *@brief La procédure jeuBoucle permet de lancer la boucle de jeu.
    */
    void jeuBoucle();

    /**
    *@brief La procédure nourir permet d'ajouter +1 au niveau de faim du personnage après chaque appel.
    */
    void nourrir();

    /**
    *@brief La procédure jouer permet d'ajouter +2 au niveau d'amusement du personnage en faisant appel à la procédure memoryBoucle de la classe Memory.
    */
    void jouer();

    /**
    *@brief La procédure dormir permet d'ajouter +1 au niveau d'énergie du personnage après chaque appel.
    */
    void dormir();

    /**
    *@brief Accesseur : récupère la donnée membre personnage du jeu.
    *@return La fonction retourne une donnée qui est de type Personnage.
    */
    const Personnage& getPersonnage () const;

    /**
    *@brief Accesseur : récupère la donnée membre memory du jeu.
    *@return La fonction retourne une donnée qui est de type Memory.
    */
    const Memory& getMemory () const;

    /**
    *@brief La procédure effectue une série de tests vérifiant que la classe fonctionne et que les données membres de l'objet sont conformes.
    */
    void jeuTestRegression();
};

#endif // JEU_H_INCLUDED

//CLASSE JEUMODETEXTE

#ifndef JEUMODETEXTE_H_INCLUDED
#define JEUMODETEXTE_H_INCLUDED

class JeuModeTexte
{
    /**
    *@brief Jeu et JeuModeGraphique sont des classes amies de JeuModeTexte.
    */
    friend class Jeu;
    friend class JeuModeGraphique ;

    private :

    /**
    *@param La donnée membre jeu est de type Jeu.
    */
    Jeu jeu;

    public :

    /**
    *@brief Constructeur de la classe JeuModeTexte : fait appel au constructeur de la classe Jeu.
    */
    JeuModeTexte();

    /**
    *@brief Destructeur de la classe JeuModeTexte.
    */
    ~JeuModeTexte();

    /**
    *@brief La procédure jeuBoucleTxt permet de lancer la boucle de jeu en mode texte en faisant appel à la procédure jeuBoucle de la classe Jeu.
    */
    void jeuBoucleTxt();

};

#endif // JEUMODETEXTE_H_INCLUDED
