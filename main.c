#include "header.h"

int main() {
  int  n1, n2, t, m, q, mode_saisie;
  double a, b, c, d;

  // Choix du mode d'entree des donnees
  printf("1. Lecture des données dans le fichier : input.txt \n2. Entrée manuelle des données \n");
  scanf("%d",&mode_saisie);
  mode_saisie = mode_saisie - 1;

  if (!mode_saisie) {

    // Ouverture du fichier
    FILE *donnees = fopen("input.txt", "r");
    // Test du bon deroulement de l'ouverture
    if (donnees==NULL) {
      printf("ERREUR : Le fichier n'a pas pu etre ouvert.\n");
      return 1;
    }
    // Lecture du fichier et on met dans les var
    fscanf(donnees, "%lf %lf %lf %lf %d %d %d", &a, &b, &c, &d, &n1, &n2, &t);
    // Fermeture du fichier
    fclose(donnees);
  }
  else {

    printf("Inserez les donnees :\n\nDomaine [a,b]x[c,d] (Entrez les valeures de a b c d) :\n");
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    printf("\nNombres de points n1 et n2 :\n");
    scanf("%d %d", &n1, &n2);
    printf("\nType des elements a construire (1. Quadrangles - 2. Triangles) : \n");
    scanf("%d", &t);
  }
 


  // Affichage des donnees
  printf("Domaine : [%lf,%lf]x[%lf,%lf]\n",a,b,c,d);
  printf("Nombres de points n1 = %d\n",n1);
  printf("Nombres de points n2 = %d\n",n2);
  if (t==1) printf("Type : Quadrangles\n");
  else if (t==2) printf("Type : Triangles\n");
  


  maillage(a,b,c,d,n1,n2,t,nrefcot); //Lire le fichier et mettre dans nrefcot les différentes valeurs (tableau de 5 éléments donc)

  return 0;
}




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