#include <stdio.h>
#include <stdlib.h>

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
