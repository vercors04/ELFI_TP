#include "header.h"

void maillage (double a, double b, double c, double d, int n1, int n2, int t,int nrefdom, const int *nrefcot){
	FILE *f = fopen("fichier.txt", "w"); 

  //Nombre de noeuds
	fprintf(f, "%d\n", n1*n2);
	
	//Calcul des coordonées
	double h1 = (b-a)/(n1-1);
	double h2 = (d-c)/(n2-1);

	for (int i=0 ; i<n2 ; i++){
		double y = c + i*h2;
		for (int j=0 ; j<n1 ; j++){
			fprintf(f, "%lf %lf\n",a+j*h1,y);
		}
	}
	
	//m t p q
	int m,q; //obligation des les déclarer pour les utiliser dans le calcul des arrêtes
	if (t==1) {
		m=(n1-1)*(n2-1);
		q=4;
		fprintf(f, "%d %d %d %d\n\n", m, t, 4, q); //Quadrangles
	}
	else if (t==2){
		m=2*((n1-1)*(n2-1));
		q=3;
		fprintf(f, "%d %d %d %d\n\n", m, t, 3, q); //Triangles
	} 
	
	//Calcul des numéros globaux triangle
	if (t==2) {
		for(int i=0; i<n2-1; i++){
			for(int j=1; j<n1; j++) {
				int indice = j + i*n1;
				fprintf(f, "%d %d %d\n", indice+1, indice+n1, indice);
				fprintf(f, "%d %d %d\n", indice+n1, indice+1, indice+1+n1);
			}
		}
	}

	//Calcul des numéros globaux quadrangle

	if (t==1) {
		for(int i=0; i<n2-1; i++){
			for(int j=1; j<n1; j++) {
					int indice = j + i*n1;
					fprintf(f, "%d %d %d %d\n", indice+1, indice+1+n1, indice+n1, indice);
				}
			}
		}
		fclose(f);

	//calcul des arrêtes 
	int *nRefAr_alloc = (int *) malloc(m * q * sizeof(int));
	int **nRefAr = (int **) malloc(m * sizeof(int *));

	for (int i = 0; i < m; i++) {
		nRefAr[i] = &nRefAr_alloc[i * q];
	}

	etiqAr(t,n1,n2,nrefdom,nrefcot,m,q,nRefAr);


	//test des arrêtes
	printf("\nmatrice des arrêtes : \n"); //PAS BON
	printTab(nRefAr,m,q);

	printf("\n\nnrefdom : %d\n\n", nrefdom);

	printf("\nnrefcot :\n");
	print_nrefcot(nrefcot);
	// et  apres on récupère le résultat de la fct etiqAR dans un tableau, et on le met dans le fichier.
    }

		
void etiqAr (int t, int n1, int n2, int nrefdom, const int *nrefcot, int m, int q, int **nRefAr){
	//remplissage de tout les elements 

	for (int i = 0; i < m; i++) {
    for (int j = 0; j < q; j++) {
            nRefAr[i][j] = nrefdom;
		}
	}

	//calcul des arrêtes quadrangle 
	if (t==1) {
	//parcours des carrés en haut et en bas du maillage
	for (int i=0; i<n1-1; i++){
		nRefAr[i][3]=nrefcot[0];
		nRefAr[m-1-i][1]=nrefcot[2];
	}
	//parcours des carrés sur les cotés du maillage
	for (int i=0; i<m; i=i+n1-1){
		nRefAr[i][3]=nrefcot[3];
		nRefAr[m-1-i][2]=nrefcot[1];
	}
	}

	//calcul des arrêtes triangles
	if (t==2) {
	//parcours des triangles en haut et en bas du maillage 2*(m/(n2-1)) est le nombre d'element dans une ligne
	for (int i=0; i<2*(n1-1); i=i+2){
		nRefAr[i][2]=nrefcot[0];
		nRefAr[m-1-i][2]=nrefcot[2];
	}
	//parcours des triangles sur les cotés du maillage A FINIR
	for (int i=0; i<m; i=i+2*(n1-1)){
		nRefAr[i][1]=nrefcot[3];
		nRefAr[m-1-i][1]=nrefcot[1];
	}
	}
}

int lecfima(char *ficmai, int *ptypel, int *pnbtng, float ***pcoord, int *pnbtel, int ***pngel, int *pnbneel,int *pnbaret, int ***pnRefAr){
	FILE *pfichier_maillage = fopen(ficmai,"r");
	// Recuperation de n
	fscanf(pfichier_maillage, "%d\n", &pnbtng);
/*
	// Allocation tableau coord
	float coord_alloc = (float *) malloc(2*pnbtng*sizeof(float));
	pcoord = (float **)  malloc(pnbtng*sizeof(float*));
	for (int i = 0; i < pnbtng; i++) pcoord = &coordalloc[2*i];
	
	// Recuperation des coordonnees des noeuds
	for (int i=0; i<n; i++){
		fscan(ficmai, "%lf %lf", pcoord[i][0], pcoord[i][0]);
	}
*/
	// Recuperation de m t p q
	//fscanf(pfichier_maillage, "%d %d %d %d\n", &pnbtel, &ptypel, &pnbneel, &pnbaret);

	
	fclose(pfichier_maillage);
	// Validation de la fonction
	FILE *f = fopen("verif_lecfima.txt", "w"); 
	fprintf(f, "%d\n",pnbtng);
	fclose(f);

/*

	// Recuperation de m t p q
	fscan(ficmai,"%d %d %d %d", &pnbtel, &ptypel, &pnbneel, &pnbaret);
*/
}	


//juste pour vérifier les matrices/vect - temporaire
void printTab(int **tab, int m, int q) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < q; j++) {
            printf("%d\t", tab[i][j]);
        }
        printf("\n");
    }
}


void print_nrefcot(const int *nrefcot)
{
    for (int i = 0; i < 4; i++)
        printf("%d\n", nrefcot[i]);
}
