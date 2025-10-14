import numpy as np
import matplotlib.pyplot as plt

# Параметры
step = 1000
filename = f"res/film_thickness_{step}.txt"
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
X, Y = np.meshgrid(x, y)

# Визуализация
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, film_thickness.T, cmap='viridis')  # транспонируем для правильной ориентации
ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Thickness")
# plt.show()

plt.savefig(f'{step}_bubble_3d.png')
plt.close()