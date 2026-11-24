# Thin Film LBM Solver

A C++ implementation of the Lattice Boltzmann Method (LBM) for thin-film hydrodynamics.

The project implements a numerical approach to thin-liquid-film simulations based on the methods described in the works of Stefan Zitz and co-authors.

**Note:** This is an independent C++ implementation of the algorithm. It is not a port of the `Swalbe.jl` Julia package.

## References

The implementation is based on the following publications:

1. S. Zitz, A. Scagliarini, S. Maddu, A. A. Darhuber, and J. Harting, "Lattice Boltzmann method for thin-liquid-film hydrodynamics", *Physical Review E*, **100**, 033313 (2019).

   [https://doi.org/10.1103/PhysRevE.100.033313](https://doi.org/10.1103/PhysRevE.100.033313)

2. S. Zitz, M. Zellhöfer, A. Scagliarini, and J. Harting, "Swalbe.jl: A lattice Boltzmann solver for thin film hydrodynamics", *Journal of Open Source Software*, **7**(77), 4312 (2022).

   [https://doi.org/10.21105/joss.04312](https://doi.org/10.21105/joss.04312)

## Project Structure

```text
.
├── constants.h             # Physical and numerical constants
├── controlling_params.h    # Simulation parameters
├── diff_operators.h        # Differential operators
├── forces.h                # Force calculations
├── initial_distribution.h  # Initial distribution functions
├── kernel.h                # Main computational routines
├── main.cpp                # Program entry point
├── output.h                # Output routines
├── run.sh                  # Build and run script
├── streaming_and_boundary.h
├── theta_calculation.h     # Contact angle calculations
└── utility_scripts/        # Utility scripts
```

## Running

Run the simulation using:

```bash
./run.sh <DIR>
```

Simulation parameters can be adjusted in `controlling_params.h`.