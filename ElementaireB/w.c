

void w(int nbneel, float* fctbas, float eltdif, float cofvar, float* vecelm){
  for (int i=0;i<nbneel;i++) {
    vecelm[i] += eltdif * cofvar * fctbas[i];
  }
}


