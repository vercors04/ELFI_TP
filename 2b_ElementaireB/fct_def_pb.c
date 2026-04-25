#include <stdio.h>
#include <math.h>

#define PI_F 3.14159265f
extern int nucas;

float A11(float* x){
  return 1.0f;
}

float A22(float* x){
  return 1.0f;
}

float A12(float* x){
  return 0.0f;
}

float A00(float* x){
  float val = 0.0f;
  switch (nucas) {
    case 1: 
      val = 0.0f;
      break;

    case 2: 
      val = 0.0f;
      break;  

    case 3: 
      val = 1.0f;
      break;
  }
} 

float BN(float* x){
  return 0.0f;
}

float FOMEGA(float* x){
  float val = 0.0f;
  switch (nucas) {
    case 1: 
      val = 32.0f * (x[0]*x[0]-x[0]+x[1]*x[1]-x[1]);
      break;
    case 2:
      val = 2.0f * PI_F * PI_F * sinf(PI_F*x[0]) * sinf(PI_F*x[1]);
      break;
    case 3:
      val = (2.0f * PI_F * PI_F + 1) * cosf(PI_F * x[0]) * cosf(PI_F * x[1]);
      break;
    default:
      printf("FOMEGA : exmple non prevu.\n");
      break;
  }
  return val;
}

float FN(float* x){
  //return 1.0f;
  // Calcul du vecteur normal unitaire
  float normale[2];
  if (fabsf(x[0])<1.0e-07f){
    normale[0] =-1.0f;
    normale[1] = 0.0f;
  }
  else if (fabsf(x[1])<1.0e-07f) {
    normale[0] = 0.0f;
    normale[1] =-1.0f;
  }
  // Domaine 1 
  else if (1.0f-1.0e-7f<x[0] && x[0]<1.0f+1.0e-7f) {
    normale[0] = 1.0f;
    normale[1] = 0.0f;
  }
  /*
  // Domaine 2 
  else if (1.0f/3.0f-1.0e-7f<x[0] && x[0]<1.0f/3.0f+1.0e-7f) {
    normale[0] = 1.0f;
    normale[1] = 0.0f;
  }
  */
  else {
    // if (1.0f-1.0e-7f<x[1] && x[1]<1.0f+1.0e-7f) Domaine 1
    // if (1.0f/3.0f-1.0e-7f<x[1] && x[1]<1.0f/3.0f+1.0e-7f) Domaine 2
    normale[0] = 0.0f;
    normale[1] = 1.0f;
  }

  float val = 0.0f;
  switch (nucas) {
    case 1: 
      val = normale[0] * 16.0f*x[1] * (-2.0f*x[0]*x[1] + 2.0f*x[0] + x[1] - 1.0f)\
          + normale[1] * 16.0f*x[0] * (-2.0f*x[0]*x[1] + 2.0f*x[1] + x[0] - 1.0f);
      break;
    case 2:
      val = normale[0] * PI_F * cosf(PI_F*x[0]) * sinf(PI_F*x[1])\
          + normale[1] * PI_F * cosf(PI_F*x[1]) * sinf(PI_F*x[0]);
      break;
    case 3:
      val = -normale[0] * PI_F * sinf(PI_F*x[0]) * cosf(PI_F*x[1])\
          -  normale[1] * PI_F * sinf(PI_F*x[1]) * cosf(PI_F*x[0]);
      break;
    default:
      printf("FOMEGA : exmple non prevu.\n");
      break;
  }
  return val;
}

float UD(float* x){
  float val = 0.0f;

  switch (nucas) {
    case 1 :
	    val = 16.0f * x[0]*x[1] * (x[0]-1)*(1.0f-x[1]);
	    break;
    case 2 :
	    val = sinf(PI_F*x[0]) * sinf(PI_F*x[1]);
	    break;
    case 3 :
	    val = cosf(PI_F*x[0]) * cosf(PI_F*x[1]);
	    break;
    default :
	    printf("*** SOLEX : exemple non prevu.\n");
	    break;
  }
  return(val);
  //return 100.0f*x[0] + x[1];
}

