
#ifndef THIN_FILM_LBM_THETA_CALCULATION_H
#define THIN_FILM_LBM_THETA_CALCULATION_H

#include <iostream>

#include "constants.h"
#include "controlling_params.h"

inline void compute_total_mass() {
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

    // --- 2. Минимальная толщина (подложка)
    // double thickness_min = thickness_max;
    // for (int i = 0; i < Nx; i++) {
    //     for (int j = 0; j < Ny; j++) {
    //         if (film_thickness[i][j] < thickness_min) {
    //             thickness_min = film_thickness[i][j];
    //         }
    //     }
    // }
    //
    int r_left = 0, r_right = 0, r_up = 0, r_down = 0;
    //
    // // вправо
    // for (int i = center_x; i < Nx - 1; i++) {
    //     if (film_thickness[i][jc] <= thickness_min) {
    //         r_right = i - center_x;
    //         break;
    //     }
    // }
    //
    // // влево
    // for (int i = center_x; i >= 0; i--) {
    //     if (film_thickness[i][jc] <= thickness_min) {
    //         r_left = center_x - i;
    //         break;
    //     }
    // }
    //
    // // вниз (ось Y+)
    // for (int j = center_y; j < Ny - 1; j++) {
    //     if (film_thickness[center_x][j] <= thickness_min) {
    //         r_down = j - center_y;
    //         break;
    //     }
    // }
    //
    // // вверх (ось Y-)
    // for (int j = center_y; j >= 0; j--) {
    //     if (film_thickness[center_x][j] <= thickness_min) {
    //         r_up = center_y - j;
    //         break;
    //     }
    // }


    // вправо
    for (int i = center_x; i < Nx - 1; i++) {
        if (film_thickness[i][center_y] == minimal_thickness) {
            r_right = i - center_x;
            break;
        }
    }

    // влево
    for (int i = center_x; i >= 0; i--) {
        if (film_thickness[i][center_y] == minimal_thickness) {
            r_left = center_x - i;
            break;
        }
    }

    // вверх
    for (int j = center_y; j < Ny - 1; j++) {
        if (film_thickness[center_x][j] == minimal_thickness) {
            r_down = j - center_y;
            break;
        }
    }

    // вниз
    for (int j = center_y; j >= 0; j--) {
        if (film_thickness[center_x][j] == minimal_thickness) {
            r_up = center_y - j;
            break;
        }
    }

    spreading_radius = std::max({r_left, r_right, r_up, r_down});
    std::cout<<"spreading: " << spreading_radius<<std::endl;
    std::cout<<"thickness_max: " << thickness_max<<" at ("<<center_x<< ", " <<center_y <<")"<<std::endl;
    // std::cout<<"thickness_min: " << thickness_min<<std::endl;

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

    theta_current = std::acos(x);
    std::cout<<"theta_current: " <<theta_current<< std::endl <<std::endl;
}

#endif //THIN_FILM_LBM_THETA_CALCULATION_H