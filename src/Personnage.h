#include <string>

using namespace std;

//CLASSE ETAT

#ifndef ETAT_H_INCLUDED
#define ETAT_H_INCLUDED

class Etat
{
    /**
    *@brief JeuModeTexte, Personnage et Jeu sont des classes amies de Etat.
    */
    friend class Jeu;
    friend class Personnage;
    friend class JeuModeGraphique;

    private :

    /**
    *@param Les données membres faim, energie et amusement sont des entiers positifs compris entre 0 et 5 définissant l'état de faim, d'énergie et d’amusement du Capri.
    */
    unsigned int faim, energie, amusement;

    public:

    /**
    *@brief Constructeur de la classe Etat : initialise chaque état à 1.
    */
    Etat();

    /**
    *@brief Destructeur de la classe Etat.
    */
    ~Etat();


    /** @brief Accesseur : récupère la donnée membre faim du personnage.
    *@return La fonction retourne un entier positif compris entre 0 et 5.
    */
    unsigned int getFaim() const ;

    /**
    *@brief Accesseur : récupère la donnée membre energie du personnage.
    *@return La fonction retourne un entier positif compris entre 0 et 5.
    */
    unsigned int getEnergie() const ;

    /**
    *@brief Accesseur : récupère la donnée membre amusement du personnage.
    *@return La fonction retourne un entier positif compris entre 0 et 5.
    */
    unsigned int getAmusement() const ;

    /**
    *@brief Mutateur : modifie la donnée membre amusement du personnage.
    *@param am est un paramètre formel de la fonction et est un entier positif compris entre 0 et 5 passé par copie.
    */
   	void setAmusement(unsigned int am);

    /**
    *@brief Procédure diminuant la valeur de l'état de faim au cours du temps.
    *@brief <br> Celle-ci sera appelée en boucle tout au long d'une partie, afin de faire diminuer la faim environ toutes les 10 minutes.
    *@param Les paramètres heure_debut et heure_fin sont des paramètres de la bibliothèque time et correspondent respectivement à l'heure de début
    * d'une partie et à l'heure courante. Afin qu'ils puissent se synchroniser avec le temps réel, ces paramètres sont passés en mode
    * donnée-résultat. La condition est donc qu'ils doivent avoir été déclarés dans la boucle de jeu avant l'appel de la fonction.
    */
    void diminuerFaim(time_t &heure_debut, time_t &heure_actuelle);

    /**
    *@brief Procédure diminuant la valeur de l'état d'énergie au cours du temps.
    *@brief <br> Celle-ci sera appelée en boucle tout au long d'une partie, afin de faire diminuer l'énergie environ toutes les 10 minutes.
    *@param Les paramètres heure_debut et heure_fin sont des paramètres de la bibliothèque time et correspondent respectivement à l'heure de début
    * d'une partie et à l'heure courante. Afin qu'ils puissent se synchroniser avec le temps réel, ces paramètres sont passés en mode
    * donnée-résultat. La condition est donc qu'ils doivent avoir été déclarés dans la boucle de jeu avant l'appel de la fonction.
    */
    void diminuerEnergie(time_t &heure_debut, time_t &heure_actuelle);

    /**
    *@brief Procédure diminuant la valeur de l'état d'amusement au cours du temps.
    *@brief <br> Celle-ci sera appelée en boucle tout au long d'une partie, afin de faire diminuer l'amusement environ toutes les 10 minutes.
    *@param Les paramètres heure_debut et heure_fin sont des paramètres de la bibliothèque time et correspondent respectivement à l'heure de début
    * d'une partie et à l'heure courante.  Afin qu'ils puissent être synchronisés avec le temps réel par la fonction, ces paramètres sont passés en mode
    * donnée-résultat. La condition est donc qu'ils doivent avoir été déclarés dans la boucle de jeu avant l'appel de la fonction.
    */
    void diminuerAmusement(time_t &heure_debut, time_t &heure_actuelle);

    /**
    *@brief Effectue une série de tests vérifiant que la classe fonctionne et que les données membres de l'objet sont conformes.
    */
    void etatTestReg();
};


#endif // ETAT_H_INCLUDED

//CLASSE COULEUR

#ifndef COULEUR_H_INCLUDED
#define COULEUR_H_INCLUDED

class Couleur
{
    /**
    *@brief Personnage est une classe amie de Couleur.
    */
    friend class Personnage ;

    private :

	/**
	*@brief Les données membres rouge,vert et bleu sont de type caractère non signé et réprésentent les composantes de la couleur, leur valeur est comprises entre 0 et 255.
	*/
  	unsigned char rouge,vert,bleu;

    public :

	/**
   	*@brief Constructeur  par défaut de la classe : initialise par défaut une couleur blanche.
   	*/
    Couleur();

   	/**
  	*@brief Constructeur de la classe: initialise rouge,vert,bleu avec les paramètres.
   	*@param nr, nv et nb sont les paramètres formels de la fonction et sont passés par copie de type caractère non signé.
   	*/
    Couleur(unsigned char nr, unsigned char nv, unsigned char nb);

   	/**
   	*@brief Accesseur : récupère la composante rouge de la couleur.
   	*@return La fonction retourne un caractère non signé compris entre 0 et 255 qui est la valeur de la donnée membre rouge.
   	*/
   	unsigned char getRouge() const;

   	/**
   	*@brief Accesseur : récupère la composante verte de la couleur.
   	*@return La fonction retourne un caractère non signé compris entre 0 et 255 qui est la valeur de la donnée membre vert.
   	*/
   	unsigned char getVert() const;

    /**
    *@brief Accesseur : récupère la composante bleue de la couleur.
    *@return La fonction retourne un caractère non signé compris entre 0 et 255 qui est la valeur de la donnée membre bleu.
    */
   	unsigned char getBleu() const;

    /**
    *@brief Mutateur : modifie la composante rouge de la couleur.
    *@param nr est un paramètre formel de la fonction et est de type caractère non signé compris entre 0 et 255 passé par copie.
    */
   	void setRouge(unsigned char nr);

    /**
    *@brief Mutateur : modifie la composante verte de la couleur.
	*@param nv est un paramètre formel de la fonction et est de type caractère non signé compris entre 0 et 255 passé par copie.
    */
   	void setVert(unsigned char nv);

    /**
    *@brief Mutateur : modifie la composante rouge de la couleur.
	*@param nb est un paramètre formel de la fonction et est de type caractère non signé compris entre 0 et 255 passé par copie.
    */
    void setBleu(unsigned char nb);

    /**
    *@brief choisirCouleur() est une procédure qui demande à l'utilisateur de choisir entre plusieurs noms de couleurs spécifiques (rose, rouge, violet...)
    * et attribue les composantes r,g,b de la couleur choisie aux données membres de l'instance.
	*/
    void choisirCouleur();
};

#endif // COULEUR_H_INCLUDED

//CLASSE PERSONNAGE

#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED

class Personnage

{
    /**
    *@brief Etat, Jeu, Couleur et JeuModeGraphique sont des classes amies de Jeu.
    */
    friend class Etat ;
    friend class Jeu ;
    friend class Couleur ;
    friend class JeuModeGraphique;

    private :

    /**
    *@brief La donnée membre nom est une chaîne de caractères représentant le nom du personnage.
    *@brief La donnée membre couleur est de type Couleur.
    *@brief La donnée membre etat est de type Etat.
    *@brief Les données membres actif,vivant et finPartie sont des booléens représentant respectivement si le personnage est actif, s'il est vivant et si la partie est terminée.
    */
    string nom;
    Couleur couleur;
    Etat etat;
    bool actif,vivant,finPartie;

    public :

    /**
    *@brief Constructeur de la classe Personnage.
    */
    Personnage();

    /**
    *@brief Constructeur de la classe Personnage : initialise les données membres nom, couleur et les booléens.
    *@param nom est une chaîne de caractères et couleur est de type Couleur, ce sont les paramètres formels de la fonction et sont passés par copie.
    */
    Personnage(const string &nom, const Couleur &couleur);

    /**
    *@brief Destructeur de la classe Personnage : mise à jour des booléens.
    */
    ~Personnage();

    /**
    *@brief Accesseur : récupère la donnée membre nom du personnage.
    *@return La fonction retourne une chaîne de caractères.
    */
    string getNom() const;

    /**
    *@brief Accesseur : récupère la donnée membre actif du personnage.
    *@return La fonction retourne un booléen.
    */
    bool getActif() const;

    /**
    *@brief Accesseur : récupère la donnée membre vivant du personnage.
    *@return La fonction retourne un booléen.
    */
    bool getVivant() const;

    /**
    *@brief Mutateur : modifie le nom du personnage.
    *@param nomChoisi est le nouveau nom choisi par l'utilisateur. Il est passé en mode donnée.
    */
    void setNom(const string &nomChoisi) ;

    /**
    *@brief Mutateur : modifie la couleur du personnage.
    *@param couleurChoisie est la nouvelle couleur choisie par l'utilisateur. Elle est passée en mode donnée.
    */
    void setCouleur(const Couleur &couleurChoisie) ;

    /**
    *@brief Procédure mettant fin à la partie si le personnage meurt ou si le joueur gagne.
    */
    void finJeu();

    /**
    *@brief Effectue une série de tests vérifiant que la classe fonctionne et que les données membres de l'objet sont conformes.
    */
    void personnageTestRegression();
};

#endif // PERSONNAGE_H_INCLUDED
