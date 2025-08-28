#ifndef THIN_FILM_LBM_INITIAL_DISTRIBUTION_H
#define THIN_FILM_LBM_INITIAL_DISTRIBUTION_H

#include <iostream>

#include "constants.h"
#include "controlling_params.h"

using std::cout;
using std::endl;

inline void set_bubble() {
    double x0 = Nx / 2.0;
    double y0 = Ny / 2.0;

    const double a_frac = 0.2;  // 20% to have a space to spread
    const double a = a_frac * Nx;

    const double R = std::sin(theta_initial_d);

    // delta = R;

    bubble_volume = ((M_PI * R * R * R) / 3.0) *
                    (1.0 - cos(theta_initial_d)) * (1.0 - cos(theta_initial_d)) * (2.0 + cos(theta_initial_d));

    cout<<"delta= "<< delta << endl;
    cout<<"initial_radius= "<< R <<endl;
    cout<<"bubble_volume= "<< bubble_volume <<endl;

    for (int i = 0; i < Nx; ++i) {
        for (int j = 0; j < Ny; ++j) {
            double r = std::sqrt((i - x0)*(i - x0) + (j - y0)*(j - y0));
            if (r <= a) {
                film_thickness[i][j] = std::sqrt(R * R - r * r) - R * std::cos(theta_initial_d);
            } else {
                film_thickness[i][j] = 0.0;
            }
        }
    }
}

inline void set_droplet(

){
    double radius=radius_initial;
    double x0 = Nx / 2.0;
    double y0 = Ny / 2.0;

    bubble_volume = ((M_PI * radius * radius * radius) / 3.0) *  (1.0 - cos(theta_initial_d)) * (1.0 - cos(theta_initial_d)) * (2.0 + cos(theta_initial_d));

    for (int i = 0; i < Nx; ++i) {
        for (int j = 0; j < Ny; ++j) {
            double dxx = i - x0;
            double dyy = j - y0;
            double r = std::sqrt(dxx * dxx + dyy * dyy);

            if (r <= radius) {
                // h(r) = (cos(asin(r / R)) - cos(theta)) * R
                double val = (std::cos(std::asin(r / radius)) - std::cos(theta_initial_d)) * radius;
                film_thickness[i][j] = (val > 0.0) ? val : minimal_thickness;
            } else {
                film_thickness[i][j] = minimal_thickness;
            }
        }
    }
}


inline void set_flat(

) {
    for (int i = 0; i < Nx; ++i) {
        for (int j = 0; j < Ny; ++j) {
            film_thickness[i][j] = 1.0;
        }
    }
}




#endif //THIN_FILM_LBM_INITIAL_DISTRIBUTION_H