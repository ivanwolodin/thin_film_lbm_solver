from math import pi

L = 0.001  # meter
Nx = 100   # nodes

tau = 1.0
dx = 1.0
dt = 1.0

c_s2 = (1.0 / 3.0) * ((dx * dx) / (dt * dt))

nu_LBM = c_s2 * (tau - 0.5)
nu_real = 10**-6

CL = L / Nx
CT = (nu_LBM / nu_real) * (CL * CL)

print(f'CL={CL}')
print(f'CT={CT}')

# [g_real] = m/s^2
#  g_real * (CT^2)/CL = g_LBM
#

gravity_LBM = 10 * (CT * CT) / CL
print(f'gravity_LBM={gravity_LBM}')

omega_LBM = 0.05
a_LBM = 80000

omega_real = (omega_LBM/(2.0 * pi)) / CT
a_real = a_LBM*CL

A = omega_real * omega_real * a_real

print('Dimensional values:')
print(f'f={omega_real} Hz')
print(f'a={a_real} m')
print('=========================================')
print(f'A={A} m/s^2')


