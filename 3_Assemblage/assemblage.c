

void assemblage(int typel, int nbtng, float** coord, int nbtel, int** ngnel,
	              int nbneel, int nbaret, int** nRefAr, int nbRef[3], int nRefDom,
	              int numRefD0[], int numRefD1[], int numRefF1[], int NbLign,
                int NbCoef, float* Matrice, int* AdPrCoefLi, int* AdSuccLi,
                int* NumCol){

  float** coordElem = alloctab_f(nbneel,2);

  int nbRefD0 = 1;
  int nbRefD1 = 1;
  int nbRefF1 = 2;
  int nRefDom = 0;
  int numRefD0[] = {1};
  int numRefD1[] = {4};
  int numRefF1[] = {2,3};

  float* LowMat = &Matrice[nbLign];

  // Boucle sur K dans Th
  for (int K=0; K<nbtel; K++) {
    float** MatElem;
    float* SMbrElem;
    float* uDElem; // Indices i tq : NuDElem[i] = -1 si Dirichlet non homogène
		               //                              0 sinon
    int* NuDElem;  // Reperer les noeuds porteurs d'une condition de Dirichlet
    selectPts(nbneel, ngnel[K], coord, coordElem);

    cal1Elem (nRefDom, nbRef[0], numRefD0, nbRef[1], numRefD1, nbRef[2], numRefF1,
	            typel, nbneel, coordElem, nbaret, nRefAr[K], &MatElem, &SMbrElem,
	            &NuDElem, &uDElem);

    for (int i=1; i<nbneel+1; i++){
      int I = ngneel[K-1][i-1];

      for (int j=1; j<i-1; j++){
        int J = ngneel[K-1][j-1];
	      int I_tilde, J_tilde;
	
	      // I_tilde = max(I,J) ; J_tilde = min(I,J)
	      if (J<I) {
	        I_tilde = I; 
	        J_tilde = J;
	      }
	      else {
	        I_tilde = J;
	        J_tilde = I;
	      }

	      assmat_(&I_tilde, &J_tilde, &MatElem[i-1][j-1], AdPrCoefLi, NumCol, 
		            AdSuccLi, LMat, NextAd);
  
      }
      // Gestion de la partie diagonale
      
      // Gestion du Second membre
      
      // Gestion des conditions de Dirichlet

    }



    freetab(MatElem);
    freevec(SMbrElem);
    freevec(uDElem);
    freevec(NuDElem);
  }
    
}
