#include "../Utilitaire/utilitaires.h"
#include "../ElementaireA/elementairesa.h"
#include "../ElementaireB/elementairesb.h"

void pder_WI (int, float** , float**, float**);

void intElem (int t, int nbneel, float** coordElem, float** matelm, float* vecelm){
    int q = q_associe(t);

    float det, eltdif;

    float* valFctBase = allocvec_f (nbneel);
    float* Fkx = allocvec_f (2);
    float* poids = allocvec_f (q);

    float** valDerFctBase = alloctab_f (nbneel,2);
    float** matJac = alloctab_f (2,2);
    float** invMatJac = alloctab_f (2,2);
    float** points = alloctab_f(q,2);
    float** cofvar = alloctab_f (2,2);
    float** dpfctbas = alloctab_f (nbneel, 2);

    //poid associe au point de quadrature
    ppquad(t, poids, points);

    for (int i=0; i<q ; i++){

        // Fonction de base au point de quadrature courant
        calFbase (t, points[i], valFctBase); 

        // Calcul des points de quadrature de l'element courant
        transFK (nbneel, coordElem, valFctBase, Fkx);

        // Valeur du coeficient variant en fonction du point de quadrature courant (non necessaire pour le moment)
        cofvar[0][0]=A11(Fkx);
        cofvar[0][1]=A12(Fkx);
        cofvar[1][0]=A12(Fkx);
        cofvar[1][1]=A22(Fkx);

        // Derivees des fonctions de base sur le point de quadrature courant
        calDerFbase (t, points[i], valDerFctBase);

        // Matrice jacobienne 
        matJacob(nbneel, coordElem, d_associe(t), valDerFctBase, matJac);

        // Determinant de la matrice jacobienne
        det = invertM2x2(matJac, invMatJac);

        // Element differentiel * poid au point de quadrature courant
        eltdif = poids[i]*fabs(det);

        // Appel de WW
        WW(nbneel, valFctBase, eltdif, A00(Fkx), matelm);

        // Appel ADWDW
        pder_WI (nbneel, valDerFctBase, invMatJac, dpfctbas);
        ADWDW (nbneel, dpfctbas, eltdif, cofvar, matelm);

        // Appel de W
        W(nbneel, valFctBase, eltdif, FOMEGA(Fkx), vecelm);

    }

    freevec(valFctBase);
    freevec(Fkx);
    freevec(poids);
    
    freetab(valDerFctBase);
    freetab(matJac);
    freetab(invMatJac);
    freetab(points);
    freetab(cofvar);
    freetab(dpfctbas);
}


/* Fonction aidant au calcul de ADWDW
 * ---------------------------------------------------------------------------------------
 * @param[in] nbneel : nombre de noeuds de l'element
 * @param[in] der_fctbas : derivee des fonctions de base au point de quadrature courant
 * @param[in] invjacob : inverse de la matrice jacobienne au point de quadrature courant
 *
 * @param[out] dpfctbas : derivee partielle des fonctions de base au points de quadrature courant *  la 
 * colonne associé à alpha (1 ou 2) de l'inverse de la matrice jacobienne de la transformée Fk
 * ---------------------------------------------------------------------------------------
*/
void pder_WI (int nbneel, float** der_fctbas, float** invjacob, float** dpfctbas){
  for (int i=0 ; i<nbneel; i++) {
      dpfctbas [i][0]=der_fctbas[i][0] * invjacob [0][0] + der_fctbas[i][1] * invjacob [1][0];
      dpfctbas [i][1]=der_fctbas[i][0] * invjacob [0][1] + der_fctbas[i][1] * invjacob [1][1];
  }
}