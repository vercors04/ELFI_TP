#include "../5_Resol_Post-Trait/dsmoapr.h"

void CalSol (int NbLign, float **coord, float *UEX){

    float point[2];

    for (int i = 0; i < NbLign; i++) {
        point[0] = coord[i][0]; 
        point[1] = coord[i][1];
        
        UEX[i] = solex(point);

    }
}