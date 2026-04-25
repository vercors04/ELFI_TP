#include <stdio.h>
#include <stdlib.h>
#include "../1_Maillage/maillage.h"
#include "../Utilitaire/utilitaires.h"


int maillage (char *ficInput, char *ficOutput ) {

// Ouverture des fichiers input et output
  FILE *Donnees = fopen(ficInput, "r");
  if (Donnees==NULL) {
    printf("ERREUR : Le fichier ficInput.txt n'a pas pu etre ouvert.\n");
    return 1;
  }

  FILE *Output = fopen (ficOutput, "w");
  if (Output==NULL) {
    printf("ERREUR : Le fichier ficOutput.txt n'a pas pu etre ouvert.\n");
	  fclose(Donnees);
    return 1;
  }

	int  n1, n2, t, nrefdom, nrefcot[4], m, q, p;
  float a, b, c, d;

  //------Lecture du fichier------ 
  fscanf(Donnees, "%f %f %f %f %d %d %d %d", &a, &b, &c, &d, &n1, &n2, &t, &nrefdom);
  for (int i = 0; i < 4; i++) {
    fscanf(Donnees, "%d", &nrefcot[i]);
  }

	// Affichage des donnees (optionel)
  printf("Domaine : [%f,%f]x[%f,%f]\n",a,b,c,d);
  printf("Nombres de points n1 = %d\n",n1);
  printf("Nombres de points n2 = %d\n",n2);
  if (t==1) printf("Type : Quadrangles\n");
  else if (t==2) printf("Type : Triangles\n");

	//------Calcul de m p q------
	switch (t) {
    case 1:
      m = (n1-1) * (n2-1);
      q = 4;
      p = 4;
      break; // Quadrangles
    case 2:
      m = 2 * (n1-1) * (n2-1);
      q = 3;
      p = 3;
      break; // Triangles
    default: 
      printf("ERREUR : Cas possibles : \n t=1 : Quadrangles\n t=2 : Triangles");
      return 1;
  }

  //------Nombre de noeuds------
	fprintf(Output, "%d\n", n1*n2);
	
	//------Calcul des coordonées------
	float h1 = (b-a) / (n1-1.0f);
	float h2 = (d-c) / (n2-1.0f);

	for (int i=0 ; i<n2 ; i++){
		float y = c + i*h2;
		for (int j=0 ; j<n1 ; j++){
			fprintf(Output, "%f %f\n",a+j*h1,y);
		}
	}
	
	//------Ecriture de : m t p q ------
	fprintf(Output, "%d %d %d %d\n", m, t, p, q); // Quadrangles
	
	//------Calcul des numéros globaux et numeros de reference des arretes------

	// Acclocation de nRefAr et calcul des arretes
 	int** nRefAr = alloctab_i(m,q);
 	etiqAr(t,n1,n2,nrefdom,nrefcot,nRefAr);


	int k=0; // Parcours de chaque element, de 0 à m. 
	// Quadrangle
	if (t==1) {
		for(int i=0; i<n2-1; i++){
			for(int j=1; j<n1; j++) {
				int indice = j + i*n1;

        // Numeros des noeuds de l'element k
				fprintf(Output, "%d %d %d %d ", indice+1, indice+1+n1, indice+n1, indice);
        // Numero de reference des arretes de l'element k
				fprintf(Output, "%d %d %d %d\n", nRefAr[k][0],nRefAr[k][1],nRefAr[k][2],nRefAr[k][3]); 
				
        k=k+1;
				}
			}
		}
	// Triangle
  else if (t==2) {
		for(int i=0; i<n2-1; i++){
			for(int j=1; j<n1; j++) {
				int indice = j + i*n1;

        // Sommets et arretes pour le triangle k
				fprintf(Output, "%d %d %d ", indice+1, indice+n1, indice);  
				fprintf(Output, "%d %d %d\n", nRefAr[k][0],nRefAr[k][1],nRefAr[k][2]); 
				k=k+1;

				fprintf(Output, "%d %d %d ", indice+n1, indice+1, indice+1+n1);
				fprintf(Output, "%d %d %d\n", nRefAr[k][0],nRefAr[k][1],nRefAr[k][2]); 
				k=k+1;
			}
		}
	}

	// Fermeture des fichiers
	fclose(Output);
	fclose(Donnees);
	freetab(nRefAr);
  return 0;
}
