#ifndef ASSEMBLAGE_H
#define ASSEMBLAGE_H
/* Fonction qui realise l'assemblage des matrices et seconds membres elementaires
 * ----------------------------------------------------------------------------
 * @param[in]  typel    : Type des elements a construire
 * @param[in]  nbtng    : Nombre de noeuds geometriques
 * @param[in]  coord    : Coordonnees des noeuds geometriques
 * @param[in]  nbtel    : Nombre d'elements du maillage
 * @param[in]  ngnel    : Numeros globaux des noeuds des elements
 * @param[in]  nbneel   : Nombre de noeuds geometriques par element
 * @param[in]  nbaret   : Nombre d'aretes par element
 * @param[in]  nRefAr   : Double pointeur donnant acces au numero de reference
 *                        de chaque arete
 * @param[in]  nbRef    : Tableau contenant le nombre de valeurs utiles dans les
 *                        tableaux : nbRefD0 - nbRefD1 - nbRefF1
 * @param[in]  nRefDom  : Numero de reference associe aux aretes internes du 
 *                        domaine
 * @param[in]  numRefD0 : Tableau contenant les numeros des bords du maillage
 *                        associe a une condition de dirichlet homogene
 * @param[in]  numRefD1 : Tableau contenant les numeros des bords du maillage
 *                        associe a une condition de dirichlet non homogene
 * @param[in]  numRefF1 : Tableau contenant les numeros des bords du maillage 
 *                        associe a une condition de Neumann ou Fourier
 * @param[in]  NbLign   : Nombre de lignes et de colonnes de la matrice A
 * @param[in]  NbCoef   : Nombre de coefficients mémorises de la partie
 *                        triangulaire inferieure stricte de A
 *
 *
 * @param[out]  Matrice   : Tableau de float, de longueur >= NbLign+NbCoef
 *                          contenant les coefficients de la diagonale suivis
 *                          des coeficients non logiquement nuls de la partie
 *                          triangulaire inférieure stricte de A
 * @param[out]  SecMembre : Second membre assemble
 * @param[out]  AdPrCoefLi: Tableau d'Int de longueur >= NbLign contenant, pour
 *                          chaque ligne de la partie triangulaire inferieure
 *                          stricte de A, l'adresse du premier coefficient non
 *                          logiquement nul de cette ligne
 * @param[out]  AdSuccLi  : Tableau d'Int de longueur >= NbCoef contenant pour
 *                          chaque coefficient de la partie triangulaire infé-
 *                          rieure stricte de A, l'adresse du coefficient suivant
 *                          sur la même ligne, ou 0 si le coefficient est le 
 *                          dernier mémorisé sur la ligne
 * @param[out]  NumCol    : Tableau d'Int,  de longueur >= NbCoef contenant,
 *                          pour chaque coefficient de la partie triangulaire
 *                          inferieure stricte de A, le numéro de colonne du
 *                          coefficient
 * @param[out]  ValDLDir  : Tableau de float contenant les valeurs associees 
 *                          aux conditions de Dirichlet aux degres de liberte 
 *                          memorises dans NumDLDir
 * @param[out]  NumDLDir  : Tableau d'Int contenant les numeros des degres de 
 *                          liberte de Dirichlet
 * ----------------------------------------------------------------------------
*/
void assemblage(int typel, int nbtng, float** coord, int nbtel, int** ngnel,
	              int nbneel, int nbaret, int** nRefAr, int nbRef[3], int nRefDom,
	              int numRefD0[], int numRefD1[], int numRefF1[], int NbLign,
                int NbCoef, float* Matrice, float* SecMembre, int* AdPrCoefLi,
                int* AdSuccLi, int* NumCol, float* ValDLDir, int* NumDLDir);

#endif
