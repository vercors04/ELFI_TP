/*
   Fonctions relatives au passage de SMO a profil.

   dSMOaLongPR. Fonction de calcul de la longueur de la matrice profil.

   dSMOaPR. Fonction de creation de la matrice profil.

*/
int dSMOaLongPR(int NbLign, int* AdPrCoefLiO, int* NumColO, float* MatriceO);

void dSMOaPR(int NbLign, int* AdPrCoefLiO, int* NumColO, float* MatriceO, int longProfilMat, int* Profil, float* MatProf);

int dSMOaLongPR2(int NbLign, int* AdPrCoefLiO, int* NumColO, float* MatriceO);

void dSMOaPR2(int NbLign,int* AdPrCoefLiO,  int* NumColO, float* MatriceO, int* Profil, float* MatProf);