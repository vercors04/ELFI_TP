#include "header.h"

int main() {
  int mode_saisie;

  // Choix du mode d'entree des donnees
  printf("1. Lecture des donnees dans le fichier : input.txt \n2. Entree manuelle des donnees \n");
  scanf("%d",&mode_saisie);

  if (mode_saisie==2) modeSaisie2();

    
  //ouverture des fichiers input et output et test
  FILE *Donnees = fopen("ficInput.txt", "r");
   if (Donnees==NULL) { 
      printf("ERREUR : Le fichier ficInput.txt n'a pas pu etre ouvert.\n");
      return 1;  
  }

  FILE *Output = fopen ("ficOutput.txt", "w");
   if (Output==NULL) { 
      printf("ERREUR : Le fichier ficOutput.txt n'a pas pu etre ouvert.\n");
      return 1;  
  }


  // Création du maillage
  maillage(Donnees,Output); 
 

  // Lecture du maillage
  //char *nom_fichier_maillage="ficOutput.txt";
  //int typel, nbtng, nbtel, nbneel, nbaret;
  //float **coord;
  //int **ngnel;
  //lecfima(nom_fichier_maillage, &typel, &nbtng, &coord, &nbtel, &ngnel, &nbneel, &nbaret, &nRefAr);
 
  // Liberation de la memoire
  /*
  free(coord[0]);
  free(coord);
  free(ngnel[0]);
  free(ngnel);
*/
  //freetab(coord);
  //freetab(ngnel);

  return 0;
}


