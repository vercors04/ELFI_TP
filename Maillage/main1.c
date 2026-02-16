/*
* POUR COMPILER LE PROGRAMME ET CREER L'EXECUTABLE :
* -----------------------------------------
* Lancer main1.sh dans le dossier "Executables/"
* Attention : l'executable doit se trouver dans le dossier "Executables/"
* -----------------------------------------
*/

#include "maillage.h"
#include "../Utilitaire/utilitaires.h"

int main() {
  int mode_saisie;

  // Choix du mode d'entree des donnees
  printf("1. Lecture des donnees dans un fichier : input.txt \n2. Entree manuelle des donnees \n");
  scanf("%d",&mode_saisie);

  if (mode_saisie==2) modeSaisie2();

  char* nom_fichier_donnees="../Donnees_1/ficInput.txt";
  char* nom_fichier_maillage1="../Donnees_1/ficOutput.txt";

  // Création du maillage
  if (maillage(nom_fichier_donnees,nom_fichier_maillage1)) return 1;

  // Lecture du maillage
  char* nom_fichier_maillage2="../Donnees_1/car1x1t_1";
  int typel, nbtng, nbtel, nbneel, nbaret;
  float** coord;
  int **ngnel,**nRefAr;
  if (lecfima(nom_fichier_maillage2, &typel, &nbtng, &coord, &nbtel, &ngnel, &nbneel, &nbaret, &nRefAr)) return 1;
 
  // Liberation de la memoire
  freetab(coord);
  freetab(ngnel);
  freetab(nRefAr);
  return 0;
}


