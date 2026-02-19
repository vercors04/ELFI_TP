void ADWDW (int nbneel, float** dpfctbas, float** cofvar, float eltdif, float** matelm){
  float som1, som2, som3, som4;
  for (int i=0; i<nbneel; i++) {
    for (int j=0; j<nbneel; j++) {
      // Calcul de la double somme alpha beta
      som1 = cofvar[0][0] * dpfctbas[i][0] * dpfctbas[j][0] ; //alpha = 1 , beta = 1
      som2 = cofvar[0][1] * dpfctbas[i][0] * dpfctbas[j][1] ; //alpha = 1 , beta = 2
      som3 = cofvar[1][0] * dpfctbas[i][1] * dpfctbas[j][0] ; //alpha = 2 , beta = 1
      som4 = cofvar[1][1] * dpfctbas[i][1] * dpfctbas[j][1] ; //alpha = 2 , beta = 2

      matelm[i][j] += eltdif * (som1 + som2 + som3 + som4); 
    }
  }
}

/*
 * cofvar : matrice 2x2 de la forme suivante :  A00 A01
 *                                              A10 A11
 *
 * dpfctbas : matrice qx2 de la forme suivante :  dw1/dx1 ; dw1/dx2
 *                                                dw2/dx1 ; dw2/dx2
 *                                                ...     ;
 *                                                dwq/dx1 ; dwq/dx2
 *
/*
 

/*
creation d'une matrice avec pour chaque ligne correspondant à un noeud les dérivée partielle en ce 
noeud * la colonne associé à alpha (1 ou 2) de l'inverse de la matrice jacobienne de la transformée Fk 
void pder_WI (int nbneel, float** der_fctbas, float** invjacob, float** res){
  for (int i=0 ; i<nbneel; i++) {
      res [i][0]=der_fctbas[i][0] * invjacob [0][0] + der_fctbas[i][1] * invjacob [1][0];
      res [i][1]=der_fctbas[i][0] * invjacob [0][1] + der_fctbas[i][1] * invjacob [1][1];
  }
}
*/
