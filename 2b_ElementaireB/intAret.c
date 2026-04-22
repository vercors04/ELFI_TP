#include <math.h>
#include "../Utilitaire/utilitaires.h"
#include "../2a_ElementaireA/elementairesa.h"
#include "../2b_ElementaireB/elementairesb.h"

void intAret ( float** coordAret, float** matAret, float* vecAret){
 
    int t = 3, q = 3, nbneelAr =2; // Cas segment

    float det, eltdif;

    float* valFctBase = allocvec_f (nbneelAr);
    float* Fkx        = allocvec_f (2);
    float* poids      = allocvec_f (q);

    float** valDerFctBase = alloctab_f (nbneelAr,2);
    float** matJac        = alloctab_f (2,2);
    float** points        = alloctab_f(q,2);

    // Poids et points de quadrature associe au segment de reference
    ppquad(t, poids, points);

    for (int i=0; i<q ; i++){

        // Fonction de base au point de quadrature courant
        calFbase (t, points[i], valFctBase);

        // Image du point de quadrature courant dans l'element courant
        transFK (nbneelAr, coordAret, valFctBase, Fkx);

        // Derivees des fonctions de base sur le point de quadrature courant
        calDerFbase (t, points[i], valDerFctBase);

        // Matrice jacobienne 
        matJacob (nbneelAr, coordAret, 1, valDerFctBase, matJac);

        // Determinant de la matrice jacobienne
        float normeEucl = sqrtf(matJac[0][0]*matJac[0][0] + matJac[0][1]*matJac[0][1]);

        // Element differentiel * poid au point de quadrature courant
        eltdif = poids[i]*normeEucl;

        // Appel de WW
        WW (nbneelAr, valFctBase, eltdif, BN(Fkx), matAret);

        // Appel de W
        W (nbneelAr, valFctBase, eltdif, FN(Fkx), vecAret);

    }

    freevec(valFctBase);
    freevec(Fkx);
    freevec(poids);
 
    freetab(valDerFctBase);
    freetab(matJac);
    freetab(points);
}
