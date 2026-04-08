#include "../forfun.h"

void dSMDaSMO (int NbLign, int* AdPrCoefLi, int* NumCol, int* AdSuccLi,
               float* Matrice, float* SecMembre, int* NumDLDir, 
               float* ValDLDir, int* AdPrCoefLiO, int* NumColO, 
               float* MatriceO, float* SecMembreO){

    cdesse_ (&NbLign, AdPrCoefLi, NumCol, AdSuccLi, Matrice, SecMembre, NumDLDir, 
    ValDLDir, AdPrCoefLiO, NumColO, MatriceO, SecMembreO);
}