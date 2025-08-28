#ifndef THIN_FILM_LBM_CONTROLLING_PARAMS_H
#define THIN_FILM_LBM_CONTROLLING_PARAMS_H

#include <cmath>

constexpr double rho_0 = 1.0;
constexpr double tau = 0.923;

constexpr double surface_tension = 0.00005; // surface tension
inline double delta = 1.0;                  // eﬀective slip length

inline double bubble_volume;

const double gravity = 1.0 * pow(10, -5);

inline double radius_initial = 80.0;

inline double theta_initial = 30.0;
inline double theta_initial_d = theta_initial * (M_PI / 180);

inline double theta_equilibrium = 15.0;
inline double theta_equilibrium_d = theta_equilibrium * (M_PI / 180);

inline double thickness_max = 0.0;

inline double minimal_thickness = 0.05;

inline int center_x = 0;
inline int center_y = 0;

inline double theta_current = theta_initial_d;

inline double spreading_radius;

inline double radius_current;

// Lennard-Johnson
constexpr int n = 9;
constexpr int m = 3;

#endif //THIN_FILM_LBM_CONTROLLING_PARAMS_H