import numpy as np
import matplotlib.pyplot as plt

step = 1000
field = 'film_thickness'
#
# field = 'u'
# field = 'v'

filename = f"res/{field}_{step}.txt"
# filename = f"bubble_height.txt"
N = 200  # размер сетки (должен совпадать с тем, что в C++ коде)
L = N  # физический размер области

# Считываем данные
data = np.loadtxt(filename)
i_vals = data[:, 0].astype(int)
j_vals = data[:, 1].astype(int)
h_vals = data[:, 2]

# Формируем массив толщины
film_thickness = np.zeros((N, N))
for k in range(len(h_vals)):
    i = i_vals[k]
    j = j_vals[k]
    film_thickness[i, j] = h_vals[k]

# Создаем координатные сетки
x = np.linspace(0, L, N)
y = np.linspace(0, L, N)

# 2D визуализация с цветом
plt.figure(figsize=(6, 5))
plt.imshow(film_thickness.T, origin='lower',
           extent=[x.min(), x.max(), y.min(), y.max()],
           cmap='viridis', interpolation='nearest')
plt.colorbar(label=f"{field}")
plt.xlabel("X")
plt.ylabel("Y")
plt.title(f"{field}_{step}")

plt.savefig(f'{step}_{field}_2d.png')
plt.close()
