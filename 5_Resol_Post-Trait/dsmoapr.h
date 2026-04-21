#ifndef DSMOAPR_H
#define DSMOAPR_H
/* * ---------------------------------------------------------------------------------------
 * @param[in]  NbLign       : Nombre de lignes et de colonnes de la matrice A
 * @param[in]  AdPrCoefLiO  : Tableau de longueur NbLign des adresses des premiers
 *                            coefficients des lignes : pour I dans {2,..,NbLign}
 *                            AdPrCoefLiO(I-1) contient l'adresse (dans LowMat) du
 *                            premier coefficient non logiquement nul de la ligne
 *                            I de A_tilde dans sa part. triangulaire inf stricte
 *                            et AdPrCoefLiO(NbLign) = NbCoef+1 ------------- (SMO)
 * @param[in]  NumColO      : Tableau de longueur NbCoef contenant le numero de 
 *                            colonne de chaque element (non logiquement nul)
 *                            memorise de la part. triang. inf. stricte de
 *                            A_tilde (dans LowMat) ------------------------- (SMO)
 * @param[in]  MatriceO     : Tableau de longueur NbLign+NbCoef contenant DiagMat
 *                            (coefficients diagonaux) dans sa premiere partie et
 *                            LowMat dans la seconde (coefficient non logiquement
 *                            nuls) ----------------------------------------- (SMO)
 *
 * * @return                : Longueur totale nécessaire pour le tableau MatProf
 * ---------------------------------------------------------------------------------------
 */
int dSMOaLongPR2(int NbLign, int* AdPrCoefLiO, int* NumColO, float* MatriceO);

/* * ---------------------------------------------------------------------------------------
 * @param[in]  NbLign       : Nombre de lignes et de colonnes de la matrice A
 * @param[in]  AdPrCoefLiO  : leau de longueur NbLign des adresses des premiers
 *                            coefficients des lignes : pour I dans {2,..,NbLign}
 *                            AdPrCoefLiO(I-1) contient l'adresse (dans LowMat) du
 *                            premier coefficient non logiquement nul de la ligne
 *                            I de A_tilde dans sa part. triangulaire inf stricte
 *                            et AdPrCoefLiO(NbLign) = NbCoef+1 ------------- (SMO)
 * @param[in]  NumColO      : Tableau de longueur NbCoef contenant le numero de 
 *                            colonne de chaque element (non logiquement nul)
 *                            memorise de la part. triang. inf. stricte de
 *                            A_tilde (dans LowMat) ------------------------- (SMO)
 * @param[in]  MatriceO     : Tableau de longueur NbLign+NbCoef contenant DiagMat
 *                            (coefficients diagonaux) dans sa premiere partie et
 *                            LowMat dans la seconde (coefficient non logiquement
 *                            nuls) ----------------------------------------- (SMO)

 *
 * @param[out] Profil       : Tableau d'entier contenant la position du premier 
 *                            coeficient de chaque ligne dans MatProf
 * @param[out] MatProf      : Tableau de reels contenant la diagonale suivie des 
 *                            coeficients de profil inferieur concatenes
 * ---------------------------------------------------------------------------------------
 */
void dSMOaPR2(int NbLign, int* AdPrCoefLiO, int* NumColO, float* MatriceO, int* Profil, float* MatProf);

/* * ---------------------------------------------------------------------------------------
 * @param[in]  NbLign       : Nombre de lignes et de colonnes de la matrice A
 * @param[in]  LongMatProf  : Longueur totale nécessaire pour le tableau MatProf
 * @param[in]  Profil       : Tableau d'entier contenant la position du premier 
 *                            coeficient de chaque ligne dans MatProf
 * @param[in]  MatProf      : Tableau de reels contenant la diagonale suivie des 
 *                            coeficients de profil inferieur concatenes
 * @param[in]  SecMembre    : Vecteur second membre assemble
 *
 * @param[out] Sol          : Vecteur solution obtenu apres la decomposition LLt 
 *                            de Cholesky puis la descente - remontee
 * ---------------------------------------------------------------------------------------
 */
void resolsyst(int NbLign, int LongMatProf, int* Profil, float* MatProf, float* SecMembre, float* Sol);

/* * ---------------------------------------------------------------------------------------
 * @param[in]  NbLign       : Nombre de lignes et de colonnes de la matrice A
 * @param[in]  coord        : Coordonnees globale des noeuds geometriques du
 *                            maillage
 *
 * @param[out] UEX          : Vecteur contenant la valeur exacte calculee en
 *                            chaques points
 * ---------------------------------------------------------------------------------------
 */
void CalSol (int NbLign, float **coord, float *UEX);

/*
--------------------------------------------------------------------------------
  Fonction fournies avec l'ennonce.
--------------------------------------------------------------------------------

   Fonctions relatives au passage de SMO a profil.

   dSMOaLongPR. Fonction de calcul de la longueur de la matrice profil.

   dSMOaPR. Fonction de creation de la matrice profil.

*/
int dSMOaLongPR(int NbLign, int* AdPrCoefLiO, int* NumColO, float* MatriceO);

void dSMOaPR(int NbLign, int* AdPrCoefLiO, int* NumColO, float* MatriceO, int longProfilMat, int* Profil, float* MatProf);

float solex(float *coor);

#endif