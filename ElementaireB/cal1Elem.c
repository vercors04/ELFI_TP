#include "../Utilitaire/utilitaires.h"

#include "../ElementaireA/elementairesa.h"
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
  
  // Procedure intAret
  for (int i=0; i<nbaret; i++) {

    if (nRefArEl[i]!=0){
      int couplePtsAret[2];

      // Cas Neumann/Fourier
      for (int k=0; k<nbRefF1; k++){
        if (nRefArEl[i]==numRefF1[k]) {
          numAret (t, i + 1, couplePtsAret);

          float** coordAret = malloc(2 * sizeof(float*));
          selectPts(2, couplePtsAret, coordElem, coordAret);

          float** matAret = alloctab_f(2, 2);
          float* vecAret = allocvec_f(2);
          intAret (coordAret, matAret, vecAret);

          //probablement pas a faire dans le TP2b - cause erreurs NaN dans le resultat 

/*
          (*SMbrElem)[couplePtsAret[0]-1]+=vecAret[0];
          (*SMbrElem)[couplePtsAret[1]-1]+=vecAret[1];

          (*MatElem)[couplePtsAret[0]-1][couplePtsAret[0]-1]+=matAret[0][0];
          (*MatElem)[couplePtsAret[0]-1][couplePtsAret[1]-1]+=matAret[0][1];
          (*MatElem)[couplePtsAret[1]-1][couplePtsAret[0]-1]+=matAret[1][0];
          (*MatElem)[couplePtsAret[1]-1][couplePtsAret[1]-1]+=matAret[1][1];
*/
         free(coordAret);
         freetab(matAret);
         freevec(vecAret);
        }
      }

      // Cas Dirichlet homogene
      for (int j=0; j<nbRefD0; j++){
        if (nRefArEl[i]==numRefD0[j]) {
          numAret (t, i + 1, couplePtsAret);

          (*NuDElem)[couplePtsAret[0] - 1] = 0;
          (*NuDElem)[couplePtsAret[1] - 1] = 0;
        }
     }

      // Cas Dirichlet non homogene
      for (int l=0; l<nbRefD1; l++){
        if (nRefArEl[i]==numRefD1[l]) {
          numAret (t, i + 1, couplePtsAret);

          (*NuDElem)[couplePtsAret[0] - 1] = -1;
          (*NuDElem)[couplePtsAret[1] - 1] = -1;

          float** coordAret = malloc(2 * sizeof(float*));
          selectPts(2, couplePtsAret, coordElem, coordAret);
          (*uDElem)[couplePtsAret[0] - 1] = UD(coordAret[0]);
          (*uDElem)[couplePtsAret[1] - 1] = UD(coordAret[1]);
          free(coordAret);
        }
      }

    }
  }
}
