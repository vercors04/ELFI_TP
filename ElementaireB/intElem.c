#include <stdio.h>
#include "../Utilitaire/utilitaires.h"


void intElem (int t, int nbneel, float** coordElem, float** matelm, float* vecelm){
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

        //fonction de base au point de quadrature courant
        calFbase (t, point, valFctBase); 

        //Sert a calculer les points de quadrature de l'element courant
        transFK (nbneel, coordElem, valFctBase, Fkx);

        //valeur du coeficient variant en fonction du point de quadrature courant (non necessaire pour le moment)
        cofvar[0][0]=A11(Fkx);
        cofvar[0][1]=A12(Fkx);
        cofvar[1][0]=A12(Fkx);
        cofvar[1][1]=A22(Fkx);

        //derivees des fonctions de base sur le point de quadrature courant
        calDerFbase (t, point, valDerFctBase);

        //matrice jacobienne 
        matJacob(nbneel, coordElem, d_associe(t), valDerFctBase, matJac);

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


/*creation d'une matrice avec pour chaque ligne correspondant à un noeud les dérivée partielle en ce 
noeud * la colonne associé à alpha (1 ou 2) de l'inverse de la matrice jacobienne de la transformée Fk 
*/
void pder_WI (int nbneel, float** der_fctbas, float** invjacob, float** dpfctbas){
  for (int i=0 ; i<nbneel; i++) {
      dpfctbas [i][0]=der_fctbas[i][0] * invjacob [0][0] + der_fctbas[i][1] * invjacob [1][0];
      dpfctbas [i][1]=der_fctbas[i][0] * invjacob [0][1] + der_fctbas[i][1] * invjacob [1][1];
  }
}
