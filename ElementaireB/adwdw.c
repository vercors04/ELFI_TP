void ADWDW (int nbneel, float** pderWi, float** cofvar, float eltdif, float** matelm){
  float som1, som2, som3, som4;
  for (int i=0; i<nbneel; i++) {
    for (int j=0; j<nbneel; j++) {
      //calcul de la somme dans l'intégrale
      som1+=cofvar[0][0] * pderWi [i][0] * pderWi [j][0] ; //alpha = 0 , beta = 0
      som2+=cofvar[0][1] * pderWi [i][0] * pderWi [j][1] ; //alpha = 0 , beta = 1
      som3+=cofvar[1][0] * pderWi [i][1] * pderWi [j][0] ; //alpha = 1 , beta = 0
      som4+=cofvar[1][1] * pderWi [i][0] * pderWi [j][1] ; //alpha = 1 , beta = 1
      //on pourrait limite faire toutes les sommes d'un coup sur une grosses ligne
      //a partir de la jsp je dois bouger matelm me soule je capte pas
      float som = 0.0f;
      som = som1 + som2 + som3 + som4;
      matelm [i][j]+=eltdif * som; 
    }
  }
}

/*creation d'une matrice avec pour chaque ligne correspondant à un noeud les dérivée partielle en ce 
noeud * la colonne associé à alpha (1 ou 2) de l'inverse de la matrice jacobienne de la transformée Fk */
void pder_WI (int nbneel, float** der_fctbas, float** invjacob, float** res){
  for (int i=0 ; i<nbneel; i++) {
      res [i][0]=der_fctbas[i][0] * invjacob [0][0] + der_fctbas[i][1] * invjacob [1][0];
      res [i][1]=der_fctbas[i][0] * invjacob [0][1] + der_fctbas[i][1] * invjacob [1][1];
  }
}