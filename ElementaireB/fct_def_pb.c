#include "elementairesb.h"

float A11(float x){
  return 1.0f;
}

float A22(float x){
  return 1.0f;
}

float A12(float x){
  return 0;
}

float A00(float x){
  return 1.0f;
}

float BN(float x){
  return 0;
}

float FOMEGA(float x){
  return 1.0f;
}

float FN(float x){
  return 1.0f;
}

float UD(float* x){
  return 100.0f*x[0] + x[1];
}

