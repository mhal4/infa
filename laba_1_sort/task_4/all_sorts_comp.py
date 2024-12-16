import matplotlib.pyplot as plt
from matplotlib.ticker import LinearLocator
import numpy as np
from numpy.polynomial import Polynomial

with open('//home//michael//Desktop//cproj//labs//1_sort_lab//task_4//data5.csv', 'r') as f:
    d = dict()
    for line in f:
        dat = line.split(',')
        name = dat[0]
        if name not in d:
            d[name] = dict()
            d[name][dat[1]] = [[dat[i] for i in range(2,5)]]
        else:
            if dat[1] not in d[name]:
                d[name][dat[1]] = [[dat[i] for i in range(2,5)]]
            else:
                d[name][dat[1]].append([dat[i] for i in range(2,5)])

print(d.keys())

fig,axs = plt.subplots(2,3)
d_name = list(d.keys())
id = 0
for i in range(2):
    for j in range(3):
        d_norm = dict()
        name = d_name[id]
        clrs = ['red','green','blue']
        for key in d[name]:
            d_norm[key] = [sum([float(d[name][key][i][k]) for i in range(10)])/10 for k in range(3)]
        for k in range(3):
            x,y =  [int(key) for key in d_norm], [d_norm[key][k] for key in d_norm]
            appr = Polynomial.fit(x,y,2)
            axs[i][j].plot(x,appr(x), color=clrs[k])
        axs[i][j].grid()
        axs[i][j].set(xlim=(0,100000))
        axs[i][j].set_title(label=name )
        axs[i][j].relim()
        axs[i][j].autoscale_view()
        id+=1

plt.show()