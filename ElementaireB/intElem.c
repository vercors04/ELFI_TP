#include <stdio.h>
#include <math.h>
#include "../Utilitaire/utilitaires.h"
#include "../ElementaireA/elementairesa.h"
#include "../ElementaireB/elementairesb.h"

void pder_WI (int , float** , float** , float** );

void intElem (int t, int nbneel, float** coordElem, float** matelm, float* vecelm){
    int q = q_associe(t);

    float detJFK_abs;
    float eltdif;
    float cofvar_zz;
    float cofvar_f;

    float* valFctBase = allocvec_f(2);
    float* Fkx = allocvec_f(2);
    float* poids = allocvec_f(q);

    float** valDerFctBase = alloctab_f(nbneel,2);
    float** matJac = alloctab_f(2,2);
    float** invMatJac = alloctab_f(2,2);
    float** dpfctbas = alloctab_f(nbneel,2);
    float** cofvar = alloctab_f(2,2);

    // Boucle qui parcours tous les points et poids de quadrature
    for (int i=0; i<q ; i++){

        // Fonction de base au point de quadrature courant
        calFbase(t, coordElem[i], valFctBase); 

        // Sert a calculer les points de quadrature de l'element courant
        transFK(nbneel, coordElem, valFctBase, Fkx);

        // Derivees des fonctions de base sur le point de quadrature courant
        calDerFbase(t, coordElem[i], valDerFctBase);

        // Matrice jacobienne 
        matJacob(nbneel, coordElem, d_associe(t), valDerFctBase, matJac);

        // Determinant de la matrice jacobienne
        detJFK_abs = fabs(invertM2x2(matJac, invMatJac));
        
        pder_WI(nbneel, valDerFctBase, invMatJac, dpfctbas);
        
        eltdif = poids[i] * detJFK_abs;
        
        cofvar_zz    = A00(Fkx);
        cofvar[0][0] = A11(Fkx);
        cofvar[0][1] = A12(Fkx);
        cofvar[1][0] = A12(Fkx);
        cofvar[1][1] = A22(Fkx);
        cofvar_f     = FOMEGA(Fkx);

        // Calcul de matelm et vecelm
        ADWDW(nbneel, dpfctbas, eltdif, cofvar, matelm);
        WW(nbneel, valFctBase, eltdif, cofvar_zz, matelm);
        W(nbneel, valFctBase, eltdif, cofvar_f, vecelm);

    }
}


/*
Creation d'une matrice avec pour chaque ligne correspondant à un noeud les dérivée partielle en ce 
noeud * la colonne associé à alpha (1 ou 2) de l'inverse de la matrice jacobienne de la transformée Fk 
*/
void pder_WI (int nbneel, float** der_fctbas, float** invMatJac, float** dpfctbas){
  for (int i=0 ; i<nbneel; i++) {
      dpfctbas[i][0] = der_fctbas[i][0] * invMatJac[0][0] + der_fctbas[i][1] * invMatJac[1][0];
      dpfctbas[i][1] = der_fctbas[i][0] * invMatJac[0][1] + der_fctbas[i][1] * invMatJac[1][1];
  }
}





