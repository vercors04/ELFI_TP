//header pour mettre toutes les declarations, etc... plus simple
#include <stdio.h>
#include <stdlib.h>

// Doc
int type_element(int t,int n1, int n2, int *m, int *q, int *p);

// Doc
void maillage (double a, double b, double c, double d, int n1, int n2 , int m , int t, int p, int q, int nrefdom, const int *nrefcot, int **nRefAr); 

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

/* Lecture du fichier ficmai & allocation de memoire, remplissage des tableaux : coord, ngnel et nRefAr
 * param ficmai : fichier lu par la fonction
 * param ptypel : pointeur vers le type des elements du maillage
 * param pnbtng : pointeur vers le nombre de noeuds geometriques
 * param pcoord : pointeur vers les coordonnees des noeuds geometriques
 * param pnbtel : pointeur vers le nombre d'elements du maillage
 * param pngnel : pointeur vers les numeros globaux des noeuds des elements
 * param pnbneel : pointeur vers le nombre de noeuds geometriques par element
 * param pnbaret : pointeur vers le nombre d'aretes par element
 * param pnRefAr : pointeur vers les numeros de reference associes aux aretes
 */
int lecfima(char *ficmai, int *ptypel, int *pnbtng, float ***pcoord, int *pnbtel, int ***pngnel, int *pnbneel, int *pnbaret, int ***pnRefAr);

float **alloctab_f(int dim1, int dim2);
int **alloctab_i(int dim1, int dim2); 

void printTab(int **tab, int m, int q);//a enlever juste pr test
void printTabf(float **tab, int m, int q);//a enlever juste pr test
void print_nrefcot(const int *nrefcot);
