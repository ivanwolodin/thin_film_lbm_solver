#ifndef THIN_FILM_LBM_STREAMING_AND_BOUNDARY_H
#define THIN_FILM_LBM_STREAMING_AND_BOUNDARY_H

#include "constants.h"


inline void streaming_step() {
    for (int x = Nx - 1; x >= 1; x--) {
        for (int y = Ny - 1; y >= 0; y--) {
            f[x][y][1] = f[x - 1][y][1];
        }
    }

    for (int x = Nx - 1; x >= 0; x--) {
        for (int y = Ny - 1; y >= 1; y--) {
            f[x][y][2] = f[x][y - 1][2];
        }
    }

    for (int x = 0; x <= Nx - 2; x++) {
        for (int y = 0; y <= Ny - 1; y++) {
            f[x][y][3] = f[x + 1][y][3];
        }
    }

    for (int x = 0; x <= Nx - 1; x++) {
        for (int y = 0; y <= Ny - 2; y++) {
            f[x][y][4] = f[x][y + 1][4];
        }
    }

    for (int x = Nx - 1; x >= 1; x--) {

        for (int y = Ny - 1; y >= 1; y--) {
            f[x][y][5] = f[x - 1][y - 1][5];
        }
    }

    for (int x = 0; x <= Nx - 2; x++) {
        for (int y = Ny - 1; y >= 1; y--) {
            f[x][y][6] = f[x + 1][y - 1][6];
        }
    }

    for (int x = 0; x <= Nx - 2; x++) {
        for (int y = 0; y <= Ny - 2; y++) {
            f[x][y][7] = f[x + 1][y + 1][7];
        }
    }

    for (int x = Nx - 1; x >= 1; x--) {
        for (int y = 0; y <= Ny - 2; y++) {
            f[x][y][8] = f[x - 1][y + 1][8];
        }
    }
}

inline void boundary_conditions(){
    // right periodic
    for (int j = 0; j <= Ny - 1; j++)
    {
        f[Nx - 1][j][6] = f[0][j][6];
        f[Nx - 1][j][3] = f[0][j][3];
        f[Nx - 1][j][7] = f[0][j][7];
    }

    // left periodic
    for (int j = 0; j <= Ny - 1; j++)
    {
        f[0][j][8] = f[Nx - 1][j][8];
        f[0][j][1] = f[Nx - 1][j][1];
        f[0][j][5] = f[Nx - 1][j][5];
    }

    // // right no-slip
    // for (int j = 0; j <= Ny - 1; j++) {
    //     f[Nx - 1][j][6] = f[Nx - 1][j][8];
    //     f[Nx - 1][j][3] = f[Nx - 1][j][1];
    //     f[Nx - 1][j][7] = f[Nx - 1][j][5];
    // }
    //
    // // left no-slip
    // for (int j = 0; j <= Ny - 1; j++) {
    //     f[0][j][8] = f[0][j][6];
    //     f[0][j][1] = f[0][j][3];
    //     f[0][j][5] = f[0][j][7];
    // }

    //  bottom periodic
    for (int i = 1; i < Nx - 1; i++)
    {
        f[i][0][2] = f[i][Ny - 1][2];
        f[i][0][6] = f[i][Ny - 1][6];
        f[i][0][5] = f[i][Ny - 1][5];
    }

    // upper periodic
    for (int i = 1; i < Nx - 1; i++)
    {
        f[i][Ny - 1][4] = f[i][0][4];
        f[i][Ny - 1][7] = f[i][0][7];
        f[i][Ny - 1][8] = f[i][0][8];
    }
}

#endif //THIN_FILM_LBM_STREAMING_AND_BOUNDARY_H