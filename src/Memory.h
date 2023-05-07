#ifndef CARTE_H_INCLUDED
#define CARTE_H_INCLUDED

class Carte
{
    /**
    *@brief Memory et JeuModeGraphique sont des classes amies de Carte.
    */
    friend class Memory ;
    friend class JeuModeGraphique ;

    private:

    /**
    *@param La donnée membre idCarte est un entier représentant l'identifiant d'une carte, qui lui-même correspond à sa position dans la grille durant une partie
    *du Memory. Cela permettra d'identifier une carte de manière unique au cours de la partie.
    *@param La donnée membre visible est un booléen indiquant si le motif de la carte est visible par le joueur ou non. Un motif est visible si la paire de la carte
    * correspondante a été trouvée et donc retournée par le joueur.
    *@param La donnée membre motif, de type caractère correspond au motif figurant sur la carte dans la version texte.
    */
    int idCarte;
    bool visible;
    char motif ;

    public :

    /**
    *@brief Constructeur à paramètres de la classe Carte : initialisation d'une carte avec le motif passé en paramètre.
    * @param Le paramètre monMotif est de type caractère correspond au motif que l'on souhaite attribuer à la carte et est passé par copie.
    */
    Carte(char monMotif) ;

    /**
    *@brief Constructeur par défaut de la classe Carte : initialisation du motif de la carte à "0", initilisation du booléen visible à false et de l'identifiant idCarte à -1.
    */
    Carte() ;

    /**
    *@brief Destructeur de la classe Carte : réinitialisation de toutes les données membres.
    */
    ~Carte() ;

    /**
    *@brief Surcharge de l'opérateur d'affectation de la classe Carte.
    *@param L'objet c2 qui est de type Carte, passé par copie, correspond à la carte que l'on souhaite affecter à l'instance courante.
    *@return Retourne une donnée de type Carte.
    */
    Carte& operator = (const Carte &c2) ;

    /**
    *@brief Accesseur : récupère la donnée membre idCarte.
    *@return La fonction retourne un entier correspondant à l'identifiant de la carte.
    */
    int getId() const;

    /**
    *@brief Accesseur : récupère la donnée membre motif.
    *@return La fonction retourne un caractère correspondant au motif de la carte.
    */
    char getMotif() const;

    /**
    *@brief Accesseur : récupère la donnée membre visible.
    *@return La fonction retourne un booléen correspondant à la donnée membre visible de la carte.
    */
    bool getVisible() const;

    /**
    *@brief Mutateur : modifie le booléen visible de la Carte.
    *@param Le paramètre vis, passé par copie, est un booléen (0 ou 1).
    */
    void setVisible(bool vis) ;

    /**
    *@brief La procédure effectue une série de tests vérifiant que la classe fonctionne et que les données membres de l'objet sont conformes.
    */
    void carteTestRegression();

};

#endif // CARTE_H_INCLUDED

//CLASSE MEMORY

#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

class Memory
{
    /**
    *@brief JeuModeTexte, Jeu et Carte sont des classes amies de Memory.
    */
    friend class Carte ;
    friend class Jeu ;
    friend class JeuModeGraphique ;

    private :

    /**
    *@param La donnée membre nbCartes est un entier indiquant le nombre de cartes présent dans tabCartes.
    *@param La donnée membre tabCartes est un tableau de Cartes alloué sur le tas. Dans ce tableau, les cartes seront rangées par paire. tabCartes sera donc invisible au joueur.
    *@param La donnée membre grille est un tableau statique 1D, alloué dynamiquement sur le tas, correspondant à la grille de jeu, visible par le joueur au cours d'une partie, qui contient des Carte desordonnées.
    *@param La donnée membre nbPairesTrouvees est un entier positif indiquant le nombre de paires trouvées par l'utilisateur.
    *@param La donnée membre memoryGagne est un booléen indiquant si la partie est gagnée ou non. Une partie est gagnée lorsque nbPairesTrouvees=NbCartes/2.
    */
    int nbCartes ;
    Carte* tabCartes ;
    Carte* grille  ;
    int nbPairesTrouvees;
    bool memoryGagne;

    public :

    /**
    *@brief Constructeur de la classe Memory : <br> - Initialisation de tabCartes en le remplissant avec des paires de cartes aux motifs '*','+','!' et '#'  <br> - Initialisation de la grille en la remplissant
    * avec des Carte dont le motif par défaut est "n"  <br> - Initialisation de nbCartes à 8 (modifiable par la suite) , nbPairesTrouvees et memoryGagne.
    */
    Memory();

    /**
    *@brief Destructeur de la classe Memory : destruction de grille et de tabCartes, nbCartes prend la valeur 0.
    */
    ~Memory();

	/**
  	*@brief La procédure afficherSolution permet d'affiche la grille du Memory ainsi que ses solutions.
	*/
    void afficherSolution() const;

    /**
    *@brief La procédure afficherGrille permet d'afficher la grille du Memory, en prenant en compte les deux dernières cartes choisies par le joueur.
    *@brief En effet, même si deux cartes ne sont pas identiques, elles doivent temporairement être rendues visibles dans la grille.
    * On affichera pour chaque carte de la grille, soit le motif de la carte, soit le caractère "?", indiquant qu'une carte n'est pas visible,
    * en insérant des sauts de lignes aux moments adéquats.
    *@param Les paramètres c1 et c2 sont des paramètres formels de la procédure et sont de type Carte passés par copie.
    */
    void afficherChoix(int case1, int case2) const ;

	/**
	*@brief La procédure afficherMemory permet d'afficher la grille du Memory. Les motifs des paires de cartes trouvées par le joueur seront visibles
	*tandis que le caractère "?" représentera les cartes qui n'ont pas encore été trouvées.
	*/
    void afficherMemory() const;

    /**
    * @brief La procédure repartirCartes permet, en début de partie, de positionner chaque carte de tabCartes dans une case choisie aléatoirement de la grille,
    * en veillant à ce que deux Cartes ne se retrouvent pas à la même case. Après avoir positionné une carte, elle met à jour son idCarte
    * (qui indique sa position dans la grille).
    */
    void repartirCartes() ;

    /**
    *@brief La procédure retournerCartes  permet de mettre à jour le booléen "visible" de deux cartes,
    * afin qu'elles puissent être affichées de manière permanente par la suite de la partie.
    *@param Les paramètres c1 et c2 sont des paramètres formels de la procédure et sont de type entier passés par copie. Ils correspondent aux indices des positions des deux cartes
    * choisies dans la grille.(L'utilisateur compte à partir de 1, il faut donc soustraire 1 à ses choix d'indice pour les passer en paramètres de procédure).
    */
    void retournerCartes(int case1, int case2);

    /**
    *@brief La procédure choixCartes permet au joueur de choisir deux cartes qu'il souhaitera retourner. <br>
    *@brief Si elles sont identiques, on fait appel à la fonction retournerCarte. Un message de succès ou d'échec sera également affiché
    * Attention, le joueur ne doit pas pouvoir choisir une carte dont il a déjà trouvé la paire antérieurement dans la partie.
    *@param Les paramètres c1 et c2 sont des paramètres formels de la procédure et sont de type entier passés par copie. Ils correspondent aux indices des positions des deux cartes
    * choisies dans la grille.(L'utilisateur compte à partir de 1, il faut donc soustraire 1 à ses choix d'indice pour les passer en paramètres de procédure).
    */
    void choixCartes(int case1, int case2);

    /**
     * @brief la fonction sontIdentiques détermine si deux cartes ont le même motif.
     * @param Les paramètres c1 et c2 sont des paramètres formels de la procédure et sont de type entier passés par copie. Ils correspondent aux indices des positions des deux cartes
    * choisies dans la grille.(L'utilisateur compte à partir de 1, il faut donc soustraire 1 à ses choix d'indice pour les passer en paramètres de procédure).
     * @return sontIdentiques renvoie un booléen indiquant si les cartes sont identiques ou non.
     */
    bool sontIdentiques(int case1, int case2) ;

    /**
    *@brief La procédure memoryBoucle permet de lancer une partie de memory.
    */
    void memoryBoucle();

    /**
    *@brief Accesseur : récupère la donnée membre nbPairesTrouvees.
    *@return La fonction retourne un entier positif.
    */
    int getNbPaires() const;

    /**
    *@brief Accesseur : récupère la donnée membre nbCartes.
    *@return La fonction retourne un entier positif.
    */
    int getNbCartes() const;

    /**
    *@brief Accesseur : retourne le tableau de cartes du Memory.
    *@return La valeur de retour est donc le pointeur sur Carte tabCartes, c'est-à-dire l'adresse du tas sur laquelle se trouve le tableau.
    */
    Carte* getTabCartes() const ;

    /**
    *@brief Accesseur : retourne la grille du Memory (plus précisément le pointeur sur Carte grille).
    *@return La valeur de retour est donc le pointeur sur Carte grille, c'est-à-dire l'adresse du tas sur laquelle se trouve la grille.
    */
    Carte* getGrille() const ;

    /**
    *@brief La procédure effectue une série de tests vérifiant que la classe fonctionne et que les données membres de l'objet sont conformes
    * <br> Le test de régréssion ne modifie pas les données membres, il effectue les tests sur un nouvel objet de la classe.
    */
    void memoryTestRegression() const ;
};

#endif // MEMORY_H_INCLUDED
