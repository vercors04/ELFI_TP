
void ADWDW (int nbneel, float** dpfctbas, float eltdif, float** cofvar, float** matelm){
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

