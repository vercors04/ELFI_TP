#include <stdio.h>

#include "1_Maillage/maillage.h"
#include "3_Assemblage/assemblage.h"
#include "4_Construction_SL/construction_SL.h"
#include "5_Resol_Post-Trait/dsmoapr.h"
#include "Utilitaire/utilitaires.h"
#include "forfun.h"


int nucas = 1; //pour solex

int main () {

  int typel; // Type des elements du maillage
  int nbtng; // Nombre de noeuds géométriques
  int nbtel; // Nombre d'elements du maillage
  int nbneel; // Nombre de noeuds geometriques par element
  int nbaret; // Nombre d'aretes par element
  int** ngnel; // Numeros globaux des noeuds des elements
  int** nRefAr; // Numeros de reference associes aux aretes
  float** coord; // Coordonnees des noeuds geometriques

  char* ficmai = "../Donnees_5/Maillages/d1t1_2";

  if (lecfima(ficmai, &typel, &nbtng, &coord, &nbtel, &ngnel, &nbneel, &nbaret, &nRefAr)){
    printf("ERREUR : lecture du fichier de maillage");
    return 1;
  }

  int nbRefD0 = 4;
  int nbRefD1 = 0;
  int nbRefF1 = 0;
  int nRefDom = 0;
  int numRefD0[] = {1, 2, 3, 4};
  int numRefD1[] = {0};
  int numRefF1[] = {0};
  
  // On stocke ces valeurs dans un tableau pour diminuer le nombre d'arguments
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



  float* Matrice    = callocvec_f(NbLign+NbCoef);
  float* SecMembre  = callocvec_f(NbLign);
  float* ValDLDir   = callocvec_f(NbLign);
  int*   AdPrCoefLi = callocvec_i(NbLign);
  int*   AdSuccLi   = callocvec_i(NbCoef);
  int*   NumCol     = callocvec_i(NbCoef);
  int*   NumDLDir   = allocvec_i(NbLign);
  for (int i=1; i<NbLign+1; i++) NumDLDir[i-1]=i;

  int*   AdPrCoefLiO;
  int*   NumColO;
  float* MatriceO;
  float* SecMembreO;

  int*   Profil;
  float* MatProf;

  float* U;
  float* UEX;

  int stop = 0, choix = 0;
  int assemb = 0, assemb0 = 0, assembP = 0, resol = 0, exacte = 0;


  while (!stop) {
      
    printf("\n ___________________________________ \
            \n| 1. ASSEMBLER LE SYSTEME           |\
            \n| 2. AFFICHER LE SYSTEME ASSEMBLE   |\
            \n| 3. CONSTRUIRE LA S.M.O            |\
            \n| 4. AFFICHER LA S.M.O              |\
            \n| 5. CONSTRUIRE LA STRUCTURE PROFIL |\
            \n| 6. AFFICHER LA STRUCTURE PROFIL   |\
            \n| 7. RÉSOUDRE LE SYSTÈME (CHOLESKY) |\
            \n| 8. CALCULER LA SOLUTION EXACTE    |\
            \n| 9. AFFICHER L'ERREUR              |\
            \n| 10. QUITTER                       |\
            \n|___________________________________|\n\
            \n> ");

     if (scanf("%d", &choix) != 1) {
      printf("ERREUR : tapez un entier\n");
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

      if (assemb0){
        freevec(MatriceO);
        freevec(SecMembreO);
        freevec(AdPrCoefLiO);
        freevec(NumColO);
      }
      if (assembP) {
        freevec(Profil);
        freevec(MatProf);
      }
      if (resol) freevec(U);
      if (exacte) freevec(UEX);
      return 1;
    } 
    
    switch (choix) {
      case 1:
        assemblage(typel, nbtng, coord, nbtel, ngnel, nbneel, nbaret, nRefAr, 
	               nbRef, nRefDom, numRefD0, numRefD1, numRefF1, NbLign, 
	               NbCoef, Matrice, SecMembre, AdPrCoefLi, AdSuccLi, NumCol, 
                 ValDLDir, NumDLDir);
        printf("\n------Assemblage termine------\n\n");
        assemb=1;
        break;

      case 2:
        if (!assemb){
          printf("ERREUR : assembler avant d'afficher\n\n");
          continue;
        }
        affsmd_ (&NbLign, AdPrCoefLi, NumCol, AdSuccLi, Matrice, SecMembre,
                 NumDLDir, ValDLDir);
        break;

      case 3:
        if (!assemb) {
          printf("ERREUR : assembler avant de construire la SMO\n\n");
          continue;
        }
        if (assemb0){
          freevec(MatriceO);
          freevec(SecMembreO);
          freevec(AdPrCoefLiO);
          freevec(NumColO);
        }
        AdPrCoefLiO = callocvec_i(NbLign);
        NumColO     = callocvec_i(NbCoef);
        MatriceO    = callocvec_f(NbLign+NbCoef);
        SecMembreO  = callocvec_f(NbLign);

        dSMDaSMO (NbLign, AdPrCoefLi, NumCol, AdSuccLi, Matrice, SecMembre, 
                  NumDLDir, ValDLDir, AdPrCoefLiO, NumColO, MatriceO, SecMembreO);
        printf("\n------SMD vers SMO termine------\n\n");
        assemb0=1;
        break;

      case 4:
        if (!assemb0){
          printf("ERREUR : construire la SMO avant d'afficher\n\n");
          continue;
        }
        affsmo_(&NbLign, AdPrCoefLiO, NumColO, MatriceO, SecMembreO);
        break;

      case 5:
        if (!assemb0){
          printf("ERREUR : construire la SMO avant de construire la structure Profil\n\n");
          continue;
        }

        if (assembP) {
          freevec(Profil);
          freevec(MatProf);
        }
        
        int longProfilMat = dSMOaLongPR2(NbLign, AdPrCoefLiO, NumColO, MatriceO);

        Profil = allocvec_i(NbLign);
        MatProf = callocvec_f(longProfilMat);
        dSMOaPR2(NbLign, AdPrCoefLiO, NumColO, MatriceO, Profil, MatProf);
        
        printf("\n------SM0 vers PROFIL termine------\n\n");

        assembP = 1;
        break;

      case 6:
        if (!assembP){
          printf("ERREUR : assembler avant d'afficher\n\n");
          continue;
        }

        int impfch_Test = 0;
        impmpr_(&impfch_Test, &NbLign, Profil, MatProf, MatProf+NbLign);
        break;

      case 7 :
        if (!assembP){
          printf("ERREUR : assembler avant d'afficher\n\n");
          continue;
        }
        if (resol) freevec(U);
        U = allocvec_f(NbLign);
        resolsyst(NbLign, longProfilMat, Profil, MatProf, SecMembreO, U);
        printf("\n------Resolution Cholesky terminee------\n\n");
        resol = 1;
        break;

      case 8 :
        if (exacte) freevec(UEX);
        UEX = allocvec_f(NbLign);
        CalSol (NbLign, coord, UEX);
        printf("\n------Calcul solution exacte UEX terminee------\n\n");
        exacte = 1;
        break;

      case 9 :
        if (!resol && !exacte) {
          printf("ERREUR : resoudre le système et calculer la solution exacte d'abord\n\n");
          continue;
        }
        else if (!resol) {
          printf("ERREUR : resoudre le système d'abord\n\n");
          continue;
        }
        else if (!exacte) {
          printf("ERREUR : calculer la solution exacte d'abord\n\n");
          continue;
        }

        int impfch_Aff = 0;
        affsol_(&NbLign, &coord[0][0], U, UEX, &impfch_Aff);
        
        break;

      case 10:
        stop = 1;
        printf("\nFermeture du programme.\n");
        break;

      default:
        printf("\nChoisir 1, 2, 3, 4, 5, 6, 7, 8, 9 ou 10\n");
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
  
  if (assemb0){
    freevec(MatriceO);
    freevec(SecMembreO);
    freevec(AdPrCoefLiO);
    freevec(NumColO);
  }
  if (assembP) {
    freevec(Profil);
    freevec(MatProf);
  }
  if (resol) freevec(U);
  if (exacte) freevec(UEX);

  return 0;
  
}
