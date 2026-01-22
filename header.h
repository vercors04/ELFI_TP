//header pour mettre toutes les declarations, etc... plus simple
#include <stdio.h>
#include <stdlib.h>

// Doc
void maillage (double, double, double, double, int, int, int, int, const int *); 

/* Affectation d'un numero de reference a chaque arete :
 * param typel : type des elements a construire 
 * param n1 & n2 : nombre de points sur les cotes 1 et 2 
 * param nrefdom : numero de reference associe au domaine 
 * param nrefcot : numero de reference associe aux cotes 
 * param nbtel : nombre d'elements du maillage 
 * param nbaret : nombre d'aretes par element 
 * param nRefAr : tableau contenant le numero de reference de chaque arete - ce qui est modifie dans la fonction 
*/
void etiqAr (int typel, int n1, int n2, int nrefdom, const int *nrefcot, int nbtel, int nbaret, int **nRefAr);

//Doc
int lecfima(char *, int *, int *, float ***, int *, int ***, int *,int *, int ***);


void printTab(int **tab, int m, int q);//a enlever juste pr test
void print_nrefcot(const int *nrefcot);
