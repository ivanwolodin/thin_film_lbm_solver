import pandas as pd
import matplotlib.pyplot as plt

# читаем три файла
h_max_50 = pd.read_csv("../spreading_square_droplet/r_50/h_max.txt", delim_whitespace=True, header=None, names=["step", "value"])
h_max_100 = pd.read_csv("../spreading_square_droplet/r_100/h_max.txt", delim_whitespace=True, header=None, names=["step", "value"])
h_max_10 = pd.read_csv("../spreading_square_droplet/r_10/h_max.txt", delim_whitespace=True, header=None, names=["step", "value"])

# общая временная сетка по самому длинному (h_max_50)
steps = h_max_100["step"]

# достраиваем ряды до этой сетки
h_max_10_full = h_max_10.set_index("step").reindex(steps).ffill().reset_index()
h_max_50_full = h_max_50.set_index("step").reindex(steps).ffill().reset_index()
h_max_100_full = h_max_100  # тут и так полная сетка

# строим графики
plt.figure(figsize=(10, 6))

plt.plot(h_max_10_full["step"], h_max_10_full["value"], label=r"$h_{S=100}$", linewidth=4.5)
plt.plot(h_max_50_full["step"], h_max_50_full["value"], label=r"$h_{S=2500}$", linewidth=4.5)
plt.plot(h_max_100_full["step"], h_max_100_full["value"], label=r"$h_{S=10000}$", linewidth=4.5)

plt.xlabel("Шаг времени")
plt.ylabel("Значение")
plt.title(r"Эволюция $h_{max}$ при разной начальной площади основания")
plt.legend()
plt.grid(True)

plt.show()
