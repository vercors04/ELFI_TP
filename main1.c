/*
* POUR COMPILER LE PROGRAMME ET CREER L'EXECUTABLE :
* -----------------------------------------
* gcc main1.c fct_maillage.c tab.c
* -----------------------------------------
*/

#include "header.h"

int main() {
  int mode_saisie;

  // Choix du mode d'entree des donnees
  printf("1. Lecture des donnees dans un fichier : input.txt \n2. Entree manuelle des donnees \n");
  scanf("%d",&mode_saisie);

  if (mode_saisie==2) modeSaisie2();

  char* nom_fichier_donnees="Donnees/ficInput.txt";
  char* nom_fichier_maillage1="Donnees/ficOutput.txt";

  // Création du maillage
  if (maillage(nom_fichier_donnees,nom_fichier_maillage1)) return 1;

  // Lecture du maillage
  char* nom_fichier_maillage2="Donnees/car1x1t_1";
  int typel, nbtng, nbtel, nbneel, nbaret;
  float** coord;
  int **ngnel,**nRefAr;
  if (lecfima(nom_fichier_maillage2, &typel, &nbtng, &coord, &nbtel, &ngnel, &nbneel, &nbaret, &nRefAr)) return 1;
 
  // Liberation de la memoire
  freetab(coord);
  freetab(ngnel);
  freetab(nRefAr);

  coord=NULL;
  printf("\n %p",coord);
  return 0;
}


