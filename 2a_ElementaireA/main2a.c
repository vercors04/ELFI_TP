/*
* POUR COMPILER LE PROGRAMME ET CREER L'EXECUTABLE :
* -----------------------------------------
* Lancer main2a.sh dans le dossier "Executables/"
* Attention : l'executable doit se trouver dans le dossier "Executables/"
* -----------------------------------------
*/

#include "elementairesa.h"
#include "../Utilitaire/utilitaires.h"


int main() {

    printf("----------------TEST DES FONCTIONS ELEMENTAIRES----------------\n\n");
    
    //données à modifier
    int t = 1;
    int nb_sommets = 4;
    int d =2; //dimension
    /*
    autre trucs à changer : 
    -le point arbitraire dans calFbase et calDerFbase
    -le point de reference dans transFK
    -coordElem dans transFK et matJacob, en fonction de t
    -coorEns dans selecpts
    */

    /*
    ppquad
    */
    printf("------ TEST PPQUAD ------\n");

    int q = q_associe(t);
    float* poids = allocvec_f(q);
    float** points = alloctab_f(q, 2);

    ppquad(t, poids, points);

    printf("\nAvec t = %d.\nAvec q = %d.\n", t, q);

    printf("\nvecteur poids : \n");
    printVect(q, poids);

    printf("\nmatrices points : \n");
    printMat(q, 2, points);


    /*
    calFbase
    */
    printf("\n\n\n------ TEST CALFBASE ------\n");
    float* point = allocvec_f(2); 
    float* vect = allocvec_f(nb_sommets);

    //point arbitraire
    point[0] = 0.333333f;
    point[1] = 0.333333f;

    calFbase (t, point, vect);

    printf("Pour t=%d au point (%f, %f) :\n\n", t, point[0], point[1]);
    printVect(nb_sommets, vect);


    /*
    calDerFbase
    */
    printf("\n\n\n------ TEST CALDERFBASE ------\n");
    float** tab = alloctab_f(nb_sommets, 2);
    calDerFbase (t, point, tab);

    printf("Pour t=%d au point (%f, %f) :\n\n", t, point[0], point[1]);
    printMat(nb_sommets, 2, tab);


    /*
    transFK
    */
    printf("\n\n\n------ TEST TRANSFK ------\n");
    //point de l'emlement de reference dont on calcule l'image
    float* pt_ref = allocvec_f(2);
    pt_ref[0] = 1.0f;
    pt_ref[1] = 1.0f/2.0f;


    //calcul des fonctions de base
    float* valFctBase = allocvec_f(nb_sommets);
    calFbase(t, pt_ref, valFctBase);

    //coordonnees du quadrangle 
    float** coordElem = alloctab_f(nb_sommets, 2);
    coordElem[0][0] = 3.0f; coordElem[0][1] = 1.0f;
    coordElem[1][0] = 3.0f; coordElem[1][1] = 3.0f;
    coordElem[2][0] = 1.0f; coordElem[2][1] = 3.0f;
    coordElem[3][0] = 1.0f; coordElem[3][1] = 1.0f;

    //vecteur image
    float* image = allocvec_f(2);


    transFK (nb_sommets, coordElem, valFctBase, image);
    printf("Pour t=%d avec le point de ref (%f, %f) :\n\n", t, pt_ref[0], pt_ref[1]);
    printVect(2,image);



    /*
    matJacob
    */
    printf("\n\n\n------ TEST MATJACOB ------\n");

    float** matJac = alloctab_f(2,d);
    matJacob(nb_sommets, coordElem, d, tab, matJac);

    printf("Pour t=%d  :\n\n", t);
    printMat(2, d, matJac);




    /*
    invertM2x2
    */
    printf("\n\n\n------ TEST INVERTM2X2 ------\n");
    float** matrice = alloctab_f(2,2);
    float** matrice_inv = alloctab_f(2,2);

    matrice[0][0] = 1;
    matrice[0][1] = 2;
    matrice[1][0] = 3;
    matrice[1][1] = 4;

    invertM2x2(matrice, matrice_inv);
    printf("\n matrice : \n");
    printMat(2, 2, matrice);
    printf("\n matrice inversee : \n");
    printMat(2, 2, matrice_inv);


    /*
    numNaret
    */
    printf("\n\n\n------ TEST NUMNARET ------\n");

    int nba = 2;
    int* couple = allocvec_i (2);
    numAret (t, nba, couple);

    printf("pour t= %d, et l'arrete %d.\ncouple = %d %d", t, nba, couple[0], couple [1]);



    /*
    selectPts
    */
    printf("\n\n\n------ TEST SELECTPTS ------\n");
    //creation d'un proto maillage pour test
    int nb_pts = 4;
    float** coorEns = alloctab_f(nb_pts, 2);

    coorEns[0][0] = 1.1f; coorEns[0][1] = 1.0f;
    coorEns[1][0] = 2.2f; coorEns[1][1] = 2.0f;
    coorEns[2][0] = 3.3f; coorEns[2][1] = 3.0f;
    coorEns[3][0] = 4.4f; coorEns[3][1] = 4.0f;
    
    printf("Matrice contenant les points à selectionner :\n");
    printMat (nb_pts,2,coorEns);
    //nombre de points à selectionner
    int nb = 2;
    int* num = allocvec_i(nb);
    num[0] = 3; 
    num[1] = 1;

    float** coorSel = alloctab_f(nb,2);
    selectPts(nb, num, coorEns, coorSel);

    printf("Pour les points numero %d et numero %d :\n", num[0], num[1]);
    //printf("(%f,%f)\n",(**coorSel),**(coorSel+1));
    printMat (nb, 2, coorSel);


    /*
    liberation de la memoire
    */
    freevec(poids);
    freetab(points);

    freevec(point);
    freevec(vect);
    freetab(tab);

    freevec(pt_ref);
    freevec(valFctBase);
    freetab(coordElem);
    freevec(image);

    freetab(matJac);

    freetab(matrice);
    freetab(matrice_inv);

    freevec(couple);

    freetab(coorEns);
    freevec(num);
    freevec(coorSel);

    return 0;
}





   



    




    




    




    







    







