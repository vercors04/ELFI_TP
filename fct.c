#include "header.h"

void file_create (double a, double b, double c, double d, int n1, int n2, int m, int t){
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
	if (t==1) fprintf(f, "%d %d %d %d\n\n", (n1-1)*(n2-1), t, 4, 0); //Quadrangles
	else if (t==2) fprintf(f, "%d %d %d %d\n\n", ((n1-1)*(n2-1))*2, t, 3, 0); //Triangles
	
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
    }

		
void etiqAR (int t, int n1, int n2, int nrefdom, const int *nrefcot, int m, int q, int **nRefAr){
	//calcul des arrêtes quadrangle 
	if (t==1) {
	//parcours des carrés en haut et en bas du maillage
	for (int i=0; i<m/(n2-1); i++){
		nRefAr[i][4]=nrefcot[0];
		nRefAr[(m-1)-i][2]=nrefcot[2];
	}
	//parcours des carrés sur les cotés du maillage
	for (int i=0; i<m-(n1-1); i=i+n1-1){
		nRefAr[i][3]=nrefcot[3];
		nRefAr[(m-1)-i][2]=nrefcot[1];
	}
	}

	//calcul des arrêtes triangles
	if (t==2) {
	//parcours des triangles en haut et en bas du maillage 2*(m/(n2-1)) est le nombre d'element dans une ligne
	for (int i=0; i<2*(m/(n2-1)); i=i+2){
		nRefAr[i][3]=nrefcot[0];
		nRefAr[(m-1)-i][3]=nrefcot[2];
	}
	//parcours des triangles sur les cotés du maillage A FINIR
	for (int i=0; i<m-(n1-1); i=i+n1-1){
		nRefAr[i][3]=nrefcot[3];
		nRefAr[(m-1)-i][2]=nrefcot[1];
	}
	}
	//testtetstetsS
}

int lecfima(char *ficmai, int *ptypel, int *pnbtng, float ***pcoord, int *pnbtel, int ***pngel, int *pnbneel,int *pnbaret, int ***pnRefAr){

}	

