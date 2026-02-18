#include "maillage.h"
#include "../Utilitaire/utilitaires.h"


int maillage (char *ficInput, char *ficOutput ) {

// Ouverture des fichiers input et output
  FILE *Donnees = fopen(ficInput, "r");
   if (Donnees==NULL) { 
      printf("ERREUR : Le fichier ficInput.txt n'a pas pu etre ouvert.\n");
      return 1;  
  }

  FILE *Output = fopen (ficOutput, "w");
   if (Output==NULL) { 
      printf("ERREUR : Le fichier ficOutput.txt n'a pas pu etre ouvert.\n");
      return 1;  
  }

	int  n1, n2, t, nrefdom, nrefcot[4], m, q, p;
  float a, b, c, d;

  //------Lecture du fichier------ 
  fscanf(Donnees, "%f %f %f %f %d %d %d %d", &a, &b, &c, &d, &n1, &n2, &t, &nrefdom);
  for (int i = 0; i < 4; i++) {
    fscanf(Donnees, "%d", &nrefcot[i]);
  }

	// Affichage des donnees (optionel)
  printf("Domaine : [%f,%f]x[%f,%f]\n",a,b,c,d);
  printf("Nombres de points n1 = %d\n",n1);
  printf("Nombres de points n2 = %d\n",n2);
  if (t==1) printf("Type : Quadrangles\n");
  else if (t==2) printf("Type : Triangles\n");

	//------Calcul de m p q------
	switch (t) {
    case 1: m=(n1-1)*(n2-1); q=4; p=4; break; // Quadrangles
    case 2: m=2*((n1-1)*(n2-1)); q=3; p=3; break; // Triangles
    default: printf("ERREUR : Cas possibles : \n t=1 : Quadrangles\n t=2 : Triangles");return 1;
  }

  //------Nombre de noeuds------
	fprintf(Output, "%d\n", n1*n2);
	
	//------Calcul des coordonées------
	float h1 = (b-a)/(n1-1.0f);
	float h2 = (d-c)/(n2-1.0f);

	for (int i=0 ; i<n2 ; i++){
		float y = c + i*h2;
		for (int j=0 ; j<n1 ; j++){
			fprintf(Output, "%f %f\n",a+j*h1,y);
		}
	}
	
	//------Ecriture de : m t p q ------
	fprintf(Output, "%d %d %d %d\n", m, t, p, q); //Quadrangles
	

	
	//------Calcul des numéros globaux et numeros de reference des arretes------

	//acclocation de nRefAr et calcul des arretes, a changer si fct allotab_i
 	int *nRefAr_alloc = (int *) malloc(m * q * sizeof(int));
 	int **nRefAr = (int **) malloc(m * sizeof(int *));
 	for (int i = 0; i < m; i++) { 
		nRefAr[i] = &nRefAr_alloc[i * q];
 	}

 	etiqAr(t,n1,n2,nrefdom,nrefcot,nRefAr);


	int k=0; // Parcours de chaque element, de 0 à m. 
	// Quadrangle
	if (t==1) {
		for(int i=0; i<n2-1; i++){
			for(int j=1; j<n1; j++) {
				int indice = j + i*n1;

        // Numeros des noeuds de l'element k
				fprintf(Output, "%d %d %d %d ", indice+1, indice+1+n1, indice+n1, indice);
        // Numero de reference des arretes de l'element k
				fprintf(Output, "%d %d %d %d\n", nRefAr[k][0],nRefAr[k][1],nRefAr[k][2],nRefAr[k][3]); 
				
        k=k+1;
				}
			}
		}

	// Triangle
  else if (t==2) {
		for(int i=0; i<n2-1; i++){
			for(int j=1; j<n1; j++) {
				int indice = j + i*(n1-1);
        // Sommets et arretes pour le triangle k
				fprintf(Output, "%d %d %d ", indice+1, indice+n1, indice);  
				fprintf(Output, "%d %d %d\n", nRefAr[k][0],nRefAr[k][1],nRefAr[k][2]); 
				k=k+1;

				fprintf(Output, "%d %d %d ", indice+n1, indice+1, indice+1+n1);
				fprintf(Output, "%d %d %d\n", nRefAr[k][0],nRefAr[k][1],nRefAr[k][2]); 
				k=k+1;
			}
		}
	}	

	// Fermeture des fichiers
	fclose(Output);
	fclose(Donnees);
	freetab(nRefAr);
  return 0;
}



int etiqAr (int t, int n1, int n2, int nrefdom, const int *nrefcot, int **nRefAr){


	//calcul de m
	int m, q;

	switch (t) {
		
    case 1: m=(n1-1)*(n2-1); q=4; break; // Quadrangles
    case 2: m=2*((n1-1)*(n2-1)); q=3; break; // Triangles
    default: printf("ERREUR : Cas possibles : \n t=1 : Quadrangles\n t=2 : Triangles");return 1;

	}

	// Remplissage de tout les elements à 0
	

	for (int i = 0; i < m; i++) {
    for (int j = 0; j < q; j++) {
      nRefAr[i][j] = nrefdom;
		}
	}

	// Calcul des arrêtes quadrangle 
	if (t==1) {
    // Parcours des carrés en haut et en bas du maillage
    for (int i=0; i<n1-1; i++){
		nRefAr[i][3] = nrefcot[0];
		nRefAr[m-1-i][1] = nrefcot[2];
    }
	  // Parcours des carrés sur les cotés du maillage
	  for (int i=0; i<m; i=i+n1-1){
		  nRefAr[i][2] = nrefcot[3];
		  nRefAr[m-1-i][0] = nrefcot[1];
	  }
	}

	// Calcul des arrêtes triangles
  else if (t==2) {
	  // Parcours des triangles en haut et en bas du maillage
	  for (int i=0; i<2*(n1-1); i=i+2){
		  nRefAr[i][2] = nrefcot[0];
		  nRefAr[m-1-i][2] = nrefcot[2];
	  }
	  // Parcours des triangles sur les cotés du maillage 
	  for (int i=0; i<m; i=i+2*(n1-1)){
		  nRefAr[i][1] = nrefcot[3];
		  nRefAr[m-1-i][1] = nrefcot[1];
	  }
	}
	return 0;
}



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

	/*
	Verif fichier lecfima
	*/


	/* 
	// Validation de la fonction
	FILE *verif = fopen("../Donnees_1/verif_lecfima.txt", "w"); 
	// Test du bon deroulement de l'ouverture
  if (verif==NULL) { 
    printf("ERREUR : Le fichier verif_lecfima.txt n'a pas pu etre ouvert.\n");
    return 1;
    }

  fprintf(verif, "%d\n",*pnbtng);

  for (int i=0; i<*pnbtng; i++){
    fprintf(verif, "%f %f\n", (*pcoord)[i][0], (*pcoord)[i][1]);
	}
	fprintf(verif, "%d %d %d %d\n", *pnbtel, *ptypel, *pnbneel, *pnbaret);

  for (int i=0;i<*pnbtel;i++) {
    for (int j=0;j<*pnbneel;j++) {
      fprintf(verif, "%d ",(*pngnel)[i][j]);
    }
    for (int j=0;j<*pnbneel;j++) {
      fprintf(verif, "%d ",(*pnRefAr)[i][j]);
    }
    fprintf(verif, "\n");
  }
	fclose(verif); */
	return 0;
}	




void modeSaisie2 () {
	int  n1, n2, t, nrefdom, nrefcot[4];
  float a, b, c, d;

	FILE *Donnees = fopen("../Donnees_1/ficInput.txt", "w");
    // Test du bon deroulement de l'ouverture
    if (Donnees==NULL) { 
      printf("ERREUR : Le fichier n'a pas pu etre ouvert.\n");
	  return;
    }

	printf("Inserez les donnees :\nDomaine [a,b]x[c,d] (Entrez les valeures de a b c d) :\n");
  scanf("%f %f %f %f", &a, &b, &c, &d);
	fprintf(Donnees,"%f %f %f %f\n", a, b, c, d);

  printf("\nNombres de points n1 et n2 :\n");
  scanf("%d %d", &n1, &n2);
	fprintf(Donnees,"%d %d\n", n1, n2);

  printf("\nType des elements a construire (1. Quadrangles - 2. Triangles) : \n");
  scanf("%d", &t);
	fprintf(Donnees,"%d\n",t);

  printf("\nNuméro de reference du domaine\n");
  scanf("%d", &nrefdom);
	fprintf(Donnees,"%d ", nrefdom);

  for (int i = 1; i < 5; i++) {
    printf("\nNuméro de reference du cote %d : \n",i);
		scanf("%d", &nrefcot[i-1]);
		fprintf(Donnees,"%d ", nrefcot[i-1]);	
  }

	fclose(Donnees);
}
