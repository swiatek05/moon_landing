import os

import pandas as pd
import matplotlib .pyplot as plt

df=pd.read_csv('results/results.csv')
df = df.apply(pd.to_numeric, errors='coerce')

fig,axes=plt.subplots(1,2,figsize=(12,4))

df.plot(x="time",
        y="height",
        kind="scatter",
        ax=axes[0],
        title="Wykres wysokości w funkcji czasu",
        xlabel="Czas [s]",
        ylabel="Wysokość [m]",
        s=1,
        grid=True)
df.plot(x="time",
        y="velocity",
        kind="scatter",
        ax=axes[1],
        title="Wykres prędkości w funkcji czasu",
        xlabel="Czas [s]",
        ylabel="Prędkość [m/s]",
        s=1,
        grid=True)
plt.tight_layout()

os.makedirs("results",exist_ok=True)

plt.savefig("results/charts.png")









