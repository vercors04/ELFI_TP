#include "header.h"

int main() {
  int  n1, n2,t;
  double a, b, c, d;

    //ouverture du fichier

  FILE *f = fopen("fichier_imput_test.txt", "r");
  fscanf(f, "%lf %lf %lf %lf %d %d %d", &a, &b, &c, &d, &n1, &n2,&t); //lecture du fichier et on met dans les var
  
  printf("Domaine : [%lf,%lf]x[%lf,%lf]\n\n",a,b,c,d);
  printf("Nombres de points n1 = %d\n\n",n1);
  printf("Nombres de points n2 = %d\n\n",n2);
  if (t==1) printf("Type : Quadrangles\n\n");
  else if (t==2) printf("Type : Triangles\n\n");
  file_create(a,b,c,d,n1,n2,t);
//test3
	
}
