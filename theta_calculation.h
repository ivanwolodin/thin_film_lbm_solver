
#ifndef THIN_FILM_LBM_THETA_CALCULATION_H
#define THIN_FILM_LBM_THETA_CALCULATION_H

#include <iostream>

#include "constants.h"
#include "controlling_params.h"

inline void compute_max_height() {
    thickness_max = 0.0;
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            if (film_thickness[i][j] > thickness_max) {
                thickness_max = film_thickness[i][j];
            }
        }
    }
    cout<<"thickness_max: " <<thickness_max<<endl;
}

inline void compute_min_height() {
    thickness_min = 10.0;
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            if (film_thickness[i][j] < thickness_min) {
                thickness_min = film_thickness[i][j];
            }
        }
    }
    cout << "thickness_min: " << thickness_min << endl;
}


inline void compute_u_total() {
    double u_total = 0.0;
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            u_total += u[i][j][0];
        }
    }
    cout<<"u_total: " <<u_total<<endl;
}

inline void compute_v_total() {
    double v_total = 0.0;
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            v_total += u[i][j][1];
        }
    }
    cout<<"v_total: " <<v_total<<endl;
}

inline void compute_energy() {
    total_energy = 0.0;
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            total_energy += film_thickness[i][j];
        }
    }
    total_energy *= gravity;
    double velocity_modulus = 0.0;

    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            velocity_modulus += (u[i][j][0] * u[i][j][0] + u[i][j][1] * u[i][j][1]);
        }
    }
    total_energy += (0.5 * velocity_modulus);
}



inline void compute_height_and_radius() {
    // --- 1. Максимальная высота и её координаты
    int jc = 0, ic = 0;

    thickness_max = 0.0;
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            if (film_thickness[i][j] > thickness_max) {
                thickness_max = film_thickness[i][j];
                ic = i;
                jc = j;
            }
        }
    }
    center_x = ic;
    center_y = jc;

    int r_left = 0, r_right = 0, r_up = 0, r_down = 0;
    const double eps = 1e-6;  // допуск для сравнения толщин
    minimal_thickness = 0.05;
    // вправо
    for (int i = center_x; i < Nx - 1; i++) {
        if (fabs(film_thickness[i][center_y] - minimal_thickness) < eps) {
            r_right = i - center_x;
            break;
        }
    }

    // влево
    for (int i = center_x; i >= 0; i--) {
        if (fabs(film_thickness[i][center_y] - minimal_thickness) < eps) {
            r_left = center_x - i;
            break;
        }
    }

    // вверх
    for (int j = center_y; j < Ny - 1; j++) {
        if (fabs(film_thickness[center_x][j] - minimal_thickness) < eps) {
            r_down = j - center_y;
            break;
        }
    }

    // вниз
    for (int j = center_y; j >= 0; j--) {
        if (fabs(film_thickness[center_x][j] - minimal_thickness) < eps) {
            r_up = center_y - j;
            break;
        }
    }

    // усреднённый радиус
    spreading_radius = (r_left + r_right + r_up + r_down) / 4.0;

    std::cout << "spreading radius (avg): " << spreading_radius << std::endl;
    std::cout << "thickness_max: " << thickness_max
              << " at (" << center_x << ", " << center_y << ")" << std::endl;
}

inline void compute_theta() {
    compute_height_and_radius();

    radius_current = (spreading_radius * spreading_radius + thickness_max * thickness_max) / (2.0 * spreading_radius);

    double y = (3.0 * bubble_volume) / (radius_current * radius_current * radius_current * M_PI);

    if (y < 0.0 || y > 4.0) {
        std::cout << "Ошибка: y = " << y << std::endl;
        throw std::invalid_argument("Решения с реальным θ нет: V/Const1 должно быть в [0,4]");
    }

    // Функция g(x) = x^3 - 3x + 2 - y
    auto g = [y](double x) { return x*x*x - 3*x + 2 - y; };

    double a = -1.0, b = 1.0;
    double ga = g(a), gb = g(b);

    if (ga * gb > 0) {
        std::cout << "Ошибка: g(a) = " << ga << ", g(b) = " << gb << std::endl;
        throw std::runtime_error("Корень не найден на отрезке [-1,1]");
    }

    double tol = 1e-12;
    double x = 0.0;

    for (int i = 0; i < 100; ++i) {
        double m1 = 0.5 * (a + b);
        double gm = g(m1);

        if (std::abs(gm) < tol || 0.5*(b-a) < tol) {
            x = m1;
            break;
        }

        if (ga * gm > 0) {
            a = m1;
            ga = gm;
        } else {
            b = m1;
        }
    }

    // Ограничиваем x диапазоном [-1,1] на всякий случай
    if (x < -1.0) x = -1.0;
    if (x > 1.0) x = 1.0;

    theta = std::acos(x);
    std::cout<<"theta_current: " <<theta<< std::endl <<std::endl;
}

double cubic_interp(double x[4], double y[4], double x0) {
    double result = 0.0;
    for (int i = 0; i < 4; i++) {
        double term = y[i];
        for (int j = 0; j < 4; j++) {
            if (j != i)
                term *= (x0 - x[j]) / (x[i] - x[j]);
        }
        result += term;
    }
    return result;
}

inline void compute_spreading_radius_v2() {
    int Nbg = 5;
    double background = 0.0;
    for (int j = 0; j < Nbg; j++) {
        background += film_thickness[Nx/2][j];
    }
    background /= Nbg;

    double threshold = background * 2.0;
    spreading_radius = -1.0;

    // Ищем индекс перехода
    int idx = -1;
    for (int j = 1; j < Ny-2; j++) {
        if (film_thickness[Nx/2][j-1] < threshold && film_thickness[Nx/2][j] >= threshold) {
            idx = j;
            break;
        }
    }

    if (idx != -1) {
        // Берем 4 точки вокруг порога для кубической интерполяции
        double x[4] = { (double)(idx-2), (double)(idx-1), (double)(idx), (double)(idx+1) };
        double y[4] = { film_thickness[Nx/2][idx-2], film_thickness[Nx/2][idx-1],
                        film_thickness[Nx/2][idx], film_thickness[Nx/2][idx+1] };

        // Решаем уравнение v(y) = threshold методом Ньютона/брутфорс (здесь простой поиск)
        double step = 0.001;
        double j_interp = idx-1;  // стартовая точка
        for (double jj = idx-1; jj <= idx; jj += step) {
            if (cubic_interp(x, y, jj) >= threshold) {
                j_interp = jj;
                break;
            }
        }

        spreading_radius = (Ny/2)*dy - j_interp*dy;  // радиус в физических единицах
        if (spreading_radius >= 0.0)
            std::cout << "Spreading radius = " << spreading_radius << std::endl;
        else
            std::cout << "Not found\n";
    } else {
        std::cout << "Not found\n";
    }
}



inline void compute_spreading_radius() {
    int Nbg = 5;
    double background = 0.0;
    for (int j = 0; j < Nbg; j++) {
        background += film_thickness[Nx/2][j];
    }
    background /= Nbg;

    double threshold = background * 2.0;

    spreading_radius = -1.0;

    for (int j = 1; j < Ny/2; j++) {
        double v1 = film_thickness[Nx/2][j-1];
        double v2 = film_thickness[Nx/2][j];

        if (v1 < threshold && v2 >= threshold) {
            // линейная интерполяция
            double t = (threshold - v1) / (v2 - v1);
            spreading_radius = (j - 1) + t;
            break;
        }
    }
    spreading_radius = (Ny/2) - spreading_radius;
    if (spreading_radius >= 0.0)
        std::cout << "Spreading radius = " << spreading_radius << std::endl;
    else
        std::cout << "Not found\n";
}


#endif //THIN_FILM_LBM_THETA_CALCULATION_H