#include "header.h"

int type_element(int t, int n1, int n2, int *m, int *q, int *p){
  switch (t) {
    case 1: *m=(n1-1)*(n2-1); *q=4; *p=4; break; // Quadrangles
    case 2: *m=2*((n1-1)*(n2-1)); *q=3; *p=3; break; // Triangles
    default: printf("ERREUR : Cas possibles : \n t=1 : Quadrangles\n t=2 : Triangles");return 1;
  }

  return 0;
}


void maillage (double a, double b, double c, double d, int n1, int n2 , int m , int t, int p, int q, int nrefdom, const int *nrefcot, int **nRefAr){
	FILE *f = fopen("fichier.txt", "w"); 

    //------Nombre de noeuds------
	fprintf(f, "%d\n", n1*n2);
	
	//------Calcul des coordonées------
	double h1 = (b-a)/(n1-1);
	double h2 = (d-c)/(n2-1);

	for (int i=0 ; i<n2 ; i++){
		double y = c + i*h2;
		for (int j=0 ; j<n1 ; j++){
			fprintf(f, "%lf %lf\n",a+j*h1,y);
		}
	}
	
	//------ calcul de  : m t p q ------
	fprintf(f, "%d %d %d %d\n", m, t, p, q); //Quadrangles
	

	//------Calcul des numéros globaux------
	//triangle
	int indice, indice2;
	if (t==2) {
		for(int i=0; i<n2-1; i++){
			for(int j=1; j<n1; j++) {
				indice = j + i*(n1-1);
				indice2 = (j + i*(n1-1))-1;
				fprintf(f, "%d %d %d ", indice+1, indice+n1, indice);
				fprintf(f, "%d %d %d\n",nRefAr[indice2][0],nRefAr[indice2][1],nRefAr[indice2][2]);
				fprintf(f, "%d %d %d ", indice+n1, indice+1, indice+1+n1);
				fprintf(f, "%d %d %d\n",nRefAr[indice2][0],nRefAr[indice2][1],nRefAr[indice2][2]);

			}
		}
	}

	//quadrangle
	if (t==1) {
		for(int i=0; i<n2-1; i++){
			for(int j=1; j<n1; j++) {
					indice = j + i*n1;
					indice2 = (j + i*(n1-1))-1;
					fprintf(f, "%d %d %d %d ", indice+1, indice+1+n1, indice+n1, indice);
					fprintf(f, "%d %d %d %d\n",nRefAr[indice2][0],nRefAr[indice2][1],nRefAr[indice2][2],nRefAr[indice2][3]);
				}
			}
		}

	//------Ecriture de nrefAr dans le fichier------
	

	//fermeture du fichier
	fclose(f);
}

void etiqAr (int t, int n1, int n2, int nrefdom, const int *nrefcot, int m, int q, int **nRefAr){

	//remplissage de tout les elements à 0

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
		nRefAr[i][2]=nrefcot[3];
		nRefAr[m-1-i][0]=nrefcot[1];
	}
	}

	//calcul des arrêtes triangles
	if (t==2) {
	//parcours des triangles en haut et en bas du maillage
	for (int i=0; i<2*(n1-1); i=i+2){
		nRefAr[i][2]=nrefcot[0];
		nRefAr[m-1-i][2]=nrefcot[2];
	}
	//parcours des triangles sur les cotés du maillage 
	for (int i=0; i<m; i=i+2*(n1-1)){
		nRefAr[i][1]=nrefcot[3];
		nRefAr[m-1-i][1]=nrefcot[1];
	}
	}
}

int lecfima(char *ficmai, int *ptypel, int *pnbtng, float ***pcoord, int *pnbtel, int ***pngnel, int *pnbneel,int *pnbaret, int ***pnRefAr){
  // Ouverture du fichier de maillage à lire
  FILE *pfichier_maillage = fopen(ficmai,"r");
  // Test du bon deroulement de l'ouverture
    if (pfichier_maillage==NULL) { 
      printf("ERREUR : Le fichier n'a pas pu etre ouvert.\n");
      return 1;
    }

	// Recuperation de n
	fscanf(pfichier_maillage, "%d\n\n", pnbtng);

	
  // Allocation tableau coord
  *pcoord = alloctab_f(*pnbtng,2);
  // Recuperation des coordonnees dans le fichier
  for (int i=0; i<*pnbtng; i++){
	  fscanf(pfichier_maillage, "%f %f\n", &(*pcoord)[i][0], &(*pcoord)[i][1]);
  }
  
  // Recuperation de m t p q
  fscanf(pfichier_maillage, "\n%d %d %d %d\n", pnbtel, ptypel, pnbneel, pnbaret);
  
  
  // Allocation tableau ngel
  *pngnel = alloctab_i(*pnbtel,*pnbneel);
  // Recuperation des numeros globaux et numeros de reference
  for (int i=0;i<*pnbtel;i++) {
    for (int j=0;j<*pnbneel;j++) {
      fscanf(pfichier_maillage, "%d ",&(*pngnel)[i][j]);
    }
    /* En attente de l'implémentation des num de reference
    for (int j=0;j<*pnbneel;j++) {
      fscanf(pfichier_maillage, "%d",);
    }
    */
    fscanf(pfichier_maillage, "\n");
    printf("\n");
  }

	fclose(pfichier_maillage);

	// Validation de la fonction
	FILE *verif = fopen("verif_lecfima.txt", "w"); 
	// Test du bon deroulement de l'ouverture
  if (verif==NULL) { 
    printf("ERREUR : Le fichier n'a pas pu etre ouvert.\n");
    return 1;
    }

  fprintf(verif, "%d\n",*pnbtng);

  for (int i=0; i<*pnbtng; i++){
    fprintf(verif, "%f %f\n", (*pcoord)[i][0], (*pcoord)[i][1]);
	}
	fprintf(verif, "%d %d %d %d\n", *pnbtel, *ptypel, *pnbneel, *pnbaret);

  for (int i=0;i<*pnbtel;i++) {
    for (int j=0;j<*pnbneel;j++) {
      fprintf(verif, "%d ",(*pngnel)[i][j]);
    }
    /* En attente de l'implémentation des num de reference
    for (int j=0;j<*pnbneel;j++) {
      fscanf(pfichier_maillage, "%d",);
    }
    */
    fprintf(verif, "\n");
  }
	fclose(verif);

}	




//------juste pour vérifier les matrices/vect - temporaire------
void printTab(int **tab, int m, int q) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < q; j++) {
            printf("%d\t", tab[i][j]);
        }
        printf("\n");
    }
}
void printTabf(float **tab, int m, int q) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < q; j++) {
            printf("%lf\t", tab[i][j]);
        }
        printf("\n");
    }
}

void print_nrefcot(const int *nrefcot)
{
    for (int i = 0; i < 4; i++)
        printf("%d\n", nrefcot[i]);
}
//test des arrêtes
// printf("\nmatrice des arrêtes : \n"); 
// printTab(nRefAr,m,q);

// printf("\n\nnrefdom : %d\n\n", nrefdom);

// printf("\nnrefcot :\n");
// print_nrefcot(nrefcot);
