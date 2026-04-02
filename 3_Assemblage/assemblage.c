#include "../Utilitaire/utilitaires.h"
#include "../2a_ElementaireA/elementairesa.h"
#include "../2b_ElementaireB/elementairesb.h"
#include "forfun.h"

void assemblage(int typel, int nbtng, float** coord, int nbtel, int** ngnel,
	              int nbneel, int nbaret, int** nRefAr, int nbRef[3], int nRefDom,
	              int numRefD0[], int numRefD1[], int numRefF1[], int NbLign,
                int NbCoef, float* Matrice, float* SecMembre,
                int* AdPrCoefLi, int* AdSuccLi, int* NumCol,
                float* ValDLDir, int* NumDLDir){

  float** coordElem = alloctab_f(nbneel,2);
  float* LowMat = &(Matrice)[NbLign];

  for (int i=1; i<NbLign+1; i++) NumDLDir[i-1]=1*i;
  // Boucle sur K dans Th
  for (int K=0; K<nbtel; K++) {
    float** MatElem;
    float* SMbrElem;
    float* uDElem; // Indices i tq : NuDElem[i] = -1 si Dirichlet non homogène
		               //                              0 sinon
    int* NuDElem;  // Reperer les noeuds porteurs d'une condition de Dirichlet
    int NextAd=1;
    selectPts(nbneel, ngnel[K], coord, coordElem);

    cal1Elem (nRefDom, nbRef[0], numRefD0, nbRef[1], numRefD1, nbRef[2], numRefF1,
	            typel, nbneel, coordElem, nbaret, nRefAr[K], &MatElem, &SMbrElem,
	            &NuDElem, &uDElem);

    impCalEl(K+1, typel, nbneel, MatElem, SMbrElem, NuDElem, uDElem);

    for (int i=1; i<nbneel+1; i++){
      int I = ngnel[K][i-1];

      for (int j=1; j<i; j++){
        int J = ngnel[K][j-1];

	      // I_tilde = max(I,J) ; J_tilde = min(I,J)
	      int I_tilde = I, J_tilde = J;
	      if (J>I) {
	        I_tilde = J;
	        J_tilde = I;
	      }

	      assmat_(&I_tilde, &J_tilde, &MatElem[i-1][j-1], AdPrCoefLi, NumCol,
		            AdSuccLi, LowMat, &NextAd);
      }

      // Gestion de la partie diagonale
      Matrice[I-1] += MatElem[i-1][i-1];

      // Gestion du Second membre
      SecMembre[I-1] += SMbrElem [i-1];

      // Gestion des conditions de Dirichlet
      if (0==NuDElem[i-1]) NumDLDir[I-1] = 0;
      else if (-1==NuDElem[i-1]) {
        NumDLDir[I-1] = -I;
        ValDLDir[I-1] = uDElem[i-1];
      }
    }



    freetab(MatElem);
    freevec(SMbrElem);
    freevec(uDElem);
    freevec(NuDElem);
  }
}
