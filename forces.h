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
            f_total[i][j][0] = f_film[i][j][0] + f_fric[i][j][0] + Fx;
            f_total[i][j][1] = f_film[i][j][1] + f_fric[i][j][1] + Fy;
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
    // theta_current = theta_initial_d;
    // compute_theta();
    double pii_theta = (1.0 - cos(theta_d)) * (((n - 1.0) * (m - 1.0)) / (n - m));
    // cout << "pii_theta = " << pii_theta << endl;
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            film_thickness_previous[i][j] = minimal_thickness;
            if (film_thickness[i][j] == 0.0) {
                continue;
            }

            // pii[i][j] = (1.0 / film_thickness[i][j] * film_thickness[i][j] * film_thickness[i][j]);

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
    double coeff = (1.0 - cos(theta_d)) * ((n - 1.0) * (m - 1.0)) / ((n - m) * minimal_thickness);
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
    // compute_grad(d_film_pressure, film_pressure);
    compute_grad_classic(d_film_pressure, film_pressure);
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

inline void compute_avg_velocity(){

    int j_center = Ny / 2;
    double sum_ux;
    double h;
    double dpdx;
    double z;
    double ux;
    double avg_ux;

    for (int k = 0; k <= Nz; k++) {
        sum_ux = 0.0;

        for (int i = 0; i <= Nx - 1; i++) {
            h = film_thickness[i][j_center];
            dpdx = d_film_pressure[i][j_center][0];

            if (h <= 0.0) continue;

            z = (double)k / Nz * h;
            ux = (1.0 / (2.0 * viscosity)) * dpdx * (z * z - h * z);

            sum_ux += ux;
        }

        avg_ux = sum_ux / Nx;
        ux_profile[k] = avg_ux;
    }


    int i_center = Nx / 2;
    double sum_uy;
    double dpdy;
    double uy;
    double avg_uy;

    for (int k = 0; k <= Nz; k++) {
        sum_uy = 0.0;

        for (int j = 0; j <= Ny - 1; j++) {
            h = film_thickness[i_center][j];
            dpdy = d_film_pressure[i_center][j][1]; // ∂p/∂y

            if (h <= 0.0) continue;

            z = (double)k / Nz * h;
            uy = (1.0 / (2.0 * viscosity)) * dpdy * (z * z - h * z);

            sum_uy += uy;
        }

        avg_uy = sum_uy / Ny;
        uy_profile[k] = avg_uy;
    }
}

inline void compute_all_forces(){
    compute_film_force();
    compute_film_fric();
    compute_total_force();
}

#endif //THIN_FILM_LBM_FORCES_H