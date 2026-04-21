/*
* POUR COMPILER LE PROGRAMME ET CREER L'EXECUTABLE :
* -----------------------------------------
* cd Executables
* ./main2b.sh
* -----------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "../2b_ElementaireB/elementairesb.h"
#include "../2a_ElementaireA/elementairesa.h"
#include "../1_Maillage/maillage.h"
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

  char* ficmai = "../Donnees_1/car3x3t_3";

  if (lecfima(ficmai, &typel, &nbtng, &coord, &nbtel, &ngnel, &nbneel, &nbaret, &nRefAr)){printf("erreur lecture du fichier de maillage");
    return 1;
  } 

  float** coordElem = (float**) malloc(nbneel * sizeof(float*));

  int nbRefD0 = 1;
  int nbRefD1 = 1;
  int nbRefF1 = 2;
  int nRefDom = 0;
  int numRefD0[] = {1};
  int numRefD1[] = {4};
  int numRefF1[] = {2,3};

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
  free(coordElem);



    return 0;
} 


