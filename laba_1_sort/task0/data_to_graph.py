import matplotlib.pyplot as plt
import numpy as np

with open('//home//michael//Desktop//cproj//labs//1_sort_lab//task_0//data0.csv', 'r') as f:
    d = dict()
    for line in f:
        dat = line.split(',')
        name = dat[0]
        if name not in d:
            d[name] = [[int(dat[1]),sum(float(dat[i]) for i in range(2,len(dat)-1,1))/len(range(2,len(dat)-1,1))]]
        else:
            d[name].append([int(dat[1]),sum(float(dat[i]) for i in range(2,len(dat)-1,1))/len(range(2,len(dat)-1,1))])
    
name_list = list(d.keys())
yt=[]
fig,axs = plt.subplots(1,2)
for i in range(3):
    x_temp, y_temp = [], []
    x_log, y_log = [], []
    dat_list = d[name_list[i]]
    for j in range(len(dat_list)):
        yt.append(dat_list[j][1])
        x_temp.append(dat_list[j][0])
        y_temp.append(dat_list[j][1])
        x_log.append(np.log2(dat_list[j][0]))
        y_log.append(np.log2(dat_list[j][1]))
    axs[0].plot(x_temp, y_temp, label = name_list[i])
    axs[1].plot(x_log, y_log, label = name_list[i])

fig.suptitle('Сортировки на плюсах')
yt.sort()
for j in range(2):
    axs[j].relim()
    axs[j].autoscale_view()
plt.show()