#ifndef THIN_FILM_LBM_OUTPUT_H
#define THIN_FILM_LBM_OUTPUT_H

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#include "constants.h"
#include "controlling_params.h"

inline void greetings() {
    std::cout<<"================================================="<<std::endl;
    std::cout<<"================================================="<<std::endl;
    std::cout<<"====LATTICE BOLTZMANN SOLVER for thin films======"<<std::endl;
    std::cout<<"================================================="<<std::endl;
    std::cout<<"================================================="<<std::endl;
}

inline void dump_initial_params() {
    std::ofstream filestr;

    std::string fileName = "initial_params.txt";

    filestr.open(fileName);

    filestr<<"Nx= "<< Nx << std::endl;
    filestr<<"Ny= "<< Ny << std::endl;

    filestr<<"gravity= "<< gravity << std::endl;

    filestr<<"tau= "<< tau << std::endl;
    filestr<<"viscosity= "<< viscosity << std::endl;

    filestr<<"surface_tension= "<< surface_tension << std::endl;

    filestr<<"theta_initial= "<< theta_initial << std::endl;
    filestr<<"theta_initial_d= "<< theta_initial_d << std::endl;

    filestr<<"theta_eq= "<< theta_equilibrium << std::endl;
    filestr<<"theta_eq_d= "<< theta_equilibrium_d << std::endl;

    filestr<<std::endl<<std::endl;
    filestr<<"delta= "<< delta << std::endl;
    filestr<<std::endl<<std::endl;

    filestr<<"_________________________________" << std::endl;

    filestr.close();
    if (filestr.is_open()) std::cout << "The file has not been closed!" << std::endl;
}

inline void output_field(int step_time, const std::string& which_field)
{
    std::ofstream filestr;

    std::string fileName = "res/" + which_field + "_" + std::to_string(step_time) + ".txt";

    filestr.open(fileName);

    for (int x = 0; x <= Nx - 1; x++)
    {
        for (int y = 0; y <= Ny - 1; y++)
        {

            if (which_field == "v")
            {
                filestr << x << " " << y << " " << u[x][y][1] << std::endl;
            }

            if (which_field == "u")
            {
                filestr << x << " " << y << " " << u[x][y][0] << std::endl;
            }


            if (which_field == "film_thickness")
            {
                filestr << x << " " << y << " " << film_thickness[x][y] << std::endl;
            }

            if (which_field == "film_pressure")
            {
                filestr << x << " " << y << " " << film_pressure[x][y] << std::endl;
            }

            if (which_field == "f_film_x")
            {
                filestr << x << " " << y << " " << f_film[x][y][0] << std::endl;
            }

            if (which_field == "f_film_y")
            {
                filestr << x << " " << y << " " << f_film[x][y][1] << std::endl;
            }

            if (which_field == "f_fric_x")
            {
                filestr << x << " " << y << " " << f_fric[x][y][0] << std::endl;
            }

            if (which_field == "f_fric_y")
            {
                filestr << x << " " << y << " " << f_fric[x][y][1] << std::endl;
            }

            if (which_field == "f_total_x")
            {
                filestr << x << " " << y << " " << f_total[x][y][0] << std::endl;
            }

            if (which_field == "f_total_y")
            {
                filestr << x << " " << y << " " << f_total[x][y][1] << std::endl;
            }

            if (which_field == "feq")
            {
                for (int k = 0; k < Nc; k++){
                    filestr << x << " " << y << " "<<k<<" " << feq[x][y][k] << std::endl;
                }
            }

            if (which_field == "f")
            {
                for (int k = 0; k < Nc; k++){
                    filestr << x << " " << y << " "<<k<<" " << f[x][y][k] << std::endl;
                }
            }
        }
        filestr << std::endl;
    }

    filestr.close();
    if (filestr.is_open())
        std::cout << "The file has not been closed!" << std::endl;
}

inline void output_fields(int step_time)
{
    if ((step_time < 15000   && step_time % 1000   == 0) ||
        (step_time < 100000  && step_time % 10000  == 0) ||
        (step_time >= 100000 && step_time % 100000 == 0) )
    {
        output_field(step_time, "u");
        output_field(step_time, "v");
        output_field(step_time, "film_thickness");
        // output_field(step_time, "d_film_pressure");
        // output_field(step_time, "film_pressure");
        // output_field(step_time, "f_film_x");
        // output_field(step_time, "f_film_y");
        // output_field(step_time, "f_fric_x");
        // output_field(step_time, "f_fric_y");
        // output_field(step_time, "f_total_x");
        // output_field(step_time, "f_total_y");

        // output_field(step_time, "feq");
        // output_evolution();
    }


    // if (step_time % 20000 == 0)
    // {
    //     output_field(step_time, "u");
    //     output_field(step_time, "v");
    //     output_field(step_time, "film_thickness");
    //     // output_field(step_time, "d_film_pressure");
    //     // output_field(step_time, "film_pressure");
    //     // output_field(step_time, "f_film_x");
    //     // output_field(step_time, "f_film_y");
    //     // output_field(step_time, "f_fric_x");
    //     // output_field(step_time, "f_fric_y");
    //     // output_field(step_time, "f_total_x");
    //     // output_field(step_time, "f_total_y");
    //
    //     // output_field(step_time, "feq");
    //     // output_evolution();
    // }
}

inline void output_max_height(int step_time) {
    std::ofstream height_f;
    std::string fileheight = "h_max.txt";

    height_f.open(fileheight, std::ios::app);
    height_f << step_time << "  " << thickness_max << endl;
}

inline void output_min_height(int step_time) {
    std::ofstream height_f;
    std::string fileheight = "h_min.txt";

    height_f.open(fileheight, std::ios::app);
    height_f << step_time << "  " << thickness_min << endl;
}

inline void output_dh(int step_time) {
    std::ofstream height_f;
    std::string fileheight = "dh.txt";

    height_f.open(fileheight, std::ios::app);
    height_f << step_time << "  " << thickness_max - thickness_min << endl;
}

inline void output_energy(int step_time) {
    std::ofstream height_f;
    std::string fileheight = "E.txt";

    height_f.open(fileheight, std::ios::app);
    height_f << step_time << "  " << total_energy << endl;
}


inline void output_total_mass(int step_time) {
    std::ofstream height_f;
    std::string fileheight = "mass.txt";

    height_f.open(fileheight, std::ios::app);
    height_f << step_time << "  " << thickness_integral << endl;
}

inline void output_radius_and_h_and_theta(int step_time)
{
    std::ofstream theta_f;
    std::string fileNameVelInt = "theta.txt";

    theta_f.open(fileNameVelInt, std::ios::app);
    theta_f << step_time << "  " << theta_current << endl;

    std::ofstream radius_f;
    std::string fileNameMeanRho = "radius.txt";

    radius_f.open(fileNameMeanRho, std::ios::app);
    radius_f << step_time << "  " << spreading_radius << endl;

    output_max_height(step_time);
}

inline void compute_thickness_integral(){
    thickness_integral = 0.0;
    for (int i = 0; i <= Nx - 1; i++){
        for (int j = 0; j <= Ny - 1; j++){
            thickness_integral += film_thickness[i][j];
        }
    }
    cout<<"mass: " <<thickness_integral<<endl;
}

inline void output_thickness_horizontal_slice(int step_time, int y)
{
    std::ofstream filestr;

    std::string fileName = "res/horizontal_slice_thickness_" + std::to_string(y) + '_' + std::to_string(step_time) + ".txt";

    filestr.open(fileName);
    for (int x = 0; x <= Nx - 1; x++)
    {
        filestr << film_thickness[x][y] << endl;
    }
    filestr.close();
}

#endif //THIN_FILM_LBM_OUTPUT_H