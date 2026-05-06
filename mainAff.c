#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "1_Maillage/maillage.h"
#include "2a_ElementaireA/elementairesa.h"
#include "2b_ElementaireB/elementairesb.h"
#include "3_Assemblage/assemblage.h"
#include "4_Construction_SL/construction_SL.h"
#include "5_Resol_Post-Trait/dsmoapr.h"
#include "Utilitaire/utilitaires.h"
#include "forfun.h"


int nucas = 1; 
int nudom = 1;

int main () {

  /* --------------------------------------------------------
                    Chargement du maillage
    --------------------------------------------------------*/

  int typel; // Type des elements du maillage
  printf("Entrez le numéro du cas (1, 2, 3) : \n");
  scanf("%d", &nucas);

  if (nucas < 1 || nucas > 3){
    printf("ERREUR : numero de cas = 1, 2 ou 3\n");
    return 1;
  }
    
  printf("\nEntrez le numéro du domaine (1 ou 2) : \n");
  scanf("%d", &nudom);

  if (nudom < 1 || nudom > 2){
    printf("ERREUR : numero de domaine = 1 ou 2\n");
    return 1;
  }

  printf("\nEntrez le Type elements (1=quadrangle, 2=triangle) : \n");
  scanf("%d", &typel);

  char lettreEl = 'a';
  if (typel == 1) {
    lettreEl = 'q';
  } else if (typel == 2) {
    lettreEl = 't';
  } else {
    printf("ERREUR : type element = 1 ou 2\n");
    return 1;
  }

  int h; // pas
  printf("\nEntrez le numéro du pas (2, 4, 8, 16, 32 ou 64) : \n");
  scanf("%d", &h);

  if (h != 2 && h != 4 && h != 8 && h != 16 && h != 32 && h != 64) {
    printf("ERREUR : numero de pas = 2, 4, 8, 16, 32 ou 64\n");
    return 1;
  }
  
  int nbtng; // Nombre de noeuds géométriques
  int nbtel; // Nombre d'elements du maillage
  int nbneel; // Nombre de noeuds geometriques par element
  int nbaret; // Nombre d'aretes par element
  int** ngnel; // Numeros globaux des noeuds des elements
  int** nRefAr; // Numeros de reference associes aux aretes
  float** coord; // Coordonnees des noeuds geometriques

  char ficmai[40]; 
  sprintf(ficmai, "../Donnees_5/Maillages/d%d%c1_%d", nudom, lettreEl, h);

  if (lecfima(ficmai, &typel, &nbtng, &coord, &nbtel, &ngnel, &nbneel, &nbaret, &nRefAr)){
    printf("ERREUR : lecture du fichier de maillage");
    return 1;
  }


  /* ----------------------------------------------------------------------
      Initialisation des conditions aux bords suivant le cas ET le domaine
     ---------------------------------------------------------------------- */ 
     
  int nRefDom = 0; 
  int nbRefD0 = 0, nbRefD1 = 0, nbRefF1 = 0;
  int numRefD0[4] = {0}, numRefD1[4] = {0}, numRefF1[4] = {0};

  if (nudom == 1) {
    if (nucas == 1 || nucas == 2) {
        nbRefD0 = 4;
        numRefD0[0] = 1; numRefD0[1] = 2; numRefD0[2] = 3; numRefD0[3] = 4;
    } 

    else if (nucas == 3) {
        nbRefF1 = 4;
        numRefF1[0] = 1; numRefF1[1] = 2; numRefF1[2] = 3; numRefF1[3] = 4;
    }
    else {
        printf("\nErreur : nucas %d non existant pour le Domaine 1, choisissez entre 1, 2 ou 3.\n\n", nucas);
        return 1;
    }
  }
   
  else if (nudom == 2) {
    if (nucas == 1 || nucas == 2) {
        nbRefD0 = 2;
        nbRefD1 = 2;
        numRefD0[0] = 1; numRefD0[1] = 4; 
        numRefD1[0] = 2; numRefD1[1] = 3; 
    } 

    else if (nucas == 3) {
        nbRefD1 = 2;
        nbRefF1 = 2;
        numRefD1[0] = 1; numRefD1[1] = 4;
        numRefF1[0] = 2; numRefF1[1] = 3; 
    }
    else {
        printf("\nErreur : nucas %d non existant pour le Domaine 2, choisissez entre 1, 2 ou 3.\n\n", nucas);
        return 1;
    }

  } 
  
  else {
      printf("Erreur : nom de fichier non attendu");
      return 1;
  }

  // On stocke ces valeurs dans un tableau pour diminuer le nombre d'arguments
  int nbRef[] = {nbRefD0, nbRefD1, nbRefF1};


  /* --------------------------------------------------------
         Allocation pour la structure morse desordonneee
     --------------------------------------------------------*/
 
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
  int NbCoef2;



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


  /* --------------------------------------------------------
           Menu et execution des differentes parties
    --------------------------------------------------------*/

  while (!stop) {
      
    printf("\n ____________________________________ \
            \n| 0. AFFICHER LE DETAIL DES ELEMENTS |\
            \n| 1. ASSEMBLER LE SYSTEME            |\
            \n| 2. AFFICHER LE SYSTEME ASSEMBLE    |\
            \n| 3. CONSTRUIRE LA S.M.O             |\
            \n| 4. AFFICHER LA S.M.O               |\
            \n| 5. CONSTRUIRE LA STRUCTURE PROFIL  |\
            \n| 6. AFFICHER LA STRUCTURE PROFIL    |\
            \n| 7. RÉSOUDRE LE SYSTÈME (CHOLESKY)  |\
            \n| 8. CALCULER LA SOLUTION EXACTE     |\
            \n| 9. AFFICHER L'ERREUR               |\
            \n| 10. QUITTER                        |\
            \n|____________________________________|\n\
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


      case 0:
        float** coordElem = (float**) malloc(nbneel * sizeof(float*));
        for (int i=0; i<nbtel; i++) {
          float** MatElem;
          float*  SMbrElem;
          float*  uDElem;  
          int*    NuDElem; 
          selectPts (nbneel, ngnel[i], coord, coordElem);

          cal1Elem (nRefDom, nbRefD0, numRefD0, nbRefD1, numRefD1, nbRefF1, numRefF1, typel,
                    nbneel, coordElem, nbaret, nRefAr[i], &MatElem, &SMbrElem, &NuDElem, &uDElem);

          impCalEl(i+1, typel, nbneel, MatElem, SMbrElem, NuDElem, uDElem);
          freetab(MatElem);
          freevec(SMbrElem);
          freevec(uDElem);
          freevec(NuDElem);
        }
        free (coordElem);
        break;


      case 1:
        assemblage(typel, coord, nbtel, ngnel, nbneel, nbaret, nRefAr, 
	               nbRef, nRefDom, numRefD0, numRefD1, numRefF1, NbLign, 
	               NbCoef, Matrice, SecMembre, AdPrCoefLi, AdSuccLi, NumCol, 
                 ValDLDir, NumDLDir);
        printf("\n------Assemblage termine------\n\n");
        assemb=1;
        NbCoef2 = AdPrCoefLi[NbLign - 1];
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
        NumColO     = callocvec_i(NbCoef2);
        MatriceO    = callocvec_f(NbLign+NbCoef2);
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
        
        int longProfilMat = dSMOaLongPR2(NbLign, AdPrCoefLiO, NumColO);

        Profil = allocvec_i(NbLign);
        MatProf = callocvec_f(longProfilMat);
        dSMOaPR2(NbLign, AdPrCoefLiO, NumColO, MatriceO, Profil, MatProf,longProfilMat);
        
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
        printf("\nChoisir 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ou 10\n");
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
