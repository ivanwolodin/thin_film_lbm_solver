#ifndef THIN_FILM_LBM_KERNEL_H
#define THIN_FILM_LBM_KERNEL_H

#include "controlling_params.h"
#include "forces.h"
#include "output.h"
#include "streaming_and_boundary.h"
#include "theta_calculation.h"

inline void save_previous_film(){
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            // film_thickness_previous[i][j] = film_thickness[i][j];
            film_thickness_previous[i][j] = minimal_thickness;
        }
    }
}

inline void compute_macroscopic_values(){
    double temporary_var_for_film = 0.0;
    double temporary_var_for_u = 0.0;
    double temporary_var_for_v = 0.0;

    // film
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            temporary_var_for_film = 0.0;

            for (int k = 0; k < Nc; k++){
                temporary_var_for_film += f[i][j][k];
            }
            if (temporary_var_for_film <= 0.0) {
                continue;
            }
            film_thickness[i][j] = temporary_var_for_film;
        }
    }

    // velocity
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            temporary_var_for_u = 0.0;
            temporary_var_for_v = 0.0;

            for (int k = 0; k < Nc; k++){
                temporary_var_for_u += (f[i][j][k] * cx[k]);
                temporary_var_for_v += (f[i][j][k] * cy[k]);
            }

            if (film_thickness[i][j] == 0) {
                continue;
            }

            u[i][j][0] = temporary_var_for_u / film_thickness[i][j];
            u[i][j][1] = temporary_var_for_v / film_thickness[i][j];

        }
    }
}

inline void compute_feq(){
    double velocity_squared = 0.0;
    double local_velocity = 0.0;

    compute_hydrostatic_pressure();

    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            velocity_squared = u[i][j][0] * u[i][j][0] + u[i][j][1] * u[i][j][1];

            feq[i][j][0] = film_thickness[i][j] - (5.0 * hydrostatic_pressure[i][j]) / (sound_speed_squared * 6.0) -
                           2.0 * (film_thickness[i][j] * velocity_squared) / (sound_speed_squared * 3.0);

            for (int k = 1; k <= 4; k++){
                local_velocity = cx[k] * u[i][j][0] + cy[k] * u[i][j][1];
                feq[i][j][k] = (hydrostatic_pressure[i][j]) / (6.0 * sound_speed_squared) +
                               (film_thickness[i][j] * local_velocity) / (3.0 * sound_speed_squared) +
                               (film_thickness[i][j] * local_velocity * local_velocity) / (2.0 * sound_speed_squared * sound_speed_squared) - (film_thickness[i][j] * velocity_squared) / (6.0 * sound_speed_squared);
            }

            for (int k = 5; k <= 8; k++){
                local_velocity = cx[k] * u[i][j][0] + cy[k] * u[i][j][1];
                feq[i][j][k] = (hydrostatic_pressure[i][j]) / (24.0 * sound_speed_squared) +
                               (film_thickness[i][j] * local_velocity) / (12.0 * sound_speed_squared) +
                               (film_thickness[i][j] * local_velocity * local_velocity) / (8.0 * sound_speed_squared * sound_speed_squared) - (film_thickness[i][j] * velocity_squared) / (24.0 * sound_speed_squared);
            }
        }
    }
}


inline void compute_feq_2(){
    double velocity_squared = 0.0;
    double local_velocity = 0.0;
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            velocity_squared = u[i][j][0] * u[i][j][0] + u[i][j][1] * u[i][j][1];
            // feq[i][j][0] = film_thickness[i][j] - w[0] * film_thickness[i][j] * ((15.0 / 2.0) * gravity * film_thickness[i][j] - 1.5 * velocity_squared);
            feq[i][j][0] = film_thickness[i][j] * (1.0 - (5.0 / 6.0) * gravity * film_thickness[i][j]
                    - (2.0 / 3.0) * velocity_squared);
            for (int k = 1; k <= 8; k++){
                local_velocity = cx[k] * u[i][j][0] + cy[k] * u[i][j][1];
                feq[i][j][k] = w[k] * film_thickness[i][j] * (1.5 * gravity * film_thickness[i][j] + 3.0 * local_velocity + 4.5 * local_velocity * local_velocity - 1.5 * velocity_squared);
            }
        }
    }
}


inline void collision_step(){
    double local_force = 0.0;

    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            for (int k = 0; k < Nc; k++){
                local_force = cx[k] * f_total[i][j][0] + cy[k] * f_total[i][j][1];

                f[i][j][k] = (1.0 - dt / tau) * f[i][j][k] + (dt / tau) * feq[i][j][k] +
                            w[k] * (dt / sound_speed_squared) * local_force;

            }
        }
    }
}

inline void collision_step_2() {
    double omega = 1.0 - 1.0 / tau;

    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            double Fx = f_total[i][j][0];
            double Fy = f_total[i][j][1];

            // Zeroth, no forcing
            f[i][j][0] = omega * f[i][j][0] + (1.0 / tau) * feq[i][j][0];

            // Straight directions
            f[i][j][1] = omega * f[i][j][1] + (1.0 / tau) * feq[i][j][1] + Fx / 3.0;
            f[i][j][2] = omega * f[i][j][2] + (1.0 / tau) * feq[i][j][2] + Fy / 3.0;
            f[i][j][3] = omega * f[i][j][3] + (1.0 / tau) * feq[i][j][3] - Fx / 3.0;
            f[i][j][4] = omega * f[i][j][4] + (1.0 / tau) * feq[i][j][4] - Fy / 3.0;

            // Diagonal directions
            f[i][j][5] = omega * f[i][j][5] + (1.0 / tau) * feq[i][j][5] + (Fx + Fy) / 24.0;
            f[i][j][6] = omega * f[i][j][6] + (1.0 / tau) * feq[i][j][6] + (Fy - Fx) / 24.0;
            f[i][j][7] = omega * f[i][j][7] + (1.0 / tau) * feq[i][j][7] - (Fx + Fy) / 24.0;
            f[i][j][8] = omega * f[i][j][8] + (1.0 / tau) * feq[i][j][8] + (Fx - Fy) / 24.0;
        }
    }
}

inline void healthy_check() {
    compute_thickness_integral();
    compute_max_height();
    compute_min_height();
    cout<< "dh = " << thickness_max - thickness_min << endl;
    compute_u_total();
    compute_v_total();

    compute_energy();
}

inline void take_step() {
    compute_feq_2();
    collision_step();
    streaming_step();
    boundary_conditions();
    compute_macroscopic_values();
    compute_all_forces();
    healthy_check();

    compute_avg_velocity();
}

#endif //THIN_FILM_LBM_KERNEL_H