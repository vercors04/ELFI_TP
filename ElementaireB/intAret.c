#include "../Utilitaire/utilitaires.h"
#include "../ElementaireA/elementairesa.h"
#include "../ElementaireB/elementairesb.h"

void intAret (int nbneel, float** coordElem, float** coordAret, float** matelm, float* vecelm){
    int t = 3, q = 3; // Cas segment

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

    // Poids et points de quadrature associe au segment de reference
    ppquad(t, poids, points);

    for (int i=0; i<q ; i++){

        // Fonction de base au point de quadrature courant
        calFbase (t, points[i], valFctBase); 

        // Image du point de quadrature courant dans l'element courant
        transFK (nbneel, coordElem, valFctBase, Fkx);

        // Valeur du coeficient variant en fonction du point de quadrature courant (non necessaire pour le moment)
        cofvar[0][0] = A11(Fkx);
        cofvar[0][1] = A12(Fkx);
        cofvar[1][0] = A12(Fkx);
        cofvar[1][1] = A22(Fkx);

        // Derivees des fonctions de base sur le point de quadrature courant
        calDerFbase (t, points[i], valDerFctBase);

        // Matrice jacobienne 
        matJacob(nbneel, coordElem, 1, valDerFctBase, matJac);

        // Determinant de la matrice jacobienne
        det = invertM2x2(matJac, invMatJac);

        // Element differentiel * poid au point de quadrature courant
        eltdif = poids[i]*fabs(det);

        // Appel de WW
        WW(nbneel, valFctBase, eltdif, BN(Fkx), matelm);

        // Appel de W
        W(nbneel, valFctBase, eltdif, FN(Fkx), vecelm);

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
