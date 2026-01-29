// Declarations
#include <stdio.h>
#include <stdlib.h>


/* Creation du fichier de maillage 
 * param ficInput : nom du fichier de donnees d'entree
 * param ficOutput : nom du fichier de sortie
*/
int maillage (char* ficInput, char *ficOutput ); //doc à changer


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

/* Entree des variables par l'utilisateur et creation d'un fichier de donnees pour la fonction maillage
*/
void modeSaisie2 ();

/* Allocation dynamique d'une matrice de float 
*/
float **alloctab_f(int dim1, int dim2);

/* Allocation dynamique d'une matrice d'entier
*/
int **alloctab_i(int dim1, int dim2); 

/* Liberation de la memoire
*/
void freetab(void *ptr); 

