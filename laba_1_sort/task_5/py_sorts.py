import time
import numpy as np
import numpy.random as rnd
global f 
f = open('//home//michael//Desktop//cproj//labs//sort_lab//task_1//data1.csv', 'w')

def tocsv(arr):
    dat = [str(j) for j in arr]
    f.write(','.join(dat) + '\n')

def bubble(arr):
    l = len(arr)
    for i in range(l-1):
        for j in range(i+1, l):
            if arr[i] > arr[j]:
                arr[i], arr[j] = arr[j], arr[i]
    return arr

def insertion(arr):
    l = len(arr)
    for i in range(l):
        elem = arr[i]
        j = i
        while (j > 0 and arr[j-1] > elem):
            arr[j] = arr[j-1]
            j -= 1
        arr[j] = elem
    return arr

def selection(arr):
    l = len(arr)
    for i in range(l-1, 0, -1):
        mx = -10**8
        for j in range(i):
            if mx < arr[j]:
                mx = arr[j]
                max_i = j
        arr[i], arr[max_i] = arr[max_i],arr[i]
    return arr

for id in range(3):
    for i in range(1000, 100001, 1000):
        print(i)
        meas = 2
        arr_tocsv = []
        match id:
                case 0:
                    arr_tocsv.append('bubble')
                case 1:
                    arr_tocsv.append('insertion')
                case 2:
                    arr_tocsv.append('selection')
        arr_tocsv.append(i)
        for j in range(meas):
            arr = [int(rnd.randint(-2147483648,2147483647)) for _ in range(i)]
            start = time.time()

            match id:
                case 0:
                    bubble(arr)
                case 1:
                    insertion(arr)
                case 2:
                    selection(arr)
            end = time.time()
            t = end - start
            arr_tocsv.append(t)
        print(arr_tocsv)
        tocsv(arr_tocsv)