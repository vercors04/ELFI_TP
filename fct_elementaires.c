#include "elementaires.h"

int ppquad(int t, float* poids, float** points){

  switch (t) {
    case 1: // Quadrangle
      // Assignation des valeurs des poids
      const float poids1 = 1.0f/36.0f;
      const float poids2 = 1.0f/9.0f;
      for (int i=0;i<4;i++) poids[i] = poids1; // w_i : i=1,..,4
      for (int i=4;i<8;i++) poids[i] = poids2; // w_i : i=5,..,8
      poids[8] = 4.0f/9.0f; // w_9

      // Assignation des valeurs des points
      points[0][0] =      1.0f; points[0][1] =         0; // x_1
      points[1][0] =      1.0f; points[1][1] =      1.0f; // x_2
      points[2][0] =         0; points[2][1] =      1.0f; // x_3
      points[3][0] =         0; points[3][1] =         0; // x_4
      points[4][0] =      1.0f; points[4][1] = 1.0f/2.0f; // x_5
      points[5][0] = 1.0f/2.0f; points[5][1] =      1.0f; // x_6
      points[6][0] =         0; points[6][1] = 1.0f/2.0f; // x_7
      points[7][0] = 1.0f/2.0f; points[7][1] =         0; // x_8
      points[8][0] = 1.0f/2.0f; points[8][1] = 1.0f/2.0f; // x_9
      break;

    case 2: // Triangle
      // Assignation des valeurs des poids
      for (int i=0;i<3;i++) poids[i] = 1.0f/6.0f; // w_i : i=1,2,3
 
      // Assignation des valeurs des points
      points[0][0] = 1.0f/2.0f; points[0][1] = 1.0f/2.0f; // x_1
      points[1][0] =         0; points[1][1] = 1.0f/2.0f; // x_2
      points[2][0] = 1.0f/2.0f; points[2][1] =         0; // x_3
      break;

    case 3:
      // Assignation des valeurs des poids
      poids[0] = 1.0f/6.0f; // w_1
      poids[1] = 1.0f/6.0f; // w_2
      poids[2] = 2.0f/3.0f; // w_3
      // Assignation des valeurs des points
      points[0][0] =      1.0f; // x_1
      points[1][0] =         0; // x_2
      points[2][0] = 1.0f/2.0f; // x_3
      break;
    
    default: printf("\nERREUR : fonction ppquad valeur de t != 1,2,3\n"); return -1;
  }
  return 0;
}

int q_associe(int t){
  int q;
  switch (t) {
    case 1: q=9; break; // Quadrangle
    case 2: q=3; break; // Triangle
    case 3: q=3; break; // Segment
    default: q=-1; // Valeur ne correspondant a aucun type
  }
  return q;
}


int calFbase (int t, float* point, float* vect){
  switch (t){
    case 1 : // Quadrangle
      vect[0] = point[0] - point[0] * point[1];
      vect[1] = point[0] * point[1];
      vect[2] = point[1] - point[0] * point[1];
      vect[3] = (1.0f - point[0]) * (1.0f - point[1]);
      break;

    case 2 : // Triangle
      vect[0] = point[0];
      vect[1] = point[1];
      vect[2] = 1.0f - point[0] - point[1];
      break;

    case 3 : // Segment
      vect[0] = point[0];
      vect[1] = 1.0f - point[0];
      break;

  default: printf("\nERREUR : fonction calFbase valeur de t != 1,2,3\n"); return -1;
  }
  return 0;
}

int calDerFbase (int t, float* point, float** tab){

  switch (t) {
    case 1 : 
      tab[0][0] = 1.0f - point[1]; //derivee en fonction de x
      tab[0][1] = - point[0]; //derivee en fonction de y
      tab[1][0] = point[1];
      tab[1][1] = point[0];
      tab[2][0] = - point[1];
      tab[2][1] = 1 - point[0];
      tab[3][0] = -1 + point[1];
      tab[3][1] = -1 + point[0];
      break;

    case 2 :
      tab[0][0] = 1.0f;
      tab[0][1] = 0;
      tab[1][0] = 0;
      tab[1][1] = 1.0f;
      tab[2][0] = -1.0f;
      tab[2][1] = -1.0f;
      break;

    case 3 :
      tab[0][0] = 1.0f;
      tab[0][1] = -1.0f;
      break;

    default: printf("\nERREUR : fonction calDerFbase valeur de t != 1,2,3\n"); return -1;
  }
  return 0;
}

void transFK (int Nk, float** coordElem, float* valFctBase, float* image){
  image[0] = 0.0f; // allocation à 0 sinon resultat errone
  image[1] = 0.0f;

  for (int i=0;i<Nk;i++) {
    image[0] += valFctBase[i] * coordElem[i][0]; // Pour x
    image[1] += valFctBase[i] * coordElem[i][1]; // Pour y
  }
}

void matJacob(int Nk, float** coordElem, int d, float** tab, float** matJac){
  switch (d) {
    case 2 : 
    for (int i=0;i<Nk;i++) {
      matJac[0][0] += coordElem[i][0] * tab[i][0]; 
      matJac[0][1] += coordElem[i][0] * tab[i][1]; 
      matJac[1][0] += coordElem[i][1] * tab[i][0]; 
      matJac[1][1] += coordElem[i][1] * tab[i][1]; 
  }
  break;

  case 1 : 
    for (int i=0;i<Nk;i++) {
      matJac[0][0] += coordElem[i][0] * tab[i][0]; 
      matJac[0][1] += coordElem[i][1] * tab[i][0]; 
  }
  break;
}
}

float invertM2x2(float** mat, float** mat_inv){
  const float delta = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
  if (fabs(delta)>=1e-8f) { // On s'assure que delta != de 0 en prenant en compte l'erreur d'approximation
    mat_inv[0][0] =  1.0f/delta * mat[1][1];
    mat_inv[0][1] = -1.0f/delta * mat[0][1];
    mat_inv[1][0] = -1.0f/delta * mat[1][0];
    mat_inv[1][1] =  1.0f/delta * mat[0][0];
  }
  else printf("\nMatrice non inversible\n");

  return delta;
}

int numAret (int t, int nba, int* couple){
  couple[0] = nba;
  switch (t) {
	  case 1 :
		  couple[1] = nba % 4 + 1;
		  break;
	  case 2 :
		  couple[0] = nba % 3 + 1;
		  break;
	  default: printf("ERREUR : fonction numAret -> t != {1,2}");return -1;
  }
  return 0;

}

void selectPts(int nb, int num[], float* coorEns[], float* coorSel[]){
  for (int i=0;i<nb;i++) {
    coorSel[i] = coorEns[num[i]-1];
  }
}

