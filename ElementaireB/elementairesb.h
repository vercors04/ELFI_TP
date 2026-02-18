// Declarations
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* Fonctions qui renvoient les resultats des fonctions intervenant dans les intégrales
 * ---------------------------------------------------------------------------------------
 * @param[in] x : point de coordonne x = (x1, x2)
 * 
 * @return le resultat de la fonction
 * ---------------------------------------------------------------------------------------
*/
float A11(float* x);

float A22(float* x);

float A12(float* x);

float A00(float* x);

float BN(float* x);

float FOMEGA(float* x);

float FN(float* x);

float UD(float* x);


/* Procedure W
 * Calcul de : $\int_{K}f_{\Omega}(x)dx$ --ou-- $\int_{K'}f_{N}(\sigma)w_{j}^{K'}d\sigma$
 * ---------------------------------------------------------------------------------------
 * @param[in]  nbneel :
 * @param[in]  fctbas :
 * @param[in]  eltdif :
 * @param[in]  cofvar :
 *
 * @param[in/out] vecelm :
 * ---------------------------------------------------------------------------------------
 */
void w(int nbneel, float* fctbas, float eltdif, float cofvar, float* vecelm);

/* 
--------------------------------------------------------------------------------
  Fonction fournies avec l'ennonce.
--------------------------------------------------------------------------------
*/

/*
  Imprime les resultats de la matrice et du second membre elementaires
  ainsi que les conditions Dirichlet en chaque noeud
  et les valeurs des conditions Dirichlet non homogene
 
*** Arguments *** 
   K        : Numero de l'element
   typEl    : Numero de type de l'element
   nbneel   : Nombre de noeuds de l'element
   MatElem  : Matrice elementaire de dimensions (nbneel,nbneel)
   SMbrElem : Second membre elementaire de dimension nbneel
   NuDElem  : Tableau de reperage des noeuds porteurs de conditions de Dirichlet
   uDElem   : Tableau des valeurs de blocage
              pour les noeuds Dirichlet non homogene
*/
void impCalEl(int K, int typEl, int nbneel, float **MatElem, float *SMbrElem,int *NuDElem, float *uDElem);

/*
--------------------------------------------------------------------------------
  Mise a jour de la matrice elementaire : ajout de la contribution
  d'un point de quadrature d'un element ou de son bord, pour le calcul
  d'integrales elementaires faisant intervenir le produit de deux
  fonctions de base.

  Terminologie : FK designe la transformation qui calcule l'image dans
                 l'element courant d'un point de l'element de reference

  Arguments d'entree :
   nbneel : nombre de noeuds de l'element
   fctbas : valeurs des fonctions de base au point de quadrature courant
            Dimensions utiles : fctbas(nbneel)
   eltdif : element differentiel multiplie par le poids de quadrature
   cofvar : valeur du coefficient variable (fonction a integrer calculee
            en l'image par FK du point de quadrature courant)
   matelm : matrice elementaire de masse a actualiser
            Dimensions utiles : matelm(nbneel,nbneel)
  Arguments de sortie :
   matelm : matrice elementaire de masse actualisee
--------------------------------------------------------------------------------
*/
void WW(int nbneel, float *fctbas, float eltdif, float cofvar, float **matelm);
