import numpy as np
import matplotlib.pyplot as plt

def load_slice(filename):
    """Чтение файла и получение среза по середине сетки по y"""
    data = np.loadtxt(filename)
    x, y, h = data[:, 0], data[:, 1], data[:, 2]

    # середина по y
    y_unique = np.unique(y)
    y0 = y_unique[len(y_unique)//2]

    # маска
    mask = (y == y0)
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

# строим все на одном графике
for filename, label in zip(files, labels):
    x_slice, h_slice, y0 = load_slice(filename)
    plt.plot(x_slice, h_slice, '-o', label=label)

plt.xlabel("X")
plt.ylabel("Высота (Z)")
plt.title(f"Срез пузыря при y={y0}")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
