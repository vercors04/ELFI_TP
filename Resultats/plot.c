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

    /*popen lance gnuplot -persist (persist pour pas que le graph se ferme quand on ferme le fichier)
    et retourne un FILE* */
    FILE* plot = popen("gnuplot -persist", "w");

    fprintf(plot, "set title 'Erreur obtenue pour le domaine %d, le cas %d et le type d''élément %d'\n", nudom, nucas, typel);
    fprintf(plot, "set xlabel 'h'\n");
    fprintf(plot, "set ylabel 'Erreur relative'\n");
    fprintf(plot, "set xrange [*:*] reverse\n");

    fprintf(plot, "plot '../Resultats/fort.%d' using 3:1 with linespoints title 'erreur quadratique relative',\
         '../Resultats/fort.%d' using 3:2 with linespoints title 'erreur maximum relative'\n", impfch_Aff,impfch_Aff);

    pclose(plot);
    return 0;
}
