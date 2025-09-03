//
// Created by Иван Володин on 25.08.2025.
//

#ifndef THIN_FILM_LBM_CONSTANTS_H
#define THIN_FILM_LBM_CONSTANTS_H

#include <vector>

#include "controlling_params.h"

using std::vector;

constexpr int Nx = 100;
constexpr int Ny = 100;
constexpr int Nc = 9;

constexpr int cx[9] = {0, 1, 0, -1, 0, 1, -1, -1, 1};
constexpr int cy[9] = {0, 0, 1, 0, -1, 1, 1, -1, -1};

constexpr double w[9] = {
    16 / 36.0,
    4 / 36.0,
    4 / 36.0,
    4 / 36.0,
    4 / 36.0,
    1 / 36.0,
    1 / 36.0,
    1 / 36.0,
    1 / 36.0
};

constexpr double dx = 1.0;
constexpr double dy = 1.0;
constexpr double dt = 1.0;

constexpr double sound_speed_squared = (1.0 / 3.0) * ((dx * dx) / dt);
inline double viscosity = (tau - 0.5) * sound_speed_squared;

inline vector<vector<vector<double>>> f(Nx, vector<vector<double>>(Ny, vector<double>(Nc)));
inline vector<vector<vector<double>>> feq(Nx, vector<vector<double>>(Ny, vector<double>(Nc)));

inline vector<vector<vector<double>>> u(Nx, vector<vector<double>>(Ny, vector<double>(2)));
inline vector<vector<double>> film_thickness(Nx, vector<double>(Ny));
inline vector<vector<double>> film_thickness_previous(Nx, vector<double>(Ny));

inline vector<vector<vector<double>>> d_film_thickness(Nx, vector<vector<double>>(Ny, vector<double>(2)));

inline vector<vector<double>> laplacian_film_thickness(Nx, vector<double>(Ny));
inline vector<vector<vector<double>>> d_laplacian_film_thickness(Nx, vector<vector<double>>(Ny, vector<double>(2)));

inline vector<vector<double>> hydrostatic_pressure(Nx, vector<double>(Ny));
inline vector<vector<double>> pii(Nx, vector<double>(Ny));
inline vector<vector<double>> film_pressure(Nx, vector<double>(Ny));

inline vector<vector<vector<double>>> d_film_pressure(Nx, vector<vector<double>>(Ny, vector<double>(2)));

inline vector<vector<vector<double>>> f_total(Nx, vector<vector<double>>(Ny, vector<double>(Nc)));
inline vector<vector<vector<double>>> f_film(Nx, vector<vector<double>>(Ny, vector<double>(Nc)));
inline vector<vector<vector<double>>> f_fric(Nx, vector<vector<double>>(Ny, vector<double>(Nc)));


#endif //THIN_FILM_LBM_CONSTANTS_H