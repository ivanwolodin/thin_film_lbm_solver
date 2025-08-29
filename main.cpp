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

int main() {
    greetings();
    simulate_relaxing_droplet();
    return 0;
}