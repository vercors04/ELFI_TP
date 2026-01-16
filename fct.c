#include "header.h"

void file_create (int a, int b, int c, int d, int n1, int n2, int t){
	FILE *f = fopen("fichier.txt", "w"); 

  //Nombre de noeuds
	fprintf(f, "%d\n", n1*n2);
	
	//Calcul des coordonées
	double h1 = (double) (b-a)/(n1-1);
	double h2 = (double) (d-c)/(n2-1);

	for (int j=0 ; j<n2 ; j++){
		double y=c+j*h2;
		for (int i=0 ; i<n1 ; i++){
			fprintf(f, "%lf %lf\n",a+i*h1,y);
		}
	}
	
	//m t p q
	if (t==1) fprintf(f, "%d %d %d %d\n",(n1-1)*(n2-1),t,4,0); //Quadrangles
	if (t==2) fprintf(f, "%d %d %d %d\n",((n1-1)*(n2-1))*2,t,3,0); //Triangles
	
	//Calcul des numéros globaux
	if (t==2) {
		for(int j=0; j<n2 ;j++){
			for (int i=1; i<n1; i++) {
				int indice = i+ j * n1;
				fprintf (f, "%d%d%d\n",indice+1,indice+n1,indice);
				fprintf (f, "%d%d%d\n",indice+n1,indice+1,indice+1+n1);
			}
		}
	}

	if (t==1) {
		for(int j=0; j<n2 ;j++){
			for (int i=1; i<n1; i++) {
					int indice = i+ j * n1;
					fprintf (f, "%d %d %d %d\n",indice+1,indice+1+n1,indice+n1,indice);
				}
			}
		}
		fclose(f);
    }

		
