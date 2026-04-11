/* Fonction qui permet de passer de la Structure Morse Desordonnee a la
 * Structure Morse Ordonnee.   SMD --> SMO
 * ----------------------------------------------------------------------------
 * param[in]  NbLign    : Nombre de lignes et de colonnes de la matrice A - (SMD)
 * param[in]  AdPrCoefLi: Tableau d'Int de longueur >= NbLign contenant, pour
 *                        chaque ligne de la partie triangulaire inferieure
 *                        stricte de A, l'adresse du premier coefficient non
 *                        logiquement nul de cette ligne ------------------ (SMD)
 * param[in]  NumCol    : Tableau d'Int,  de longueur >= NbCoef contenant,
 *                        pour chaque coefficient de la partie triangulaire
 *                        inferieure stricte de A, le numéro de colonne du
 *                        coefficient ------------------------------------- (SMD)
 * param[in]  AdSuccLi  : Tableau d'Int de longueur >= NbCoef contenant pour
 *                        chaque coefficient de la partie triangulaire infé-
 *                        rieure stricte de A, l'adresse du coefficient suivant
 *                        sur la même ligne, ou 0 si le coefficient est le
 *                        dernier mémorisé sur la ligne ------------------- (SMD)
 * param[in]  Matrice   : Tableau de float, de longueur >= NbLign+NbCoef
 *                        contenant les coefficients de la diagonale suivis
 *                        des coeficients non logiquement nuls de la partie
 *                        triangulaire inférieure stricte de A ------------ (SMD)
 * param[in]  SecMembre : Second membre assemble -------------------------- (SMD)
 * param[in]  NumDLDir  : Tableau d'Int contenant les numeros des degres de
 *                        liberte de Dirichlet ---------------------------- (SMD)
 * param[in]  ValDLDir  : Tableau de float contenant les valeurs associees 
 *                        aux conditions de Dirichlet aux degres de liberte 
 *                        memorises dans NumDLDir ------------------------- (SMD)
 *
 *
 * param[out]  AdPrCoefLiO: Tableau de longueur NbLign des adresses des premiers
 *                          coefficients des lignes : pour I dans {2,..,NbLign}
 *                          AdPrCoefLiO(I-1) cotient l'adresse (dans LowMat) du
 *                          premier coefficient non logiquement nul de la ligne
 *                          I de A_tilde dans sa part. triangulaire inf stricte
 *                          et AdPrCoefLiO(NbLign) = NbCoef+1 ------------- (SMO)
 * param[out]  NumColO    : Tableau de longueur NbCoef contenant le numero de 
 *                          colonne de chaque element (non logiquement nul)
 *                          memorise de la part. triang. inf. stricte de
 *                          A_tilde (dans LowMat) ------------------------- (SMO)
 * param[out]  MatriceO   : Tableau de longueur NbLign+NbCoef contenant DiagMat
 *                          (coefficients diagonaux) dans sa premiere partie et
 *                          LowMat dans la seconde (coefficient non logiquement
 *                          nuls) ----------------------------------------- (SMO)
 * param[out]  SecMembreO : Second membre assemble ------------------------ (SMO)
 * ----------------------------------------------------------------------------
*/
void dSMDaSMO (int NbLign, int* AdPrCoefLi, int* NumCol, int* AdSuccLi,
               float* Matrice, float* SecMembre, int* NumDLDir, 
               float* ValDLDir, int* AdPrCoefLiO, int* NumColO, 
               float* MatriceO, float* SecMembreO);



