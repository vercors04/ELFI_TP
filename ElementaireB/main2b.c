/*
* POUR COMPILER LE PROGRAMME ET CREER L'EXECUTABLE :
* -----------------------------------------
* gcc ElementaireB/fct_def_pb.c ElementaireB/main2b.c ElementaireB/impcalel.c ElementaireB/ww.c tab.c -o main2b.exe
* -----------------------------------------
*/

#include "elementairesb.h"


int main (){

    int t = 3, nbneel;
    switch (t) {
    case 1: nbneel = 4 ; break; // Quadrangles
    case 2: nbneel = 3 ; break; // Triangles
    default: printf("ERREUR : Cas possibles : \n t=1 : Quadrangles\n t=2 : Triangles");return 1;
    }



    return 0;
} 


