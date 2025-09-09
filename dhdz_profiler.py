import numpy as np
import matplotlib.pyplot as plt

def load_slice(filename, x_max=100):
    """Чтение файла и получение среза по середине сетки по y, обрезка по x"""
    data = np.loadtxt(filename)
    x, y, h = data[:, 0], data[:, 1], data[:, 2]

    # середина по y
    y_unique = np.unique(y)
    y0 = y_unique[len(y_unique)//2]

    # маска
    mask = (y == y0) & (x <= x_max)
    x_slice = x[mask]
    h_slice = h[mask]

    # сортировка по x
    order = np.argsort(x_slice)
    return x_slice[order], h_slice[order], y0

# список файлов
files = [
    "square_drop/08-09-2025_14-05-45/res/film_thickness_5000000.txt",
    "r_10/res/film_thickness_1500000.txt",
    "r_100/res/film_thickness_1500000.txt"
]

labels = [r"$S=10^4$", r"$S=10^2$", r"$S=25 \cdot 10^2$"]

plt.figure(figsize=(7, 5))

# строим профиль
for filename, label in zip(files, labels):
    x_slice, h_slice, y0 = load_slice(filename, x_max=100)
    plt.plot(x_slice, h_slice, '-o', label=label)

plt.xlabel("X")
plt.ylabel("Высота (Z)")
plt.title(f"Срез пузыря при y={y0}, x ≤ 100")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()

# график производных
plt.figure(figsize=(7, 5))
for filename, label in zip(files, labels):
    x_slice, h_slice, y0 = load_slice(filename, x_max=100)
    dhdx = np.gradient(h_slice, x_slice)  # численная производная
    plt.plot(x_slice, dhdx, '-o', label=label)

plt.xlabel("X")
plt.ylabel("dh/dx")
plt.title(f"Производные профиля при y={y0}, x ≤ 100")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
