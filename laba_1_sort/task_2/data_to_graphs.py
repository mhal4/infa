import matplotlib.pyplot as plt
from matplotlib.ticker import LinearLocator
import numpy as np
from numpy.polynomial import Polynomial

with open('//home//michael//Desktop//cproj//labs//1_sort_lab//task_2//data02.csv', 'r') as f:
    d = dict()
    for line in f:
        dat = line.split(',')
        name = dat[0]
        if name not in d:
            d[name] = [[int(dat[1]),sum(float(dat[i]) for i in range(2,len(dat)-1,1))/len(range(2,len(dat)-1,1))]]
        else:
            d[name].append([int(dat[1]),sum(float(dat[i]) for i in range(2,len(dat)-1,1))/len(range(2,len(dat)-1,1))])
    
name_list = list(d.keys())
fig,axs = plt.subplots(3,2)
for i in range(3):
    x_temp, y_temp = [], [] 
    yt=[]
    dat_list = d[name_list[i]]
    for j in range(len(dat_list)):
        yt.append(dat_list[j][1]/(dat_list[j][0] * np.log(dat_list[j][0])))
        x_temp.append(dat_list[j][0])
        y_temp.append(dat_list[j][1])
    approximation = Polynomial.fit(x_temp, y_temp, 1)
    log_app = Polynomial.fit(x_temp, y_temp, 2)
    axs[i][0].scatter(x_temp, y_temp, s=5, c='r')
    axs[i][0].plot(x_temp,log_app(x_temp))
    for k in range(2): 
        axs[i][k].yaxis.set_major_locator(LinearLocator(4))
        axs[i][0].set(xlim = (0,100000), ylim=(0,max(y_temp)))
        axs[i][1].set(xlim = (0,100000), ylim=(0,max(yt)))
        axs[i][k].grid()
    axs[i][1].plot(x_temp, yt)

fig.suptitle('Сортировки на плюсах O(n logn)')
for i in range(3):
    for j in range(2):
        axs[i][j].set_title(label=name_list[i], )
        axs[i][j].relim()
        axs[i][j].autoscale_view()
plt.show()