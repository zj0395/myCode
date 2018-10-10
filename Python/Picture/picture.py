#!/usr/bin/env python
# coding=utf-8
import matplotlib.pyplot as plt
import numpy as np

DATAFILE = "SN_y_tot_V2.0.txt"

data = np.loadtxt(DATAFILE)
year, total, deviation, number = data[-10:,0], data[-10:,1], data[-10:,2], data[-10:,3]
year = year.astype(int)
number = number.astype(int)
allDatas = [year, total, deviation, number]
strs = ['Year', 'Total', 'Deviation', 'Number']
for i in range(3):
    plt.subplot(2, 2, i+1)
    plt.plot( year, allDatas[i+1] )
    plt.ylabel(strs[i+1])
plt.show()
