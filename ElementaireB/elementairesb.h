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
void W(int nbneel, float* fctbas, float eltdif, float cofvar, float* vecelm);

/* fonction pour le calcul de la matrice de rigidite
 * ---------------------------------------------------------------------------------------
 * @param[in] nbneel : nombre de noeuds de l'element
 * @param[in] dpfctbas : derivee partielle des fonctions de base au points de quadrature courant *  la 
 * colonne associé à alpha (1 ou 2) de l'inverse de la matrice jacobienne de la transformée Fk
 * @param[in] eltdif : element differentiel multiplie par le poids de quadrature
 * @param[in] cofvar : valeur du coefficient variable (fonction a integrer calculee
 * en l'image par FK du point de quadrature courant)
 * 
 * @param[out] matelm : matrice lementaire de rigidite a actualiser
 * ---------------------------------------------------------------------------------------
*/
void ADWDW (int nbneel, float** dpfctbas, float eltdif, float** cofvar, float** matelm);

/* fonction pour le calcul de la matrice elementaire
 * ---------------------------------------------------------------------------------------
 * @param[in] t : type de l'element (1 - quadrangle ; 2 - triangle ; 3 - segment)
 * @param[in] nbneel : nombre de noeuds de l'element
 * @param[in] coordElem : coordonnees de l'element courant
 *
 * @param[out] matelm : matrice elementaire
 * @param[out] vecelm : vecteur elementaire
 * ---------------------------------------------------------------------------------------
*/
void intElem (int t, int nbneel, float** coordElem, float** matelm, float* vecelm);

/* fonction pour le calcul l'integrale sur une arrete
 * ---------------------------------------------------------------------------------------
 * @param[in] coordElem : coordonnees de l'element courant
 * @param[in] coordAret : coordonnees des noeuds de l'arrete
 *
 * @param[out] matAret : matrice de l'arrete
 * @param[out] vecAret : vecteur de l'arrete
 * ---------------------------------------------------------------------------------------
*/
void intAret ( float** coordAret, float** matAret, float* vecAret);



void cal1Elem (int nRefDom, int nbRefD0, int* numRefD0, int nbRefD1, int* numRefD1, 
               int nbRefF1, int* numRefF1, int t, int nbneel, float** coordElem, int nbaret, 
               int* nRefArEl, float*** MatElem, float** SMbrElem, int** NuDElem, float** uDElem);


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
