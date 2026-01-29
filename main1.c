#include "header.h"

int main() {
  int mode_saisie;

  // Choix du mode d'entree des donnees
  printf("1. Lecture des donnees dans le fichier : input.txt \n2. Entree manuelle des donnees \n");
  scanf("%d",&mode_saisie);

  if (mode_saisie==2) modeSaisie2();

  char* nom_fichier_donnees="ficInput.txt";
  char* nom_fichier_maillage1="ficOutput.txt";
  /*
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
*/

  // Création du maillage
  maillage(nom_fichier_donnees,nom_fichier_maillage1);

  // Lecture du maillage
  char* nom_fichier_maillage2="ficOutput.txt";
  int typel, nbtng, nbtel, nbneel, nbaret;
  float** coord;
  int **ngnel,**nRefAr;
  lecfima(nom_fichier_maillage2, &typel, &nbtng, &coord, &nbtel, &ngnel, &nbneel, &nbaret, &nRefAr);
 
  // Liberation de la memoire
  freetab(coord);
  freetab(ngnel);
  freetab(nRefAr);

  return 0;
}


