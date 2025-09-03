#include <iostream>

#include "initial_distribution.h"
#include "kernel.h"
#include "output.h"


inline void simulate_relaxing_droplet() {

    tau = 0.923;
    viscosity = (tau - 0.5) * sound_speed_squared;
    radius_initial = 80.0;
    delta = 1.0;
    surface_tension = 0.00005;
    gravity = 1.0 * pow(10, -5);
    theta_initial = 30.0;
    theta_initial_d = theta_initial * (M_PI / 180);
    theta_current = theta_initial_d;
    minimal_thickness = 0.05;

    steps_number = 200000;

    set_droplet();
    compute_feq_2();
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            for (int k = 0; k < Nc; k++){
                f[i][j][k] = feq[i][j][k];
            }

        }
    }

    dump_initial_params();

    for (int step = 1; step <= steps_number; step++) {
        std::cout<<"============================"<<std::endl;
        std::cout << "step = " << step << std::endl;

        take_step();
        output_fields(step);
        output_radius_and_h_and_theta(step);
        output_thickness_horizontal_slice(step, center_y);
    }
}

inline void run_flat() {
    tau = 0.923;
    viscosity = (tau - 0.5) * sound_speed_squared;

    delta = 1.0;
    surface_tension = 0.005;
    gravity = 20.0 * pow(10, -7);
    theta_initial = 30.0;
    theta_initial_d = theta_initial * (M_PI / 180);
    theta_current = theta_initial_d;
    minimal_thickness = 0.07;

    steps_number = 200000;

    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            film_thickness[i][j] = 1.0;
        }
    }

    compute_feq_2();
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            for (int k = 0; k < Nc; k++){
                f[i][j][k] = feq[i][j][k];
            }

        }
    }

    dump_initial_params();

    for (int step = 1; step <= steps_number; step++) {
        std::cout<<"============================"<<std::endl;
        std::cout << "step = " << step << std::endl;

        take_step();
        output_fields(step);
    }
}

inline void run_disturbed_interface() {
    tau = 0.923;
    viscosity = (tau - 0.5) * sound_speed_squared;

    delta = 1.0;
    surface_tension = 0.005;
    gravity = 1.0 * pow(10, -5);
    theta_initial = 30.0;
    theta_initial_d = theta_initial * (M_PI / 180);
    theta_current = theta_initial_d;
    minimal_thickness = 0.07;

    steps_number = 2000000;

    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            film_thickness[i][j] = 1.0;
        }
    }
    for (int j = 75; j <= 125; j++) {
        for (int i = 50; i < 100; i++) {
            film_thickness[i][j] = film_thickness[i][j] - 0.1;
        }
        for (int i = 100; i <= 150; i++) {
            film_thickness[i][j] = film_thickness[i][j] + 0.1;
        }
    }

    output_fields(0);
    compute_feq_2();
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            for (int k = 0; k < Nc; k++){
                f[i][j][k] = feq[i][j][k];
            }

        }
    }

    dump_initial_params();

    for (int step = 1; step <= steps_number; step++) {
        std::cout<<"============================"<<std::endl;
        std::cout << "step = " << step << std::endl;

        take_step();
        output_fields(step);
        output_max_height(step);
        output_total_mass(step);
    }
}

inline void run_wave_pattern_interface() {
    tau = 0.923;
    viscosity = (tau - 0.5) * sound_speed_squared;

    delta = 1.0;
    surface_tension = 0.005;
    gravity = 1.0 * pow(10, -5);
    theta_initial = 30.0;
    theta_initial_d = theta_initial * (M_PI / 180);
    theta_current = theta_initial_d;
    minimal_thickness = 0.07;

    steps_number = 2000000;

    double H0 = 1.0;
    double A  = 0.2;
    int Nwaves = 3;  // сколько волн уместить по всей высоте Ny

    for (int j = 0; j < Ny; ++j) {
        double wave = H0 + A * std::sin(2.0 * M_PI * Nwaves * j / Ny);

        for (int i = 0; i < Nx; ++i) {
            film_thickness[i][j] = wave;
        }
    }

    output_fields(0);
    compute_feq_2();
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            for (int k = 0; k < Nc; k++){
                f[i][j][k] = feq[i][j][k];
            }

        }
    }

    dump_initial_params();

    for (int step = 1; step <= steps_number; step++) {
        std::cout<<"============================"<<std::endl;
        std::cout << "step = " << step << std::endl;

        take_step();
        output_fields(step);
        output_max_height(step);
        output_total_mass(step);
    }
}

int main() {
    greetings();
    run_wave_pattern_interface();
    //simulate_relaxing_droplet();
    // run_flat();
    // run_disturbed_interface();
    return 0;
}