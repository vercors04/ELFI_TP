/*
* POUR COMPILER LE PROGRAMME ET CREER L'EXECUTABLE :
* -----------------------------------------
*
* -----------------------------------------
*/
#include "elementairesb.h"
#include "../ElementaireA/elementairesa.h"
#include "../Maillage/maillage.h"
#include "../Utilitaire/utilitaires.h"

int main (){
  int typel; // Type des elements du maillage
  int nbtng; // Nombre de noeuds géométriques
  int nbtel; // Nombre d'elements du maillage
  int nbneel; // Nombre de noeuds geometriques par element
  int nbaret; // Nombre d'aretes par element
  int** ngnel; // Numeros globaux des noeuds des elements
  int** nRefAr; // Numeros de reference associes aux aretes
  float** coord; // Coordonnees des noeuds geometriques

    char* ficmai = "../Donnees_1/car1x1t_1";

  if (lecfima(ficmai, &typel, &nbtng, &coord, &nbtel, &ngnel, &nbneel, &nbaret, &nRefAr)) return 1;
 
  float** coordElem = alloctab_f(nbneel,2);

  /*
  int t = 3, nbneel;
  switch (t) {
    case 1: nbneel = 4 ; break; // Quadrangles
    case 2: nbneel = 3 ; break; // Triangles
    default: printf("ERREUR : Cas possibles : \n t=1 : Quadrangles\n t=2 : Triangles");return 1;
  }
  */
  


  int nbRefD0 = 2;
  int nbRefD1 = 2;
  int nbRefF1 = 3;
  int nRefDom = 0;
  int numRefD0[] = {1,1};
  int numRefD1[] = {1,4};
  int numRefF1[] = {2,2,3};

  for (int i=0; i<nbtel; i++) {
    float** MatElem;
    float* SMbrElem;
    float* uDElem; // Indices i tq : NuDElem[i] = -1 si Dirichlet non homogène ; 0 sinon
    int* NuDElem; // Reperer les noeuds porteurs d'une condition de Dirichlet
    selectPts(nbneel, ngnel[i], coord, coordElem);

    cal1Elem (nRefDom, nbRefD0, numRefD0, nbRefD1, numRefD1, nbRefF1, numRefF1, typel, 
              nbneel, coordElem, nbaret, nRefAr[i], &MatElem, &SMbrElem, &NuDElem, &uDElem);

    impCalEl(i+1, typel, nbneel, MatElem, SMbrElem, NuDElem, uDElem);
    freetab(MatElem);
    freevec(SMbrElem);
    freevec(uDElem);
    freevec(NuDElem);
  }


  // Liberation de la memoire
  freetab(coord);
  freetab(ngnel);
  freetab(nRefAr);
  freevec(coordElem);



    return 0;
} 


