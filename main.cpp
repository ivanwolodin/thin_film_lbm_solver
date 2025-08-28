#include <iostream>

#include "initial_distribution.h"
#include "kernel.h"
#include "output.h"

int main() {
    greetings();
    // set_bubble();
    set_droplet();
    // set_flat();
    compute_feq_2();
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            for (int k = 0; k < Nc; k++){
                f[i][j][k] = feq[i][j][k];
            }

        }
    }

    // compute_theta();
    // compute_all_forces();

    dump_initial_params();

    for (int step = 1; step <= 1000000; step++) {
        std::cout<<"============================"<<std::endl;
        std::cout << "step = " << step << std::endl;

        take_step();
        output_fields(step);
        output_radius_and_h_and_theta(step);
        output_thickness_horizontal_slice(step, center_y);
    }

    return 0;
}