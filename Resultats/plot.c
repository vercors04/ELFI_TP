#include <stdio.h>

int main() {

    int impfch_Aff;
    printf("Entrez le numéro du fichier 'fort.' que l'on veut plot : \n");
    scanf("%d", &impfch_Aff);

    if (impfch_Aff != 111 && impfch_Aff != 112 && impfch_Aff != 121 && impfch_Aff != 122 && impfch_Aff != 131 && impfch_Aff != 132 && 
        impfch_Aff != 211 && impfch_Aff != 212 && impfch_Aff != 221 && impfch_Aff != 222 && impfch_Aff != 231 && impfch_Aff != 232) {
            printf("\nNuméro du fichier 'fort.' non valable\n");
            return 1;
        } 

    int nudom = impfch_Aff/100;
    int nucas = (impfch_Aff / 10) % 10;
    int typel = impfch_Aff%10;

    char* nom_element;

    if (typel == 1) {
        nom_element = "Quadrangle";
    }
    else if (typel == 2) {
        nom_element = "Triangle";
    }
    else {
        nom_element = "Inconnu";
    }
    /*popen lance gnuplot -persist (persist pour pas que le graph se ferme quand on ferme le fichier)
    et retourne un FILE* */
    FILE* plot = popen("gnuplot -persist", "w");

    fprintf(plot, "set title 'Erreur obtenue en échelle logarithmique pour le domaine %d, le cas %d et l''élément %s'\n", nudom, nucas, nom_element);
    fprintf(plot, "set xlabel 'Log de h'\n");
    fprintf(plot, "set ylabel 'Log de l''Erreur relative'\n");
    fprintf(plot, "set xrange [*:*] reverse\n");
    fprintf(plot, "set logscale x\n");
    fprintf(plot, "set logscale y\n");

    fprintf(plot, "plot '../Resultats/fort.%d' using 3:1 with linespoints title 'erreur quadratique relative',\
         '../Resultats/fort.%d' using 3:2 with linespoints title 'erreur maximum relative'\n", impfch_Aff,impfch_Aff);

    pclose(plot);
    return 0;
}
