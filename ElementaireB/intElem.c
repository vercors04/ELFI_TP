#include "../Utilitaire/utilitaires.h"
#include "../ElementaireA/elementairesa.h"
#include "../ElementaireB/elementairesb.h"

void pder_WI (int , float** , float** , float** );

void intElem (int t, int nbneel, float** coordElem, float** matelm, float* vecelm){
<<<<<<< HEAD

    int q = q_associe(t);
=======
    float* point = allocvec (2);
    float* valFctBase = allocvec (nbneel);
    float* Fkx = allocvec (2);
    float* poids = allocvec (q_associe(t));

    float** valDerFctBase = alloctab (nbneel,2);
    float** matJac = alloctab (2,2);
    float** invMatJac = alloctab (2,2);
    float** points = alloctab(q_associe(t),2);
    float** cofvar = alloctab (2,2);
    float** dpfctbas = alloctab (nbneel, 2);

    //poid associe au point de quadrature
    ppquad(t, poids, points);

    for (int i=0; i<q_associate(t) ; i++){
        //coordonne du point de quadrature courant
        point[0]=points [i][0];
        point[1]=points [i][1];
>>>>>>> xavier

    float detJFK_abs;
    float eltdif;
    float cofvar_zz;
    float cofvar_f;

    float* valFctBase = allocvec_f(2);
    float* Fkx = allocvec_f(2);
    float* poids = allocvec_f(q);

<<<<<<< HEAD
    float** valDerFctBase = alloctab_f(nbneel,2);
    float** matJac = alloctab_f(2,2);
    float** invMatJac = alloctab_f(2,2);
    float** dpfctbas = alloctab_f(nbneel,2);
    float** cofvar = alloctab_f(2,2);
=======
        //valeur du coeficient variant en fonction du point de quadrature courant (non necessaire pour le moment)
        cofvar[0][0]=A11(Fkx);
        cofvar[0][1]=A12(Fkx);
        cofvar[1][0]=A12(Fkx);
        cofvar[1][1]=A22(Fkx);

        //derivees des fonctions de base sur le point de quadrature courant
        calDerFbase (t, point, valDerFctBase);
>>>>>>> xavier

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

<<<<<<< HEAD
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
=======
        //determinant de la matrice jacobienne
        float det = invertM2x2(matJac, invMatJac);

        //element differentiel * poid au point de quadrature courant
        float eltdif = poids[i]*fabs(det);

        //appel de WW
        WW(nbneel, valFctBase, eltdif, A00(Fkx), matelm);

        //appel ADWDW
        pder_WI (nbneel, valDerFctBase, invMatJac, dpfctbas);
        ADWDW (nbneel, dpfctbas, eltdif, cofvar, matelm);

        //appel de W
        w(nbneel, valFctBase, eltdif, FOMEGA(Fkx), vecelm);
>>>>>>> xavier

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

    freevec(point);
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


<<<<<<< HEAD


=======
/*creation d'une matrice avec pour chaque ligne correspondant à un noeud les dérivée partielle en ce 
noeud * la colonne associé à alpha (1 ou 2) de l'inverse de la matrice jacobienne de la transformée Fk 
*/
void pder_WI (int nbneel, float** der_fctbas, float** invjacob, float** dpfctbas){
  for (int i=0 ; i<nbneel; i++) {
      dpfctbas [i][0]=der_fctbas[i][0] * invjacob [0][0] + der_fctbas[i][1] * invjacob [1][0];
      dpfctbas [i][1]=der_fctbas[i][0] * invjacob [0][1] + der_fctbas[i][1] * invjacob [1][1];
  }
}
>>>>>>> xavier
