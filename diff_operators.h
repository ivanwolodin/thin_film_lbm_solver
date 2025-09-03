#ifndef THIN_FILM_LBM_DIFF_OPERATORS_H
#define THIN_FILM_LBM_DIFF_OPERATORS_H
#include "constants.h"

inline void compute_grad_classic(
    ::vector<vector<vector<double>>> &grad_func,
    const vector<vector<double>> &func)
{
    for (int i = 2; i < Nx - 2; i++) {
        for (int j = 2; j < Ny - 2; j++) {
            double dfdx = (-func[i + 2][j] + 8 * func[i + 1][j] - 8 * func[i - 1][j] + func[i - 2][j]) / (12.0);
            double dfdy = (-func[i][j + 2] + 8*func[i][j + 1] - 8 * func[i][j - 1] + func[i][j - 2]) / (12.0);

            grad_func[i][j][0] = dfdx;
            grad_func[i][j][1] = dfdy;
        }
    }
}


inline void compute_grad(
    ::vector<vector<vector<double>>> &grad_func,
    const vector<vector<double>> &func)
{
    double summ_x;
    double summ_y;
    int ii;
    int jj;

    for (int i = 1; i < Nx - 1; i++){
        for (int j = 1; j < Ny - 1; j++) {
            summ_x = 0.0;
            summ_y = 0.0;
            for (int k = 1; k < Nc; k++){
                ii = i + cx[k];
                jj = j + cy[k];
                summ_x += (w[k] * cx[k] * func[ii][jj]);
                summ_y += (w[k] * cy[k] * func[ii][jj]);
            }
            grad_func[i][j][0] = 3.0 * summ_x;
            grad_func[i][j][1] = 3.0 * summ_y;
        }
    }

    for (int j = 1; j < Ny - 1; j++) {
        grad_func[0][j][0] = func[0][j] - func[1][j];
        grad_func[0][j][1] = func[0][j] - func[0][j - 1];

        grad_func[Nx - 1][j][0] = func[Nx - 1][j] - func[Nx - 2][j];
        grad_func[Nx - 1][j][1] = func[Nx - 1][j] - func[Nx - 1][j - 1];
    }

    // for (int j = 1; j < Ny - 1; j++) {
    //     // левая стенка (i = 0)
    //     summ_x = 0.0;
    //     summ_y = 0.0;
    //     for (int k = 1; k < Nc; k++) {
    //         ii = (0 + cx[k] + Nx) % Nx;   // периодическая индексация
    //         jj = (j + cy[k] + Ny) % Ny;
    //         // cout<< "ii = " << ii << ", jj = " << jj << std::endl;
    //         // getchar();
    //         summ_x += (w[k] * cx[k] * func[ii][jj]);
    //         summ_y += (w[k] * cy[k] * func[ii][jj]);
    //     }
    //     grad_func[0][j][0] = 3.0 * summ_x;
    //     grad_func[0][j][1] = 3.0 * summ_y;
    //
    //     // правая стенка (i = Nx-1)
    //     summ_x = 0.0;
    //     summ_y = 0.0;
    //     for (int k = 1; k < Nc; k++) {
    //         ii = ((Nx - 1) + cx[k] + Nx) % Nx;
    //         jj = (j + cy[k] + Ny) % Ny;
    //         summ_x += (w[k] * cx[k] * func[ii][jj]);
    //         summ_y += (w[k] * cy[k] * func[ii][jj]);
    //     }
    //     grad_func[Nx - 1][j][0] = 3.0 * summ_x;
    //     grad_func[Nx - 1][j][1] = 3.0 * summ_y;
    // }

}

inline void compute_laplacian(
    vector<vector<double>> &laplacian_func,
    const vector<vector<double>> &func)
{
    double rectangular_sum = 0.0;
    double diagonal_sum = 0.0;
    int ii;
    int jj;
    for (int i = 1; i < Nx - 1; i++){
        for (int j = 1; j < Ny - 1; j++){

            rectangular_sum = 0.0;
            for (int k = 1; k <= 4; k++){
                ii = i + cx[k];
                jj = j + cy[k];
                rectangular_sum += (w[1] * func[ii][jj]);
            }

            diagonal_sum = 0.0;
            for (int k = 5; k <= 8; k++){
                ii = i + cx[k];
                jj = j + cy[k];
                diagonal_sum += (w[5] * func[ii][jj]);
            }

            laplacian_func[i][j] = (1.0 / 6.0) * (4.0 * rectangular_sum + 1.0 * diagonal_sum - 20.0 * func[i][j]);
        }
    }
}

inline void compute_laplacian_classic(
    vector<vector<double>> &laplacian_func,
    const vector<vector<double>> &func)
{
    const double coef = 1.0 / (6.0 * 1.0 * 1.0);
    for (int i = 0; i < Nx; ++i) for (int j = 0; j < Ny; ++j) laplacian_func[i][j] = 0.0;

    for (int i = 1; i <= Nx - 2; ++i) {
        for (int j = 1; j <= Ny - 2; ++j) {
            laplacian_func[i][j] = coef * (
                -20.0 * func[i][j]
                + 4.0 * (func[i+1][j] + func[i-1][j] + func[i][j+1] + func[i][j-1])
                + (func[i+1][j+1] + func[i-1][j+1] + func[i-1][j-1] + func[i+1][j-1])
            );
        }
    }
    // // граница i=0
    // for (int j = 0; j < Ny; ++j) {
    //     int ip = (0 + 1) % Nx;
    //     int im = (0 - 1 + Nx) % Nx;
    //     int jp = (j + 1) % Ny;
    //     int jm = (j - 1 + Ny) % Ny;
    //
    //     laplacian_func[0][j] = coef * (
    //         -20.0 * func[0][j]
    //         + 4.0 * (func[ip][j] + func[im][j] + func[0][jp] + func[0][jm])
    //         + (func[ip][jp] + func[im][jp] + func[im][jm] + func[ip][jm])
    //     );
    // }
    //
    // // граница i = Nx-1
    // for (int j = 0; j < Ny; ++j) {
    //     int i = Nx - 1;
    //     int ip = (i + 1) % Nx;
    //     int im = (i - 1 + Nx) % Nx;
    //     int jp = (j + 1) % Ny;
    //     int jm = (j - 1 + Ny) % Ny;
    //
    //     laplacian_func[i][j] = coef * (
    //         -20.0 * func[i][j]
    //         + 4.0 * (func[ip][j] + func[im][j] + func[i][jp] + func[i][jm])
    //         + (func[ip][jp] + func[im][jp] + func[im][jm] + func[ip][jm])
    //     );
    // }
}

#endif //THIN_FILM_LBM_DIFF_OPERATORS_H
