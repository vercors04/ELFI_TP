#include "../Utilitaire/utilitaires.h"
#include "../1_Maillage/maillage.h"
#include "assemblage.h"
#include "../forfun.h"

int main (){

  int typel; // Type des elements du maillage
  int nbtng; // Nombre de noeuds géométriques
  int nbtel; // Nombre d'elements du maillage
  int nbneel; // Nombre de noeuds geometriques par element
  int nbaret; // Nombre d'aretes par element
  int** ngnel; // Numeros globaux des noeuds des elements
  int** nRefAr; // Numeros de reference associes aux aretes
  float** coord; // Coordonnees des noeuds geometriques

  char* ficmai = "../Donnees_1/car3x3t_3";

  if (lecfima(ficmai, &typel, &nbtng, &coord, &nbtel, &ngnel, &nbneel, &nbaret, &nRefAr)){
    printf("ERREUR : lecture du fichier de maillage");
    return 1;
  }

  int nbRefD0 = 1;
  int nbRefD1 = 1;
  int nbRefF1 = 2;
  int nRefDom = 0;
  int numRefD0[] = {1};
  int numRefD1[] = {4};
  int numRefF1[] = {2,3};

  int nbRef[] = {nbRefD0, nbRefD1, nbRefF1};

  int NbLign = nbtng, NbCoef; // 
  // Surestimation de NbCoef pour la longueur de LMat
  if (1==typel) {
    NbCoef = nbtng * 8; // Quadrangle : 8 * nb-noeuds
  }
  else if (2==typel) {
    NbCoef = nbtng * 6; // Triangle : 6 * nb-noeuds
  }
  else{
    printf("ERREUR : typel != 1 ou 2");
    return 1;
  }
  float* Matrice = callocvec_f(NbLign+NbCoef);
  float* SecMembre = callocvec_f(NbLign);
  float* ValDLDir = callocvec_f(NbLign);
  int* AdPrCoefLi = callocvec_i(NbLign);
  int* AdSuccLi = callocvec_i(NbCoef);
  int* NumCol = callocvec_i(NbCoef);
  int* NumDLDir = allocvec_i(NbLign);
  for (int i=1; i<NbLign+1; i++) NumDLDir[i-1]=1*i;
  
  int choix = 0;
  int assemb= 0;
  while (1) {
    printf("1. ASSEMBLER LE SYSTEME\n");
    printf("2. AFFICHER LE SYSTEME ASSEMBLE\n");
    printf("3. QUITTER\n");
        
    if (scanf("%d", &choix) != 1) {
      printf("tapez un entier\n");
      return 1;
    }

    if (choix == 1) {
      assemblage(typel, nbtng, coord, nbtel, ngnel, nbneel, nbaret, nRefAr, 
	     nbRef, nRefDom, numRefD0, numRefD1, numRefF1, NbLign, 
	     NbCoef, Matrice, SecMembre, AdPrCoefLi, AdSuccLi, NumCol, ValDLDir, NumDLDir);
      printf("Assemblage termine.\n");
      assemb=1;
    }

    else if (choix == 2) {
      if (assemb == 0){
        printf("ERREUR : assembler avant d'afficher\n\n");
        return 1;
      }
        affsmd_ (&NbLign, AdPrCoefLi, NumCol, AdSuccLi, Matrice, SecMembre, NumDLDir, ValDLDir);
      }

    else if (choix == 3) {
      printf("\nFermeture du programme.\n");
      break;
    }
  
    else {
      printf("\nChoisir 1, 2 ou 3.\n");
      }
    }
 

  

  freevec(Matrice);
  freevec(SecMembre);
  freevec(AdPrCoefLi);
  freevec(AdSuccLi);
  freevec(NumCol);
  freevec(ValDLDir);
  freevec(NumDLDir);

  freetab(coord);
  freetab(ngnel);
  freetab(nRefAr);
  
  return 0;
}
