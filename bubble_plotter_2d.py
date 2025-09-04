import numpy as np
import matplotlib.pyplot as plt

step = 1000
field = 'film_thickness'

filename = f"res/{field}_{step}.txt"
# filename = f"bubble_height.txt"

Nx = 100  # число узлов по X
Ny = 100  # число узлов по Y
Lx = Nx   # физический размер области по X
Ly = Ny   # физический размер области по Y

# Считываем данные
data = np.loadtxt(filename)
i_vals = data[:, 0].astype(int)
j_vals = data[:, 1].astype(int)
h_vals = data[:, 2]

# Формируем массив толщины
film_thickness = np.zeros((Nx, Ny))
for k in range(len(h_vals)):
    i = i_vals[k]
    j = j_vals[k]
    film_thickness[i, j] = h_vals[k]

# Создаем координатные сетки
x = np.linspace(0, Lx, Nx)
y = np.linspace(0, Ly, Ny)

# 2D визуализация с цветом
plt.figure(figsize=(6, 5))
plt.imshow(film_thickness.T, origin='lower',
           extent=[x.min(), x.max(), y.min(), y.max()],
           aspect=Lx/Ly,  # чтобы не искажало пропорции
           cmap='viridis', interpolation='nearest')
plt.colorbar(label=f"{field}")
plt.xlabel("X")
plt.ylabel("Y")
plt.title(f"{field}_{step}")

plt.savefig(f'{step}_{field}_2d.png')
plt.close()
