// Declarations
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Fonction qui renvoie les poids et points de quadrature en fonction du type de l'element
 * ---------------------------------------------------------------------------------------
 * @param[in] t : type de l'element (1 - quadrangle ; 2 - triangle ; 3 - segment)
 * @param[out] poids : pointeur donnant acces aux poids de quadrature
 * @param[out] points : pointeur donnant acces aux points de quadrature
 *
 * @return 0 si t est bien une des valeurs autorisees (1 - 2 - 3)
 * @return -1 si t n'est pas une des valeurs autorisees
 * ---------------------------------------------------------------------------------------
 */
int ppquad(int t, float* poids, float** points);

/* Fonction qui renvoie la valeur q associee au type de l'element
 * ---------------------------------------------------------------------------------------
 * @param[in] t : type de l'element (1 - quadrangle ; 2 - triangle ; 3 - segment)
 *
 * @return q : nombre de poids et points de quadrature en fonction de t
 * Attention : q = -1 si t n'est pas une des valeurs autorisee
 * ---------------------------------------------------------------------------------------
 */
int q_associe(int t);

/* Fonction qui calcule la valeur en un point des p fonctions de
 * base associees a l'element de reference de type t
 * ---------------------------------------------------------------------------------------
 * @param[in] t : type de l'element (1 - quadrangle ; 2 - triangle ; 3 - segment)
 * @param[in] point : pointeur donnant acces aux coordonnnes du point
 * @param[out] vect : pointeur donnant acces à la valeur en ce point 
 *                    des p fonctions de base associees a t
 *
 * @return 0 si t est bien une des valeurs autorisees (1 - 2 - 3)
 * @return -1 si t n'est pas une des valeurs autorisees
 * ---------------------------------------------------------------------------------------
 */
int calFbase (int t, float* point, float* vect);

/* Fonction qui calcule la valeur en un point des p fonctions de
 * base associees a l'element de reference de type t
 * ---------------------------------------------------------------------------------------
 * @param[in] t : type de l'element (1 - quadrangle ; 2 - triangle ; 3 - segment)
 * @param[in] point : pointeur donnant acces aux coordonnnes du point
 * @param[out] tab : pointeur donnant acces à la valeur en ce point 
 *                   des derivees des p fonctions de base associees a t
 *
 * @return 0 si t est bien une des valeurs autorisees (1 - 2 - 3)
 * @return -1 si t n'est pas une des valeurs autorisees
 * ---------------------------------------------------------------------------------------
 */
int calDerFbase (int t, float* point, float** tab);

/* Fonction qui calcule l'image d'un point de l'element de reference par la 
 * transformation (affine ici) F_{K}
 * ---------------------------------------------------------------------------------------
 * @param[in] Nk : nombre de noeuds de l'element
 * @param[in] coordElem : pointeur donnant accces aux coordonnees des 
 *                        noeuds geometriques de l'element
 * @param[in] valFctBase : pointeur donnant acces aux valeurs des fonctions
 *                         de base au point souhaite
 *
 * @param[out] image : pointeur vers les coordonnees de l'image du point de 
 *                     l'element par la transformation F_{K}
 * ---------------------------------------------------------------------------------------
 */
void transFK (int Nk, float** coordElem, float* valFctBase, float* image);

/*
 * ---------------------------------------------------------------------------------------
 *
 * ---------------------------------------------------------------------------------------
 */
void matJacob(int Nk, float** coordElem, int d, float** tab, float** matJac);

/* Fonction qui calcule le determinant et l'inverse d'une matrice de float 2x2
 * ---------------------------------------------------------------------------------------
 * @param[in] mat : Une matrice de float 2x2
 * @param[out] mat_inv : l'inverse de la matrice mat
 *
 * @return delta : le determinant de la matrice
 * ---------------------------------------------------------------------------------------
 */
float invertM2x2(float** mat, float** mat_inv);

/*
 * ---------------------------------------------------------------------------------------
 *
 * ---------------------------------------------------------------------------------------
 */
int numAret (int t, int nba, int* couple);

/* Fonction qui selectionne un nombre de points parmi un ensemble et les regroupe dans
 * un autre ensemble
 * ---------------------------------------------------------------------------------------
 * @param[in] nb : nombre de points a selectionner
 * @param[in] num[] : pointeur donnant acces aux numeros des points a selectionner
 * @param[in] coorEns[] : pointeur donnant acces aux coordonnees des points de 
 *                        l'ensemble de base
 *
 * param[out] coorSel[] : pointeur donnant acces aux coordonnees des points selectionnes
 * ---------------------------------------------------------------------------------------
 */
void selectPts(int nb, int num[], float* coorEns[], float* coorSel[]);


/* 
--------------------------------------------------------------------------------
  Autres fonctions non demandés mais utile.
--------------------------------------------------------------------------------
*/

float **alloctab_f(int dim1, int dim2);

int **alloctab_i(int dim1, int dim2); 

void freetab(void *ptr); 

float *allocvec_f(int dim);

float *allocvec_i(int dim);

void printMat(int m, int n, float **mat);

void printVect(int n, float *v);
