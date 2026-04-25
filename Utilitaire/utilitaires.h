#ifndef UTILITAIRES_H
#define UTILITAIRES_H

/* Fonction qui alloue dynamiquement une matrice de float de taille dim1 x dim2
*/
float **alloctab_f(int dim1, int dim2);

/* Fonction qui alloue dynamiquement une matrice d'Int de taille dim1 x dim2
*/
int **alloctab_i(int dim1, int dim2); 

/* Liberation de la memoire
*/
void freetab(void *ptr); 

/* Fonction qui alloue dynamiquement un vecteur de float de taille dim
*/
float *allocvec_f(int dim);

/* Fonction qui alloue dynamiquement un vecteur d'int de taille dim
*/
int *allocvec_i(int dim);

/* Liberation de la memoire
*/
void freevec(void *ptr);

/* Fonction qui imprime une matrice de float de taille m x n
*/
void printMat(int m, int n, float **mat);

/* Fonction qui imprime un vecteur de float de taille n
*/
void printVect(int n, float *v);

/* Fonction qui alloue dynamiquement une matrice de float de taille dim1 x dim2, et l'initialise à 0
*/
float **calloctab_f(int dim1, int dim2);

/* Fonction qui alloue dynamiquement une matrice d' Int de taille dim1 x dim2, et l'initialise à 0
*/
int **calloctab_i(int dim1, int dim2);

/* Fonction qui alloue dynamiquement un vecteur de float de taille dim, et l'initialise a 0
*/
float *callocvec_f(int dim);

/* Fonction qui alloue dynamiquement un vecteur d'Int de taille dim, et l'initialise a 0
*/
int *callocvec_i(int dim);

#endif
