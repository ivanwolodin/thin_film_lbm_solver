#ifndef THIN_FILM_LBM_DIFF_OPERATORS_H
#define THIN_FILM_LBM_DIFF_OPERATORS_H
#include "constants.h"

inline void compute_grad(
    ::vector<vector<vector<double>>> &grad_func,
    const vector<vector<double>> &func)
{
    double summ_x;
    double summ_y;
    int ii;
    int jj;

    for (int i = 1; i < Nx - 1; i++){
        for (int j = 1; j < Ny - 1; j++){
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
}

#endif //THIN_FILM_LBM_DIFF_OPERATORS_H