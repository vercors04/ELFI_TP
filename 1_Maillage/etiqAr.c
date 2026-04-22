#include <stdio.h>

int etiqAr (int t, int n1, int n2, int nrefdom, const int *nrefcot, int **nRefAr){


	//calcul de m
	int m, q;

	switch (t) {
		
    case 1:
      m = (n1-1) * (n2-1); 
      q = 4;
      break; // Quadrangles
    case 2:
      m = 2 * (n1-1) * (n2-1); 
      q = 3;
      break; // Triangles
    default:
      printf("ERREUR : Cas possibles : \n t=1 : Quadrangles\n t=2 : Triangles");
      return 1;
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
		  nRefAr[i][3]     = nrefcot[0];
		  nRefAr[m-1-i][1] = nrefcot[2];
    }
	  // Parcours des carrés sur les cotés du maillage
	  for (int i=0; i<m; i=i+n1-1){
		  nRefAr[i][2]     = nrefcot[3];
		  nRefAr[m-1-i][0] = nrefcot[1];
	  }
	}
	// Calcul des arrêtes triangles
  else if (t==2) {
	  // Parcours des triangles en haut et en bas du maillage
	  for (int i=0; i<2*(n1-1); i=i+2){
		  nRefAr[i][2]     = nrefcot[0];
		  nRefAr[m-1-i][2] = nrefcot[2];
	  }
	  // Parcours des triangles sur les cotés du maillage 
	  for (int i=0; i<m; i=i+2*(n1-1)){
		  nRefAr[i][1]     = nrefcot[3];
		  nRefAr[m-1-i][1] = nrefcot[1];
	  }
	}
	return 0;
}

