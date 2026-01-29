// Declarations
#include <stdio.h>
#include <stdlib.h>


/* Creation du fichier de maillage 
 * param[in] ficInput : nom du fichier de donnees d'entree
 * param[out] ficOutput : nom du fichier de sortie
 * return 0 si la fonction s'est bien deroulee, 1 sinon
*/
int maillage (char* ficInput, char *ficOutput ); //doc à changer


/* Affectation d'un numero de reference a chaque arete :
 * param[in] typel : type des elements a construire
 * param[in] n1 & n2 : nombre de points sur les cotes 1 et 2
 * param[in] nrefdom : numero de reference associe au domaine
 * param[in] nrefcot : pointeur donnant acces au numero de reference associe aux cotes
 * param[in] nbtel : nombre d'elements du maillage
 * param[in] nbaret : nombre d'aretes par element
 * param[out] nRefAr : double pointeur donnant acces au numero de reference de chaque arete
*/
void etiqAr (int typel, int n1, int n2, int nrefdom, const int *nrefcot, int nbtel, int nbaret, int **nRefAr);

/* Lecture du fichier ficmai & allocation de memoire, remplissage des tableaux : coord, ngnel et nRefAr
 * param[in] ficmai : fichier lu par la fonction
 * param[out] ptypel : pointeur vers le type des elements du maillage
 * param[out] pnbtng : pointeur vers le nombre de noeuds geometriques
 * param[out] pcoord : pointeur vers les coordonnees des noeuds geometriques
 * param[out] pnbtel : pointeur vers le nombre d'elements du maillage
 * param[out] pngnel : pointeur vers les numeros globaux des noeuds des elements
 * param[out] pnbneel : pointeur vers le nombre de noeuds geometriques par element
 * param[out] pnbaret : pointeur vers le nombre d'aretes par element
 * param[out] pnRefAr : pointeur vers les numeros de reference associes aux aretes
 * return 0 si la fonction si s'est bien deroulee, 1 sinon
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

