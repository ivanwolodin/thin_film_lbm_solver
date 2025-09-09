#ifndef THIN_FILM_LBM_CONTROLLING_PARAMS_H
#define THIN_FILM_LBM_CONTROLLING_PARAMS_H

#include <cmath>

constexpr double rho_0 = 1.0;
inline double tau = 0.923;

inline double surface_tension = 0.00005; // surface tension
inline double delta = 1.0;                  // eﬀective slip length

inline double bubble_volume;

inline double gravity = 1.0 * pow(10, -5);

inline double radius_initial = 80.0;

inline double theta_initial = 30.0;
inline double theta_initial_d = theta_initial * (M_PI / 180);

inline double theta_equilibrium = 15.0;
inline double theta_equilibrium_d = theta_equilibrium * (M_PI / 180);

inline double thickness_max = 0.0;
inline double thickness_min = 10.0;

inline double total_energy = 0.0;

inline double minimal_thickness = 0.07;

inline int center_x = 0;
inline int center_y = 0;

inline double theta_current = theta_initial_d;

inline double spreading_radius;

inline double radius_current;

inline int steps_number;

inline double thickness_integral = 0.0;

inline double Fx = -1000;
inline double Fy = -1000;

inline double modulated_gravity = 10000;

// Lennard-Johnson
constexpr int n = 9;
constexpr int m = 3;


inline double amplitude = 11110.01;
inline double omega     = 1111110.05;
inline size_t area;
#endif //THIN_FILM_LBM_CONTROLLING_PARAMS_H