import matplotlib.pyplot as plt
from matplotlib.ticker import LinearLocator
import numpy as np
from numpy.polynomial import Polynomial

with open('//home//michael//Desktop//cproj//labs//1_sort_lab//task_0//data0.csv', 'r') as f:
    d_sqr = dict()
    for line in f:
        dat = line.split(',')
        name = dat[0]
        if name not in d_sqr:
            d_sqr[name] = [[int(dat[1]),sum(float(dat[i]) for i in range(2,len(dat)-1,1))/len(range(2,len(dat)-1,1))]]
        else:
            d_sqr[name].append([int(dat[1]),sum(float(dat[i]) for i in range(2,len(dat)-1,1))/len(range(2,len(dat)-1,1))])

with open('//home//michael//Desktop//cproj//labs//1_sort_lab//task_2//data02.csv', 'r') as f:
    d_log = dict()
    for line in f:
        dat = line.split(',')
        name = dat[0]
        if name not in d_log:
            d_log[name] = [[int(dat[1]),sum(float(dat[i]) for i in range(2,len(dat)-1,1))/len(range(2,len(dat)-1,1))]]
        else:
            d_log[name].append([int(dat[1]),sum(float(dat[i]) for i in range(2,len(dat)-1,1))/len(range(2,len(dat)-1,1))])


name_list = list(d_sqr.keys()) + list(d_log.keys())
fig,axs = plt.subplots(3,1)
for i in range(3):
    x_temp, y_temp = [], [] 
    dat_list = d_sqr[name_list[i]]
    for j in range(len(dat_list)):
        x_temp.append(dat_list[j][0])
        y_temp.append(dat_list[j][1])
    #approximation = Polynomial.fit(x_temp, y_temp, 1)
    sqr_app = Polynomial.fit(x_temp, y_temp, 2)
    #axs[0].scatter(x_temp, y_temp, s=5, c='r')
    axs[0].plot(x_temp,sqr_app(x_temp))
    axs[0].yaxis.set_major_locator(LinearLocator(4))
    
    axs[2].plot(x_temp,sqr_app(x_temp))
    axs[2].yaxis.set_major_locator(LinearLocator(4))
    axs[2].set(xlim = (0,100000),ylim = (0,22))

for i in range(3):
    x_temp, y_temp = [], [] 
    dat_list = d_log[name_list[i+3]]
    for j in range(len(dat_list)):
        x_temp.append(dat_list[j][0])
        y_temp.append(dat_list[j][1])
    #approximation = Polynomial.fit(x_temp, y_temp, 1)
    log_app = Polynomial.fit(x_temp, y_temp, 2)
    #axs[1].scatter(x_temp, y_temp, s=5, c='r')
    axs[1].plot(x_temp,log_app(x_temp))
    axs[1].yaxis.set_major_locator(LinearLocator(4))
    axs[1].set_xlim(xmin = 0, xmax =100000)
    axs[1].set_ylim(ymin = 0, ymax = 0.08)
    axs[2].plot(x_temp,log_app(x_temp))
    axs[0].grid()
axs[1].grid()
axs[2].grid()

fig.suptitle('Сравнение сортировок за n^2 и nlogn')
for i in range(3):
    axs[i].relim()
    axs[i].autoscale_view()
plt.show()