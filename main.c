#include "header.h"

int main() {
    int a, b, c, d, n1, n2,t;

    //ouverture du fichier
    FILE *f = fopen("fichier_imput_test.txt", "r");
	fscanf(f, "%d %d %d %d %d %d", &a, &b, &c, &d, &n1, &n2,&t); //lecture du fichier et on met dans les var
    printf("test : %d %d",a,n1);
    file_create(a,b,c,d,n1,n2,t);

	
}