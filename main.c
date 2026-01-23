#include "header.h"

int main() {
  int  n1, n2, t, m, q, mode_saisie, nrefdom, nrefcot[4];
  double a, b, c, d;

  // Choix du mode d'entree des donnees
  printf("1. Lecture des données dans le fichier : input.txt \n2. Entrée manuelle des données \n");
  scanf("%d",&mode_saisie);

  if (mode_saisie==1) {

    // Ouverture du fichier
    FILE *donnees = fopen("input.txt", "r");
    // Test du bon deroulement de l'ouverture
    if (donnees==NULL) { 
      printf("ERREUR : Le fichier n'a pas pu etre ouvert.\n");
      return 1;
    }
    // Lecture du fichier et on met dans les var
    fscanf(donnees, "%lf %lf %lf %lf %d %d %d %d", &a, &b, &c, &d, &n1, &n2, &t, &nrefdom);
    for (int i = 0; i < 4; i++) {
        fscanf(donnees, "%d", &nrefcot[i]);
    }
    // Fermeture du fichier
    fclose(donnees);
    
  }
  else if (mode_saisie==2) {

    printf("Inserez les donnees :\n\nDomaine [a,b]x[c,d] (Entrez les valeures de a b c d) :\n");
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    printf("\nNombres de points n1 et n2 :\n");
    scanf("%d %d", &n1, &n2);
    printf("\nType des elements a construire (1. Quadrangles - 2. Triangles) : \n");
    scanf("%d", &t);
    printf("\nNuméro de référence du domaine \n");
    scanf("%d", &nrefdom);
    for (int i = 1; i < 5; i++) {
      printf("\nNuméro de référence du coté %d : \n",i);
      scanf("%d", &nrefcot[i-1]);
    }
  }
 


  // Affichage des donnees
  printf("Domaine : [%lf,%lf]x[%lf,%lf]\n",a,b,c,d);
  printf("Nombres de points n1 = %d\n",n1);
  printf("Nombres de points n2 = %d\n",n2);
  if (t==1) printf("Type : Quadrangles\n");
  else if (t==2) printf("Type : Triangles\n");
 
  // A remettre au propre, deplacer de la fct maillage vers main
  if (t==1) {
	  m=(n1-1)*(n2-1);
  	  q=4;
  }
  else if (t==2){
	  m=2*((n1-1)*(n2-1));
	  q=3;
  }

  // Allocation en memoire du tableau des numeros de reference des aretes 
  int *nRefAr_alloc = (int *) malloc(m * q * sizeof(int));
  int **nRefAr = (int **) malloc(m * sizeof(int *));
  for (int i = 0; i < m; i++) {	
	  nRefAr[i] = &nRefAr_alloc[i * q];
  }
  
  // Création du maillage
  maillage(a,b,c,d,n1,n2,t,nrefdom,nrefcot); 
  
  // Lecture du maillage
  FILE *pfichier_maillage = fopen("fichier.txt","r");
  if (pfichier_maillage==NULL){ 
      printf("ERREUR : Le fichier n'a pas pu etre ouvert.\n");
      return 1;
  }
  char *nom_fichier_maillage="fichier.txt";
  int typel, nbtng, nbtel, nbneel, nbaret;
  float coord[n1*n2][2], ngnel[m][q];
  lecfima(nom_fichier_maillage, &typel, &nbtng, coord[2], &nbtel, ngnel[m][q], &nbneel, &nbaret, nRefAr[m][q]);

  fclose(fichier_maillage);



  return 0;
}

/*----------retrait du main---------------- */

 // if (t==1) { //Quadrangles
	//   m = (n1-1)*(n2-1); 
	//   q = 4;
  // }
  // else if (t==2){ //Triangles
	//   m = ((n1-1)*(n2-1))*2;
	//   q = 3;
  // }
  // else {
	//   printf("ERREUR : pas de type d'elements correctement initialise");
	//   return 1;
  // }
  // int *nRefAr_alloc = (int *) calloc(m*q,sizeof(int));
  // int **nRefAr = (int **) malloc(m*sizeof(int*));
  // for(int i=0; i<m; i++) &nRefAr[i] = nRefAr_alloc[i*q];

  //--j'ai fait l'equivalent mais dans la fonction "maillage" (ex creation_fichier), comme ça le main est plus propre et ça reviens en même--
