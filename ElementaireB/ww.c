#include "elementairesb.h"

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
