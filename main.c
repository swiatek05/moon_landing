#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    const char *filename = (argc>1) ? argv[1] : "results.csv";
    double m = 2000.0;
    double H_0 = 500.0;
    double V_0 = 10.0;
    double F_c = 4500.0;
    const double g = 1.6;

    if (argc == 6) {
        m = atof(argv[2]);
        H_0 = atof(argv[3]);
        V_0 = atof(argv[4]);
        F_c = atof(argv[5]);
    } else if (argc != 1 && argc != 2) {
        fprintf(stderr, "Bad usage: %s m H_0 V_0 F_c\n", argv[0]);
        return 1;
    }

    if (m <= 0.0 || H_0 <= 0.0 || F_c <= 0.0) {
        fprintf(stderr, "Usage: %s m H_0 V_0 F_c\n", argv[0]);
        return 1;
    }

    const double dt = 0.001;
    const int log_step = 20;
    const double v_cel = 0.35;
    const int MAX_STEPS = 1000000;

    double a_brake = (F_c / m - g);
    printf("Starts parameteres: m=%.2f kg, H_0=%.2f m/s, F_c=%.1f N\n", m, H_0, F_c);

    if (a_brake <=0.0) {
        printf("Warning: Engine thrust is too low to overcome weight (%.1f N). Landing is not possible.\n",F_c,m*g);
    }else if (V_0>=1.0) {
        double H_min=(V_0*V_0 - 1.0)/(2.0 * a_brake);
        if (H_0<H_min) {
            printf("Warning: Initial height too low (minimum %.2f required). Landing is not possible.\n",H_min);
        }
    }
    printf("-------------------------------------------------------------------\n");




}
