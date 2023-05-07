#include "Personnage.h"
#include <string>

// main pour tester le module Personnage.

int main ()
{
    string nomtest = "test"; 
    
    // Test de régréssion de Etat 
    Etat E;
    E.etatTestReg();
    


    // Test de régréssion de Personnage
    Couleur couleurtest(0,0,0) ;
    Personnage P(nomtest,couleurtest);
    P.personnageTestRegression() ;

	return 0 ;
}

