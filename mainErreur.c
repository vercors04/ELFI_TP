#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //pour la fonction chdir

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

int main() {

    int typel;
    printf("Entrez le numéro du cas (1, 2, 3) ? \n");
    scanf("%d", &nucas);
    printf("\nEntrez le numéro du domaine (1 ou 2) ? \n");
    scanf("%d", &nudom);
    printf("\nEntrez le Type elements (1=quadrangle, 2=triangle) ? \n");
    scanf("%d", &typel);

    /* --Chargement du maillage--*/

    int tailles_maillage[] = {2, 4, 8, 16, 32, 64};
    int nb_tailles = 6;
    char lettreEl = 'a';
    if (typel == 1) {
        lettreEl = 'q';
    } else if (typel == 2) {
        lettreEl = 't';
    } else {
        printf("ERREUR : type element = 1 ou 2\n");
        return 1;
    }

    chdir("../Resultats"); //Pour avoir les resultats dans un autre dossier

    //supression du fichier dans le dossier resultat si il existe deja
    char nomFic[20];
    //sprintf fonctionne comme printf mais écrit dans une variable
    sprintf(nomFic, "fort.%d", (nudom*100)+(nucas*10)+typel);
    remove(nomFic);

    char ficmai[50]; //reserve 50 octets en mémoire (talle des lettres en mémoire ?)
    for (int i = 0; i < nb_tailles; i++) {
        //on construit "dynamiquement" le nom du fichier de maillage
        sprintf(ficmai, "../Donnees_5/Maillages/d%d%c1_%d", nudom, lettreEl, tailles_maillage[i]);
        printf("\n maillage actuel : %s \n", ficmai);

        int nbtng; // Nombre de noeuds géométriques
        int nbtel; // Nombre d'elements du maillage
        int nbneel; // Nombre de noeuds geometriques par element
        int nbaret; // Nombre d'aretes par element
        int** ngnel; // Numeros globaux des noeuds des elements
        int** nRefAr; // Numeros de reference associes aux aretes
        float** coord; // Coordonnees des noeuds geometriques
        
        if (lecfima(ficmai, &typel, &nbtng, &coord, &nbtel, &ngnel, &nbneel, &nbaret, &nRefAr)){
            printf("ERREUR : lecture du fichier de maillage\n");
            return 1;
        }

        /* --Initialisation des conditions aux bords suivant le cas ET le domaine-- */
        int nRefDom = 0;
        int nbRefD0 = 0, nbRefD1 = 0, nbRefF1 = 0;
        int numRefD0[4] = {0}, numRefD1[4] = {0}, numRefF1[4] = {0};

        if (nudom == 1) {
            if (nucas == 1 || nucas == 2) {
                nbRefD0 = 4;
                numRefD0[0] = 1;
                numRefD0[1] = 2;
                numRefD0[2] = 3;
                numRefD0[3] = 4;
            } else if (nucas == 3) {
                nbRefF1 = 4;
                numRefF1[0] = 1;
                numRefF1[1] = 2;
                numRefF1[2] = 3;
                numRefF1[3] = 4;
            } else {
                printf("\nErreur : nucas %d non existant pour le Domaine 1, choisissez entre 1, 2 ou 3.\n\n", nucas);
                return 1;
            }
        } else if (nudom == 2) {
            if (nucas == 1 || nucas == 2) {
                nbRefD0 = 2;
                nbRefD1 = 2;
                numRefD0[0] = 1;
                numRefD0[1] = 4;
                numRefD1[0] = 2;
                numRefD1[1] = 3;
            } else if (nucas == 3) {
                nbRefD1 = 2;
                nbRefF1 = 2;
                numRefD1[0] = 1;
                numRefD1[1] = 4;
                numRefF1[0] = 2;
                numRefF1[1] = 3;
            } else {
                printf("\nErreur : nucas %d non existant pour le Domaine 2, choisissez entre 1, 2 ou 3.\n\n", nucas);
                return 1;
            }
        } else {
            printf("Erreur : nom de fichier non attendu");
            return 1;
        }

        // On stocke ces valeurs dans un tableau pour diminuer le nombre d'arguments
        int nbRef[] = {nbRefD0, nbRefD1, nbRefF1};

        /* ---Allocation pour la structure morse desordonneee---*/

        int NbLign = nbtng, NbCoef; // 
        // Surestimation de NbCoef pour la longueur de LMat
        if (1 == typel) {
            NbCoef = nbtng * 8; // Quadrangle : 8 * nb-noeuds
        } else if (2 == typel) {
            NbCoef = nbtng * 6; // Triangle : 6 * nb-noeuds
        } else {
            printf("ERREUR : typel != 1 ou 2");
            return 1;
        }

        float* Matrice = callocvec_f(NbLign + NbCoef);
        float* SecMembre = callocvec_f(NbLign);
        float* ValDLDir = callocvec_f(NbLign);
        int* AdPrCoefLi = callocvec_i(NbLign);
        int* AdSuccLi = callocvec_i(NbCoef);
        int* NumCol = callocvec_i(NbCoef);
        int* NumDLDir = allocvec_i(NbLign);
        for (int i = 1; i < NbLign + 1; i++) NumDLDir[i - 1] = i;
        int NbCoef2;

        int* AdPrCoefLiO;
        int* NumColO;
        float* MatriceO;
        float* SecMembreO;

        int* Profil;
        float* MatProf;

        float* U;
        float* UEX;


        /*------------assemblage---------------*/
        assemblage(typel, coord, nbtel, ngnel, nbneel, nbaret, nRefAr,
                   nbRef, nRefDom, numRefD0, numRefD1, numRefF1, NbLign,
                   NbCoef, Matrice, SecMembre, AdPrCoefLi, AdSuccLi, NumCol,
                   ValDLDir, NumDLDir);
        printf("\n-Assemblage termine-\n");
        NbCoef2 = AdPrCoefLi[NbLign - 1];



        /*------------Construction SMO---------------*/
        AdPrCoefLiO = callocvec_i(NbLign);
        NumColO = callocvec_i(NbCoef2);
        MatriceO = callocvec_f(NbLign + NbCoef2);
        SecMembreO = callocvec_f(NbLign);

        dSMDaSMO(NbLign, AdPrCoefLi, NumCol, AdSuccLi, Matrice, SecMembre,
                 NumDLDir, ValDLDir, AdPrCoefLiO, NumColO, MatriceO, SecMembreO);
        printf("\n-SMD vers SMO termine-\n");



        /*------------SMO a Profil---------------*/
        int longProfilMat = dSMOaLongPR2(NbLign, AdPrCoefLiO, NumColO);

        Profil = allocvec_i(NbLign);
        MatProf = callocvec_f(longProfilMat);
        dSMOaPR2(NbLign, AdPrCoefLiO, NumColO, MatriceO, Profil, MatProf, longProfilMat);

        printf("\n-SM0 vers PROFIL termine-\n");



        /*------------Resolution Cholesky---------------*/
        U = allocvec_f(NbLign);
        resolsyst(NbLign, longProfilMat, Profil, MatProf, SecMembreO, U);
        printf("\n-Resolution Cholesky terminee-\n");



        /*------------Calcul solution Exacte---------------*/
        UEX = allocvec_f(NbLign);
        CalSol(NbLign, coord, UEX);
        printf("\n-Calcul solution exacte UEX terminee-\n");



        /*------------Calcul erreur et affichage---------------*/
        int impfch_Aff = (nudom * 100) + (nucas * 10) + typel;
        /*nom du fichier de sortie, par ex :
        132 = domaine 1, cas 3 avec maillages par triangle
        211 = domaine 2, cas 1 avec maillage quadrangle
        */
        affsol_(&NbLign, &coord[0][0], U, UEX, &impfch_Aff);



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

        freevec(MatriceO);
        freevec(SecMembreO);
        freevec(AdPrCoefLiO);
        freevec(NumColO);

        freevec(Profil);
        freevec(MatProf);
        freevec(U);
        freevec(UEX);

    }
    chdir("../Executables"); //retour dans le dossier executable

    return 0;
}