#include "elementairesb.h"

float A11(float x){
  return 1.0f;
}

float A22(float x){
  return 1.0f;
}

float A12(float x){
  return 0.0f;
}

float A00(float x){
  return 1.0f;
}

float BN(float x){
  return 0.0f;
}

float FOMEGA(float x){
  return 1.0f;
}

float FN(float x){
  return 1.0f;
}

float UD(float* x){
  return 100.0f*x[0] + x[1];
}

void WW(int nbneel, float *fctbas, float eltdif, float cofvar, float **matelm) {
  int i, j;
  float coeff;

  for (i=0; i<nbneel; i++) {
    coeff = eltdif*cofvar*fctbas[i];
    for (j=0; j<nbneel; j++) {
      matelm[i][j] = matelm[i][j] + coeff*fctbas[j];
    }
  }
}


void impCalEl(int K, int typEl, int nbneel, float **MatElem, float *SMbrElem, int *NuDElem, float *uDElem) {
  int i, j;
  printf("\n");
  printf(" ELEMENT=%3d    DE TYPE=%5d    NB NOEUDS=%2d\n", K,typEl,nbneel);
  printf(" NuDElem   uDElem    SMbrElem    MatElem\n");
  for (i=0; i < nbneel; i++) {
    printf(" %6d %10.4e %10.4e", NuDElem[i],uDElem[i],SMbrElem[i]);
    for (j=0; j <= i; j++) { printf(" %10.4e", MatElem[i][j]); }
    printf("\n");
  }
}


