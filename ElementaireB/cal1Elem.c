#include "../Utilitaire/utilitaires.h"
#include "../ElementaireB/elementairesb.h"

void cal1Elem (int nRefDom, int nbRefD0, int* numRefD0, int nbRefD1, int* numRefD1, 
               int nbRefF1, int* numRefF1, int t, int nbneel, float** coordElem, int nbaret, 
               int* nRefArEl, float*** MatElem, float** SMbrElem, int** NuDElem, float** uDElem){

  *MatElem = calloctab_f (nbneel, nbneel);
  *SMbrElem = callocvec_f (nbneel);

  *NuDElem = allocvec_i (nbneel);
  for (int i = 0 ;  i< nbneel ; i++ ) (*NuDElem)[i] = 1;
  *uDElem = allocvec_f(nbneel);
  for (int i = 0 ;  i< nbneel ; i++ ) (*uDElem)[i] = 0;

  intElem (t, nbneel, coordElem, *MatElem, *SMbrElem);
  /*
  // Procedure intAret
  for (int i=0; i<nbneel; i++) {
    int couplePtsAret[2];
    numAret(t,nRefArEl[i],couplePtsAret);

  }
  */
}
