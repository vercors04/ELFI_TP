#include <stdio.h>
#include "../Utilitaire/utilitaires.h"


void intElem (int t, int nbneel, float** coordElem, float** matelm, float* vecelem){
    float* point = allocvec (2);
    float* valFctBase = allocvec (2);
    float* Fkx = allocvec (2);
    float* poids = allocvec (q_associate(t));

    float** valDerFctBase = alloctab (nbneel,2);
    float** matJac = alloctab (2,2);
    float** invMatJac = alloctab (2,2);
    
    for (int i=0; i<q_associate(t) ; i++){
        //coordonne du point de quadrature courant
        point[0]=coordElem [i][0];
        point[1]=coordElem [i][1];

        //fonction de base au point de quadrature courant
        calFbase (t, point, valFctBase); 

        //Sert a calculer les points de quadrature de l'element courant
        transFK (nbneel, coordElem, valFctBase, Fkx);

        //derivees des fonctions de base sur le point de quadrature courant
        calDerFbase (t, point, valDerFctBase);

        //matrice jacobienne 
        matJacob(nbneel, coordElem, d_associe(t), valDerFctBase, matJac);

        //determinant de la matrice jacobienne
        int det = invertM2x2(matJac, invMatJac);


    }





}