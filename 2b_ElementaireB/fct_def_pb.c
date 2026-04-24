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
  return 1.0f;
}

float BN(float* x){
  return 1.0f;
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
  return 1.0f;
}

float UD(float* x){
  return 100.0f*x[0] + x[1];
}

