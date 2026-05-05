#include<math.h>
#include<stdio.h>

/*
--------------------------------------------------------------------------------
    Evaluation de la solution exacte
--------------------------------------------------------------------------------
*/
extern int nucas;

float solex(float *coor) {
  const float PI = M_PI;
  float val = 0.0f;

  switch (nucas) {
    case 1 :
	    val=16.0f*coor[0]*coor[1]*(coor[0]-1)*(1.0f-coor[1]);
	    break;
    case 2 :
	    val=sinf(PI*coor[0])*sinf(PI*coor[1]);
	    break;
    case 3 :
	    val=cosf(PI*coor[0])*cosf(PI*coor[1]);
	    break;
    default :
	    printf("*** SOLEX : exemple non prevu.\n");
	    break;
  }
  return(val);
}
