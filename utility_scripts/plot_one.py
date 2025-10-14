import pandas as pd
import matplotlib.pyplot as plt

# читаем три файла
step = 1000
ux_profile = pd.read_csv(f"res/ux_profile_{step}.txt", delim_whitespace=True, header=None, names=["step", "value"])

# строим графики
plt.figure(figsize=(10, 6))

plt.plot(ux_profile["step"], ux_profile["value"], label="h_min")

# plt.xlabel("Шаг времени")
# plt.ylabel("Значение")
# plt.title("Эволюция h_min, h_max и dh")
plt.legend()
plt.grid(True)

plt.show()

