#include <stdlib.h>

float *allocvec_f(int dim) {
    float *v = malloc(dim * sizeof(float));
    return v;
}

int *allocvec_i(int dim) {
    int *v = malloc(dim * sizeof(int));
    return v;
}

float *callocvec_f(int dim) {
    float *v = calloc(dim, sizeof(float));
    return v;
}

int *callocvec_i(int dim) {
    int *v = calloc(dim , sizeof(int));
    return v;
}


