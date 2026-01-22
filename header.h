//header pour mettre toutes les declarations, etc... plus simple
#include <stdio.h>
#include <stdlib.h>

// Doc
void maillage (double, double, double, double, int, int, int, int, const int *); 

// etiqAr(int typel, int n1, int n2, int nrefdom, 
// 		const int *nrefcot, int nbtel, int nbaret, int **nRefAr)
// ----------------------------------------------------------------------//
//Effectation d'un numero de reference a chaque arete
// Entrees :
// typel : type des elements a construire (int)
// n1 & n2 : nombre de points sur les cotes 1 et 2 (int)
// nrefdom : numero de reference associe au domaine (int)
// nrefcot : numero de reference associe aux cotes (const int *)
// nbtel : nombre d'elements du maillage (int)
// nbaret : nombre d'aretes par element (int)
// nRefAr : tableau contenant le numero de reference de chaque arete (int **)
void etiqAr (int, int, int, int, const int *, int, int, int **);

//Doc
int lecfima(char *, int *, int *, float ***, int *, int ***, int *,int *, int ***);


void printTab(int **tab, int m, int q);//a enlever juste pr test
