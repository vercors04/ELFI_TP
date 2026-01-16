#include "header.h"

int main() {
  int a, b, c, d, n1, n2,t;

    //ouverture du fichier

  FILE *f = fopen("fichier_imput_test.txt", "r");
  fscanf(f, "%d %d %d %d %d %d %d", &a, &b, &c, &d, &n1, &n2,&t); //lecture du fichier et on met dans les var
  
  printf("Domaine : [%d,%d]x[%d,%d]\n",a,b,c,d);
  printf("Nombres de points n1 = %d\n",n1);
  printf("Nombres de points n2 = %d\n",n2);
  if (1==t) printf("Type : Quadrangles\n");
  else if (2==t) printf("Type : Triangles\n");
  file_create(a,b,c,d,n1,n2,t);
//test3
	
}
