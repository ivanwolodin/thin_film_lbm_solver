import pandas as pd
import matplotlib.pyplot as plt

# читаем три файла
h_min = pd.read_csv("h_min.txt", delim_whitespace=True, header=None, names=["step", "value"])
h_max = pd.read_csv("h_max.txt", delim_whitespace=True, header=None, names=["step", "value"])
dh = pd.read_csv("dh.txt", delim_whitespace=True, header=None, names=["step", "value"])

# строим графики
plt.figure(figsize=(10, 6))

plt.plot(h_min["step"], h_min["value"], label="h_min")
plt.plot(h_max["step"], h_max["value"], label="h_max")
plt.plot(dh["step"], dh["value"], label="dh")

plt.xlabel("Шаг времени")
plt.ylabel("Значение")
plt.title("Эволюция h_min, h_max и dh")
plt.legend()
plt.grid(True)

plt.show()

