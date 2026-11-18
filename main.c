#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int main(int argc, char **argv) {
    const char *filename = (argc > 1) ? argv[1] : "results.csv";
    char path[strlen("results/") + strlen(filename)+1];
    snprintf(path, sizeof(path), "results/%s", filename);

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
    const int log_step = 200;
    const double v_end = 0.35;
    const int MAX_STEPS = 1000000;

    double a_brake = (F_c / m - g);
    printf("Start parameters: m=%.2f kg, H_0=%.2f m, V_0=%.2f m/s, F_c=%.1f N\n", m, H_0, V_0, F_c);

    if (a_brake <= 0.0) {
        printf("Warning: Engine thrust (%.2f N) is too low to overcome weight (%.2f N). Landing is not possible.\n",
               F_c, m * g);
    } else if (V_0 >= 1.0) {
        double H_min = (V_0 * V_0 - 1.0) / (2.0 * a_brake);
        if (H_0 < H_min) {
            printf("Warning: Initial height too low (minimum %.2f required). Landing is not possible.\n", H_min);
        }
    }
    printf("-------------------------------------------------------------------\n");

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Failed to open csv file");
        return 1;
    }
    fprintf(file,"time,height,velocity,engine_state\n");

    double H=H_0;
    double V=V_0;
    double t=0.0;
    int engine_state=0;
    int step=0;

    while (H>0.0 && step<MAX_STEPS) {

        if (a_brake<=0.0) {
            engine_state=1;
        }else {
            double H_brake= (V>v_end) ? (V*V -v_end*v_end)/ (2.0*a_brake): 0.0;

            if (engine_state==0) {
                if (V>v_end && (H-0.5*V*dt)<=H_brake) {
                    engine_state=1;
                }
            }else {
                if (V<=0.05 && H>1.0) {
                    engine_state=0;
                }
            }
        }

        fprintf(file, "%.3f,%.4f,%.4f,%d\n",t,H,V,engine_state);

        if (step%log_step==0) {
            printf("H=%.1fm, V=%.1fm/s, %s\n", H, V, engine_state ? "ON" : "OFF");
        }
        double a=g-(engine_state*F_c)/m;
        double H_next= H- (V*dt +0.5 *a*dt*dt);

        if (H_next<=0.0) {
            double delta=V*V+ 2.0*a*H;
            if (delta<0.0) delta=0.0;
            double denom = V+ sqrt(delta);
            double dt_hit= (denom>0.0) ? (2.0 *H)/ denom: 0.0;

            t+=dt_hit;
            V+=a*dt_hit;
            H=0.0;
            break;
        }

        H=H_next;
        V+=a*dt;
        t+=dt;
        step++;
    }
    fprintf(file, ".%3f,%.4f,%.4f,%d\n",t,H,V,engine_state);
    printf("H=%.1fm, V=%.1fm/s, %s\n", H, V, engine_state ? "ON" : "OFF");
    fclose(file);
    printf("-----------------------------------------------------------------------------\n");
    printf("Flight time: %.2f s | Ending velocity: %.3f m/s\n",t,V);
    if (H<=0.0 && V>=0.0 && V<1.0) {
        printf("Success, Lander landing safely on the Moon\n");
    }
    else {
        printf("Unsuccess, Lander hit on surface the Moon\n");
    }
    printf("Simulation save to: %s\n",path);

    return 0;
}
