#include "../forfun.h"
#include "../Utilitaire/utilitaires.h"

void resolsyst(int NbLign, int LongMatProf, int* Profil, float* MatProf, float* SecMembre, float* Sol){
  
  float eps = 1.e-10; // Seuil de singularite

  float* DiagL = allocvec_f (NbLign);
  float* InfL  = allocvec_f (LongMatProf-NbLign); // ???

  // Decomposition de Cholesky
  ltlpr_(&NbLign, Profil, MatProf, MatProf + NbLign, &eps, DiagL, InfL);
  // Descente
  rsprl_(&NbLign, Profil, DiagL, InfL, SecMembre, Sol);
  // Remontee
  rspru_(&NbLign, Profil, DiagL, InfL, Sol, Sol);

  freevec (DiagL);
  freevec (InfL);
}
