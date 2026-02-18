

void w(int nbneel, float* fctbas, float eltdif, float cofvar, float* vecelm){
  for (int i=0;i<nbneel;i++) {
    vecelm[i] = eltdif * cofvar * fctbas[i];
  }
}


void ADWDW (int nbeel, float** der_fctbas, float** invjacFk, float cofvar, float eltdif, float** matelm){
  // for (int i=0;i<nbeel;i++){
  //   cofvar * eltdif

  // }
}