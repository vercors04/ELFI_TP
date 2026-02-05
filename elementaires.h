
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
 * @param[in] pt :
 * @param[out] vect :
 *
 * @return 0 si t est bien une des valeurs autorisees (1 - 2 - 3)
 * @return -1 si t n'est pas une des valeurs autorisees
 * ---------------------------------------------------------------------------------------
 */
int calFbase (int t, float* pt, float* vect);

int calDerFbase (int t, float* pt, float** tab);

void transFK (int Nk, float** coordElem, float* valFctBase, float* image);

void matJacob();

float invertM2x2(float** mat, float** mat_inv);

int* numAret ();

void selectPts(int nb, num[], float* coorEns[], float* coorSel[]);
