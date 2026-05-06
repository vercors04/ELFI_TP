#include <stdio.h>

int main() {
    int impfch_Aff = 111;
    int nudom = impfch_Aff/100;
    int nucas = nudom%10;
    int typel = impfch_Aff%10;

    FILE* plot = popen("gnuplot -persist", "w");

    fprintf(plot, "set title 'domaine %d, cas %d, typel %d'\n", nudom, nucas, typel);
    fprintf(plot, "set xlabel 'h'\n");
    fprintf(plot, "set ylabel 'Erreur relative'\n");
    fprintf(plot, "set xrange [*:*] reverse\n");


    fprintf(plot, "plot 'fort.%d' using 3:1 with line title 'erreur quadratique relative', 'fort.%d' using 3:2 with line title 'erreur maximum relative'\n", impfch_Aff,impfch_Aff);

    pclose(plot);
    return 0;
}