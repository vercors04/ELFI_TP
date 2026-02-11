#include "elementairesb.h"


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
