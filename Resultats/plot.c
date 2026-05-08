#include <stdio.h>

int main() {

    int impfch_Aff;

    printf("Entrez le numéro du fichier 'fort.' que l'on veut plot : ");
    scanf("%d", &impfch_Aff);

    if (impfch_Aff != 111 && impfch_Aff != 112 &&
        impfch_Aff != 121 && impfch_Aff != 122 &&
        impfch_Aff != 131 && impfch_Aff != 132 &&
        impfch_Aff != 211 && impfch_Aff != 212 &&
        impfch_Aff != 221 && impfch_Aff != 222 &&
        impfch_Aff != 231 && impfch_Aff != 232) {

        printf("\nNuméro du fichier 'fort.' non valable\n");
        return 1;
    }

    int nudom = impfch_Aff / 100;
    int nucas = (impfch_Aff / 10) % 10;
    int typel = impfch_Aff % 10;

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

    FILE* plot = popen("gnuplot -persist", "w");

    if (plot == NULL) {
        printf("Erreur ouverture gnuplot\n");
        return 1;
    }

    /* ---------- STYLE GENERAL ---------- */

    fprintf(plot, "set terminal qt size 1200,700 enhanced font 'Arial,12'\n");

    fprintf(plot,
        "set title "
        "'Erreur relative en fonction du pas h : "
        "Domaine %d  -  Cas %d  -  %s' "
        "font ',16'\n",
        nudom, nucas, nom_element);

    fprintf(plot, "set xlabel 'Pas h' font ',14'\n");
    fprintf(plot, "set ylabel 'Erreur relative' font ',14'\n");

    fprintf(plot, "set logscale x\n");
    fprintf(plot, "set logscale y\n");

    fprintf(plot, "set xrange [*:*] reverse\n");

    /* ---------- GRILLE ---------- */

    fprintf(plot, "set grid xtics ytics lw 1 lc rgb '#bbbbbb'\n");
    fprintf(plot, "set border lw 1.5\n");

    /* ---------- LEGENDES ---------- */

    fprintf(plot, "set key top left box opaque\n");

    /* ---------- FORMAT DES AXES ---------- */

    fprintf(plot, "set format x '10^{%%L}'\n");
    fprintf(plot, "set format y '10^{%%L}'\n");

    fprintf(plot, "set tics font ',11'\n");

    /* ---------- COURBES ---------- */

    fprintf(plot,
        "plot "
        "'../Resultats/fort.%d' using 3:1 "
        "with linespoints "
        "lw 2.5 pt 7 ps 1.4 "
        "lc rgb '#1f77b4' "
        "title 'Erreur quadratique relative', "

        "'../Resultats/fort.%d' using 3:2 "
        "with linespoints "
        "lw 2.5 pt 5 ps 1.4 "
        "lc rgb '#d62728' "
        "title 'Erreur maximum relative'\n",

        impfch_Aff,
        impfch_Aff
    );

    pclose(plot);

    return 0;
}
