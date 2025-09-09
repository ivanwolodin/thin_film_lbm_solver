#include <iostream>
#include <random>
#include <iomanip>

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

    steps_number = 5000000;

    set_droplet();
    Fx = 0;
    Fy = 0;
    compute_feq_2();
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            for (int k = 0; k < Nc; k++){
                f[i][j][k] = feq[i][j][k];
            }

        }
    }
    output_fields(0);
    dump_initial_params();

    for (int step = 1; step <= steps_number; step++) {
        std::cout<<"============================"<<std::endl;
        std::cout << "step = " << step << std::endl;

        take_step();
        output_fields(step);
        // output_radius_and_h_and_theta(step);
        // output_thickness_horizontal_slice(step, center_y);
        output_max_height(step);
        output_min_height(step);
        output_total_mass(step);
        output_dh(step);
        output_energy(step);
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
    theta_initial = 20.0;
    theta_initial_d = theta_initial * (M_PI / 180);
    theta_current = theta_initial_d;
    minimal_thickness = 0.07;

    steps_number = 10000000;

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
        output_min_height(step);
        output_total_mass(step);
        output_dh(step);
        output_energy(step);
    }
}


inline void run_disturbed_interface_v2() {
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
    for (int j = 25; j <= 75; j++) {
        for (int i = 25; i < 50; i++) {
            film_thickness[i][j] = film_thickness[i][j] - 0.01;
        }
        for (int i = 50; i <= 75; i++) {
            film_thickness[i][j] = film_thickness[i][j] + 0.01;
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
        output_min_height(step);
        output_total_mass(step);
        output_dh(step);
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
    double inclination_angle = 45.0;

    Fx = 1*gravity * sin(inclination_angle * (M_PI / 180));
    Fy = -1*gravity * cos(inclination_angle * (M_PI / 180));
    steps_number = 10000000;

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
        output_min_height(step);
        output_total_mass(step);
        output_dh(step);
        output_energy(step);
    }
}


void simulate_random_interface() {
    tau = 0.923;
    viscosity = (tau - 0.5) * sound_speed_squared;

    delta = 1.0;
    surface_tension = 0.005;
    gravity = 1.0 * pow(10, -5);
    theta_initial = 20.0;
    theta_initial_d = theta_initial * (M_PI / 180);
    theta_current = theta_initial_d;
    minimal_thickness = 0.07;

    steps_number = 10000000;


    double h0 = 1.0;
    double eps = 0.01;
    std::random_device rd;
    std::mt19937 gen(rd());  // генератор случайных чисел
    std::normal_distribution<> dist(0.0, 1.0); // стандартное N(0,1)

    size_t nx = film_thickness.size();
    size_t ny = film_thickness[0].size();

    for (size_t i = 0; i < nx; i++) {
        for (size_t j = 0; j < ny; j++) {
            double eta = dist(gen);  // случайный шум
            film_thickness[i][j] = h0 * (1.0 + eps * eta);
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


void simulate_falling_film() {
    tau = 0.923;
    viscosity = (tau - 0.5) * sound_speed_squared;

    delta = 1.0;
    surface_tension = 0.005;
    gravity = 20.0 * pow(10, -7);
    theta_initial = 30.0;
    theta_initial_d = theta_initial * (M_PI / 180);
    theta_current = theta_initial_d;
    minimal_thickness = 0.07;

    steps_number = 2000000;
    double inclination_angle = 90;
    Fx = 1*gravity * sin(inclination_angle * (M_PI / 180));
    Fy = -1*gravity * cos(inclination_angle * (M_PI / 180));

    double h0 = 1.0;

    for (size_t i = 0; i <= Nx - 1; i++) {
        for (size_t j = 0; j <= Ny - 1; j++) {
            film_thickness[i][j] = h0;
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
        output_min_height(step);
        output_total_mass(step);
        output_dh(step);
        output_energy(step);
    }
}


inline void simulate_bubble() {

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

    steps_number = 5000000;

    double radius=radius_initial;
    double x0 = Nx / 2.0;
    double y0 = Ny / 2.0;

    bubble_volume = ((M_PI * radius * radius * radius) / 3.0) *  (1.0 - cos(theta_initial_d)) * (1.0 - cos(theta_initial_d)) * (2.0 + cos(theta_initial_d));

    Fx = 0;
    Fy = 0;

    // for (int i = 0; i < Nx; ++i) {
    //     for (int j = 0; j < Ny; ++j) {
    //         double dxx = i - x0;
    //         double dyy = j - y0;
    //         double r = std::sqrt(dxx * dxx + dyy * dyy);
    //
    //         if (r <= radius) {
    //             // h(r) = (cos(asin(r / R)) - cos(theta)) * R
    //             double val = (std::cos(std::asin(r / radius)) - std::cos(theta_initial_d)) * radius;
    //             film_thickness[i][j] = (val > 0.0) ? val : minimal_thickness;
    //         } else {
    //             film_thickness[i][j] = minimal_thickness;
    //         }
    //     }
    // }

    for (size_t i = 0; i <= Nx - 1; i++) {
        for (size_t j = 0; j <= Ny - 1; j++) {
            film_thickness[i][j] = 0.05;
        }
    }

    double height = 10.0;    // заданная высота
    size_t area = 625;       // площадь в ячейках (например 5x5)

    size_t side = static_cast<size_t>(std::sqrt(area));
    if (side * side < area) side++; // чтобы гарантировать площадь ≥ заданной

    size_t cxx = Nx / 2;
    size_t cyy = Ny / 2;

    size_t half = side / 2;

    for (size_t i = cxx - half; i <= cxx + half && i < Nx; i++) {
        for (size_t j = cyy - half; j <= cyy + half && j < Ny; j++) {
            film_thickness[i][j] = height;
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
    // compute_all_forces();

    for (int step = 1; step <= steps_number; step++) {
        std::cout<<"============================"<<std::endl;
        std::cout << "step = " << step << std::endl;


        take_step();
        output_fields(step);
        output_max_height(step);
        output_min_height(step);
        output_total_mass(step);
        output_dh(step);
        output_energy(step);
    }
}

inline void simulate_bubble_vibro() {

    tau = 0.923;
    viscosity = (tau - 0.5) * sound_speed_squared;
    radius_initial = 80.0;
    delta = 1.0;
    surface_tension = 0.00005;
    gravity = 1.0 * pow(10, -6);
    theta_initial = 30.0;
    theta_initial_d = theta_initial * (M_PI / 180);
    theta_current = theta_initial_d;
    minimal_thickness = 0.05;

    steps_number = 5000000;

    double radius=radius_initial;
    double x0 = Nx / 2.0;
    double y0 = Ny / 2.0;

    bubble_volume = ((M_PI * radius * radius * radius) / 3.0) *  (1.0 - cos(theta_initial_d)) * (1.0 - cos(theta_initial_d)) * (2.0 + cos(theta_initial_d));

    Fx = 0;
    Fy = 0;

    // for (int i = 0; i < Nx; ++i) {
    //     for (int j = 0; j < Ny; ++j) {
    //         double dxx = i - x0;
    //         double dyy = j - y0;
    //         double r = std::sqrt(dxx * dxx + dyy * dyy);
    //
    //         if (r <= radius) {
    //             // h(r) = (cos(asin(r / R)) - cos(theta)) * R
    //             double val = (std::cos(std::asin(r / radius)) - std::cos(theta_initial_d)) * radius;
    //             film_thickness[i][j] = (val > 0.0) ? val : minimal_thickness;
    //         } else {
    //             film_thickness[i][j] = minimal_thickness;
    //         }
    //     }
    // }

    for (size_t i = 0; i <= Nx - 1; i++) {
        for (size_t j = 0; j <= Ny - 1; j++) {
            film_thickness[i][j] = 0.05;
        }
    }

    double height = 10.0;    // заданная высота
    area = 400;              // площадь в ячейках (например 5x5)

    size_t side = static_cast<size_t>(std::sqrt(area));
    if (side * side < area) side++; // чтобы гарантировать площадь ≥ заданной

    size_t cxx = Nx / 2;
    size_t cyy = Ny / 2;

    size_t half = side / 2;

    for (size_t i = cxx - half; i <= cxx + half && i < Nx; i++) {
        for (size_t j = cyy - half; j <= cyy + half && j < Ny; j++) {
            film_thickness[i][j] = height;
        }
    }

    modulated_gravity = gravity;
    output_fields(0);
    compute_feq_2();
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            for (int k = 0; k < Nc; k++){
                f[i][j][k] = feq[i][j][k];
            }

        }
    }

    amplitude = 0*30;//14.14213;
    omega     = 0.05;

    dump_initial_params();
    // compute_all_forces();

    for (int step = 1; step <= steps_number; step++) {
        std::cout<<"============================"<<std::endl;
        std::cout << "step = " << step << std::endl;

        // double t = step * delta_t;
        modulated_gravity = gravity *  (1.0 + amplitude * amplitude * omega * sin(omega * step));

        take_step();
        output_fields(step);
        output_max_height(step);
        output_min_height(step);
        output_total_mass(step);
        output_dh(step);
        output_energy(step);
    }
}


void simulate_square_drop() {
    tau = 1.0;
    viscosity = (tau - 0.5) * sound_speed_squared;

    delta = 1.0;
    surface_tension = 0.005;
    gravity = 20.0 * pow(10, -7);
    theta_initial = 30.0;
    theta_initial_d = theta_initial * (M_PI / 180);
    theta_current = theta_initial_d;
    minimal_thickness = 0.07;

    steps_number = 2000000;
    double inclination_angle = 90;
    Fx = 0*gravity * sin(inclination_angle * (M_PI / 180));
    Fy = -0*gravity * cos(inclination_angle * (M_PI / 180));

    double h0 = 1.0;

    // for (size_t i = 0; i <= Nx - 1; i++) {
    //     for (size_t j = 0; j <= Ny - 1; j++) {
    //         film_thickness[i][j] = 0.05;
    //     }
    // }
    //
    // double height = 10.0;    // заданная высота
    // size_t area = 2500;       // площадь в ячейках (например 5x5)
    //
    // size_t side = static_cast<size_t>(std::sqrt(area));
    // if (side * side < area) side++; // чтобы гарантировать площадь ≥ заданной
    //
    // size_t cxx = Nx / 2;
    // size_t cyy = Ny / 2;
    //
    // size_t half = side / 2;
    //
    // for (size_t i = cxx - half; i <= cxx + half && i < Nx; i++) {
    //     for (size_t j = cyy - half; j <= cyy + half && j < Ny; j++) {
    //         film_thickness[i][j] = height;
    //     }
    // }

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
        output_min_height(step);
        output_total_mass(step);
        output_dh(step);
        output_energy(step);
    }
}


inline void simulate_sliding_square_drop() {

    tau = 0.923;
    viscosity = (tau - 0.5) * sound_speed_squared;
    radius_initial = 80.0;
    delta = 1.0;
    surface_tension = 0.00005;
    gravity = 1.0 * pow(10, -5);
    theta_initial = 80.0;
    theta_initial_d = theta_initial * (M_PI / 180);
    theta_current = theta_initial_d;
    minimal_thickness = 0.05;

    steps_number = 5000000;

    double inclination_angle = 45;
    Fx = 1.0 * pow(10, -5) * sin(inclination_angle * (M_PI / 180));
    Fy = 0;

    for (size_t i = 0; i <= Nx - 1; i++) {
        for (size_t j = 0; j <= Ny - 1; j++) {
            film_thickness[i][j] = 0.05;
        }
    }

    for (size_t i = 0; i <= (Nx - (Nx / 4)); i++) {
        for (size_t j = 0; j <= Ny - 1; j++) {
            film_thickness[i][j] = 1.0;
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
    // compute_all_forces();

    for (int step = 1; step <= steps_number; step++) {
        std::cout<<"============================"<<std::endl;
        std::cout << "step = " << step << std::endl;

        take_step();
        output_fields(step);
        output_max_height(step);
        output_min_height(step);
        output_total_mass(step);
        output_dh(step);
        output_energy(step);
    }
}



int main() {
    greetings();
    // simulate_falling_film();
    // run_disturbed_interface();
    // run_wave_pattern_interface();
    // simulate_relaxing_droplet();
    // run_flat();
    // run_disturbed_interface_v2();
    // simulate_random_interface();
    // simulate_square_drop();

    // simulate_bubble();
    simulate_bubble_vibro();
    return 0;
}