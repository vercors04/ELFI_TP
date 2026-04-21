#include <stdio.h>
#include "../Utilitaire/utilitaires.h"

int lecfima(char *ficmai, int *ptypel, int *pnbtng, float ***pcoord, int *pnbtel, int ***pngnel, int *pnbneel,int *pnbaret, int ***pnRefAr){
  // Ouverture du fichier de maillage à lire
  FILE *pfichier_maillage = fopen(ficmai,"r");
  // Test du bon deroulement de l'ouverture
    if (pfichier_maillage==NULL) { 
      printf("ERREUR : Le fichier ficmai n'a pas pu etre ouvert.\n");
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
  fscanf(pfichier_maillage, "%d %d %d %d\n", pnbtel, ptypel, pnbneel, pnbaret);
  
  
  // Allocation tableau ngel
  *pngnel = alloctab_i(*pnbtel,*pnbneel);
  *pnRefAr = alloctab_i(*pnbtel,*pnbneel);
  // Recuperation des numeros globaux et numeros de reference
  for (int i=0;i<*pnbtel;i++) {
    for (int j=0;j<*pnbneel;j++) {
      fscanf(pfichier_maillage, "%d ",&(*pngnel)[i][j]);
    }
    for (int j=0;j<*pnbneel;j++) {
      fscanf(pfichier_maillage, "%d ",&(*pnRefAr)[i][j]);
    }
    fscanf(pfichier_maillage, "\n");
  }

	fclose(pfichier_maillage);

	return 0;
}




