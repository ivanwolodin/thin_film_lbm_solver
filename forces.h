#ifndef THIN_FILM_LBM_FORCES_H
#define THIN_FILM_LBM_FORCES_H

#include "constants.h"
#include "controlling_params.h"
#include "diff_operators.h"
#include "theta_calculation.h"

inline void compute_hydrostatic_pressure(){
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            hydrostatic_pressure[i][j] = gravity * film_thickness[i][j] * film_thickness[i][j];
        }
    }
}

inline void compute_total_force(){
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            f_total[i][j][0] = f_film[i][j][0] + f_fric[i][j][0] + gravity * 0.0;
            f_total[i][j][1] = f_film[i][j][1] + f_fric[i][j][1] - gravity * 1.0;
        }
    }
}

inline void compute_film_fric(){
    double alpha_h;
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            if (film_thickness[i][j] == 0) {
                continue;
            }

            alpha_h = (6.0 * film_thickness[i][j]) /
                      (2.0 * film_thickness[i][j] * film_thickness[i][j] + 6.0 * delta * film_thickness[i][j] + 3.0 * delta * delta);

            f_fric[i][j][0] = -viscosity * alpha_h * u[i][j][0];
            f_fric[i][j][1] = -viscosity * alpha_h * u[i][j][1];

        }
    }
}

inline void compute_pii(){
    theta_current = theta_initial_d;
    // compute_theta();
    double pii_theta = (1.0 - cos(theta_current)) * (((n - 1.0) * (m - 1.0)) / (n - m));
    // cout << "pii_theta = " << pii_theta << endl;
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            film_thickness_previous[i][j] = minimal_thickness;
            if (film_thickness[i][j] == 0.0) {
                continue;
            }

            pii[i][j] = (pii_theta / film_thickness_previous[i][j]) *
                    (pow(
                         (film_thickness_previous[i][j] / (film_thickness[i][j])),
                         n) -
                     pow(
                         (film_thickness_previous[i][j] / (film_thickness[i][j]) ),
                         m));
        }
    }
}

inline void compute_pii_2() {
    double coeff = (1.0 - cos(theta_current)) * ((n - 1.0) * (m - 1.0)) / ((n - m) * minimal_thickness);
    double hcrit = 0.007;
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            double h = film_thickness[i][j];
            if (h <= 0.0) {
                pii[i][j] = 0.0;
                continue;
            }

            double arg = minimal_thickness / (h + hcrit);
            pii[i][j] = coeff * (pow(arg, 9) - pow(arg, 3));

        }
    }
}

inline void compute_pressure_film_2() {
    compute_pii_2();
    compute_laplacian(laplacian_film_thickness, film_thickness);

    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            // film_pressure = -σ * (pii + laplacian(h))
            film_pressure[i][j] = -surface_tension * (pii[i][j] + laplacian_film_thickness[i][j]);
        }
    }
}

inline void compute_pressure_film(){
    compute_pii();
    // compute_laplacian(laplacian_film_thickness, film_thickness);
    compute_laplacian_classic(laplacian_film_thickness, film_thickness);

    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            film_pressure[i][j] = -surface_tension * (laplacian_film_thickness[i][j] + pii[i][j]);
        }
    }
}

inline void compute_film_force(){
    compute_pressure_film();
    compute_grad(d_film_pressure, film_pressure);
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            f_film[i][j][0] = -(1.0 / rho_0) * film_thickness[i][j] * d_film_pressure[i][j][0];
            f_film[i][j][1] = -(1.0 / rho_0) * film_thickness[i][j] * d_film_pressure[i][j][1];
        }
    }
}

inline void compute_film_force_2(){
    compute_pressure_film_2();
    compute_grad(d_film_pressure, film_pressure);
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            f_film[i][j][0] = -(1.0 / rho_0) * film_thickness[i][j] * d_film_pressure[i][j][0];
            f_film[i][j][1] = -(1.0 / rho_0) * film_thickness[i][j] * d_film_pressure[i][j][1];
        }
    }
}

inline void compute_all_forces(){
    compute_film_force();
    compute_film_fric();
    compute_total_force();
}

#endif //THIN_FILM_LBM_FORCES_H