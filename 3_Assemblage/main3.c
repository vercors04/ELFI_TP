


int main (){

  int typel; // Type des elements du maillage
  int nbtng; // Nombre de noeuds géométriques
  int nbtel; // Nombre d'elements du maillage
  int nbneel; // Nombre de noeuds geometriques par element
  int nbaret; // Nombre d'aretes par element
  int** ngnel; // Numeros globaux des noeuds des elements
  int** nRefAr; // Numeros de reference associes aux aretes
  float** coord; // Coordonnees des noeuds geometriques

  char* ficmai = "../Donnees_1/car1x1t_1";

  if (lecfima(ficmai, &typel, &nbtng, &coord, &nbtel, &ngnel, &nbneel, &nbaret, &nRefAr)){printf("erreur lecture du fichier de maillage");
    return 1;
  }

  float** coordElem = alloctab_f(nbneel,2);

  int nbRefD0 = 1;
  int nbRefD1 = 1;
  int nbRefF1 = 2;
  int nRefDom = 0;
  int numRefD0[] = {1};
  int numRefD1[] = {4};
  int numRefF1[] = {2,3};

  int nbRef[] = {nbRefD0, nbRefD1, nbRefF1};

  int nbLign = nbtng;
  int NbCoef = nbtng * 2*typel * 2;
  int* Matrice = callocvec_i((**2)); // Surestimation : 
					       //    Triangle : 6*nb-noeuds
					       //    Quadrangle : 8*nb-noeuds 
  int* AdPrCoefLi = callocvec_i(());

  assemblage(typel, nbtng, coord, nbtel, ngnel, nbneel, nbaret, nRefAr, 
	     nbRef[3], nRefDom, numRefD0[], numRefD1[], numRefF1[], NbLign, 
	     NbCoef, Matrice, AdPrCoefLi, AdSuccLi, NumCol);


}
