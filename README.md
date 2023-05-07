## PROJET CAPRI 

Ce projet a été réalisé dans le cadre de l'UE "Conception et Développement d'Applications" (LIFAP4) par :
- BALA Na'ilah - p2000525
- DIF Sirine - p2018973
- MAGASSA Fatoumata - p2008591


# Capri - Introduction du jeu  

Un Capri est un petit animal virtuel inspiré du tamagotchi. Dans ce jeu de simulation de vie artificielle, il s'agira de prendre soin d'un Capri en le nourrissant, en s'amusant avec lui et en le laissant se reposer. 

## Principe d'une partie 

- Pour commencer, cliquez sur l'oeuf qui vous plaît le plus afin de donner naissance à votre Capri. Une fois celui-ci rencontré, vous remarquerez qu'il est très affaibli. 
- Un Capri dispose en effet de trois niveaux d'états (faim, énergie et amusement), représentés par des jauges, qui, au début d'une partie sont respectivement à 1/5.
- C'est à vous d'y remédier ! Nourrissez et endormez votre Capri en cliquant sur les boutons correspondants. 
- En cliquant sur le bouton jouer, vous lancerez une partie du mini-jeu Memory pour distraire votre animal. 
- La partie est remportée lorsque le Capri est pleinement épanoui, c'est-à-dire lorsque ses trois niveaux d'états sont à 5/5. 
- Attention, si vous négligez votre Capri et que l'une de ses barres d'état se vide complètement, celui-ci rendra l'âme immédiatement. 

## Découpage des modules 

Le projet se divise en 4 modules : 

- Le module Personnage constitué de 3 classes qui correspondent respectivement aux fonctionnalités relatives à un personnage, à sa couleur ainsi qu’à son état. Les fichiers correspondants sont src/Personnage.h, src/Personnage.cpp et src/mainPersonnage.cpp, qui créent l'éxécutable bin/mainPersonnage, dans lequel est effectué le test de régression du module. 
- le module Memory qui est composé d’une classe cartes et d’une classe memory faisant usage de ces cartes. Les fichiers correspondants sont src/Memory.h, src/Memory.cpp et src/mainMemory.cpp, qui créent l'éxécutable bin/mainMemory, qui sert à lancer la boucle de jeu memory en mode texte et le test de régression du module.
- le module Jeu, qui permet de mettre en lien un personnage et son mini-jeu memory pour lancer une partie complète en mode texte. Les fichiers correspondants sont src/Jeu.h, src/Jeu.cpp et src/mainJeu.cpp, qui créent l'éxécutable bin/mainJeu.
- le module sdlJeu, qui permet de lancer la boucle de jeu en version graphique grâce à SDL2. Les fichiers correspondants sont src/sdlJeu.h, src/sdlJeu.cpp et src/mainSdlJeu.cpp, qui créent l'éxécutable bin/mainSdlJeu.



## Organisation des répertoires du projet 

L'ensemble des fichiers nécéssaires au projet est rangé dans le dossier 'tamagotchi', divisé en plusieurs sous-dossiers de la manière suivante : 

- src/ : Contient les fichiers sources d'extensions .h et .cpp de chaque module, y compris les programmes principaux (mainPersonnage.cpp, mainMemory.cpp, mainJeu.cpp, mainSdlJeu.cpp)
- bin/ : Contient les fichiers éxécutables, regénérés à chaque édition des liens . Ce dossier n'est donc pas géré par GIT. 
- obj/ : Contient les fichiers objets d'extension .o regénérés à chaque compilation. Ce dossier n'est donc pas géré par GIT. 
- data/ : Contient les assets de l'application, essentiels à la version graphique : images et son 
- doc/ : Contient le fichier doxyfile de la documentation Doxygen 
- makefile : le makefile fonctionnel, nécéssaire à la compilation du projet 
- Ce readme. 

## Lancer l'application 

La compilation et l'éxécution du projet s'effectuent systématiquement sous Linux, en terminal de commandes, grâce au makefile. On distingue deux programmes différents pour la version texte et la version graphique qui fait appel à la librairie externe SDL2. Il est donc nécéssaire de pré-installer cette dernière si vous souhaitez jouer en mode graphique. 

# en version texte 
Pour compiler puis éxecuter le jeu en mode texte, se placer dans le répertoire parent de src/ et taper les commandes suivantes : 
```
make 
./bin/mainJeu
```
# en version graphique  
Pour compiler puis éxecuter le jeu en mode graphique, se placer dans le répertoire parent de src/ et taper les commandes suivantes : 
```
make 
./bin/mainSdlJeu 
```

## Documentation du projet 
Le projet est documenté grâce à Doxygen. Pour générer la documentation : 
```
cd doc  
doxygen doxyfile 
```

## Crédits multimedia 
- Les dessins des personnages, du décor principal, des boutons et des oeufs de l'introduction ont été réalisés avec soin par Sirine DIF 
- Les montages des cartes du Memory graphique ont été réalisés par Fatoumata MAGASSA 
- Pour le reste (arrière-plans de l'introduction du jeu), il s'agit d'images libres de droits.
- Voici le lien vers la musique utilisée en arrière-plan du jeu : https://www.youtube.com/watch?v=1nomS1pYeZ0&list=RD1nomS1pYeZ0&start_radio=1 