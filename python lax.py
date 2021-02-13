# setting jupyter notebook to display animation
#matplotlib notebook

# importing relevant modules & packages
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
plt.rcParams['axes.linewidth'] = 1

dataset = pd.read_excel('BurgersNumerical.xlsx', header=None)
dataset1 = pd.read_excel('BurgersAnalytical.xlsx', header=None)
print(dataset[0])

x = np.linspace(0, 1, 10201)
x1 = np.linspace(0, 1, 10100)

ig, (ax) = plt.subplots(1, figsize=(10,6))

#ax.plot(x, dataset, color = 'blue', linewidth = 1.5, linestyle = 'dashed', marker = 'o', markersize = 5)
ax.plot(x1, dataset, color = 'blue', marker = 'o')
ax.plot(x, dataset1, color = 'orange')
ax.set_xlim(0.01, 0.02)
#ax.set_ylim(-1,0.75)
#plt.yticks([-1, -0.5, 0, 0.5, 0.75], fontsize=15)
#plt.gca().xaxis.set_major_locator(MaxNLocator(prune='lower'))
#ax.tick_params(axis='x', pad=20)
plt.xticks(fontsize=15)
ax.set_title("Burgers 1D equation", fontsize=20)
ax.set_xlabel("time t(s)", fontsize=18)
ax.set_ylabel("velocity u", fontsize=18)
plt.show()


