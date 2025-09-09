# import numpy as np
# import matplotlib.pyplot as plt
#
# # читаем данные
# data = np.loadtxt("res/film_thickness_1000000.txt")
# x = data[:, 0]
# y = data[:, 1]
# h = data[:, 2]
#
# # хотим срез по y = y0 (посередине сетки)
# y_unique = np.unique(y)  # берёт все уникальные значения координаты y (так как в файле каждая строка — отдельный узел сетки, а значения y y там повторяются).
# y0 = y_unique[len(y_unique)//2]   # середина
# mask = (y == y0)  # Создаётся логическая маска: True для тех точек, где координата y совпадает с выбранным y
#
# # Теперь берём координаты x и высоты h только для этой линии Получаем одномерные массивы, которые описывают профиль пузыря в плоскости XZ
# x_slice = x[mask]
# h_slice = h[mask]
#
# # сортировка по x
# # Так как данные из файла могут быть записаны в любом порядке, здесь мы их сортируем по возрастанию x, чтобы линия была непрерывной
# order = np.argsort(x_slice)
# x_slice = x_slice[order]
# h_slice = h_slice[order]
#
# # строим профиль
# plt.figure(figsize=(6, 4))
# plt.plot(x_slice, h_slice, 'o-')
# plt.xlabel("X")
# plt.ylabel("Высота (Z)")
# plt.title(f"Срез пузыря при y={y0}")
# plt.grid(True)
# plt.show()



import numpy as np
import matplotlib.pyplot as plt

def load_slice(filename):
    """Считывает файл и возвращает (x_slice, h_slice) для среза по середине y"""
    data = np.loadtxt(filename)
    x = data[:, 0]
    y = data[:, 1]
    h = data[:, 2]

    # уникальные y и середина
    y_unique = np.unique(y)
    y0 = y_unique[len(y_unique)//2]
    mask = (y == y0)

    x_slice = x[mask]
    h_slice = h[mask]

    # сортировка по x
    order = np.argsort(x_slice)
    return x_slice[order], h_slice[order], y0

# пути к файлам
file1 = "r_100/res/film_thickness_1500000.txt"
file2 = "r_10/res/film_thickness_1500000.txt"

# загрузка срезов
x1, h1, y0_1 = load_slice(file1)
x2, h2, y0_2 = load_slice(file2)

# строим оба профиля
plt.figure(figsize=(7,5))
plt.plot(x1, h1, 'o-', label="Пузырь 1 (h≈3.5)")
plt.plot(x2, h2, 's-', label="Пузырь 2 (h≈2.7)")
plt.xlabel("X")
plt.ylabel("Высота (Z)")
plt.title(f"Срез пузыря при y={y0_1}")
plt.grid(True)
plt.legend()
plt.show()
