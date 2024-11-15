# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 12
# Date:         11 Nov 2024

import numpy as np
import matplotlib.pyplot as plt
from datetime import date

# cols = [ "Date", 
# "Average Dew Point (F)", 
# "Average Temperature (F)", 
# "Average Relative Humidity (%)",
# "Average Daily Wind Speed (mph)", 
# "Maximum Temperature (F)",
# "Minimum Temperature (F)",
# "Precipitation (in)"]

data = []

def int2date(s):
    p = s.split('-')
    return (date(int(p[0]), int(p[1]), int(p[2])) - date(1970, 1, 1)).days

monthinfo = {}

with open("WeatherDataCLL.csv") as f:
    cols = f.readline().strip().split(",")
    data = [ [] for _ in cols ]
    line = f.readline()
    while line != '':
        p = line.strip().split(",") # split up the line
        
        month_id = p[0][5:7] # first 7 digits of date is yyyy-mm which is the month id 
        if month_id not in monthinfo:
            monthinfo[month_id] = {} # sub dictionary which has temp and wind
            monthinfo[month_id]['avg_temp'] = []
            monthinfo[month_id]['precip'] = []
        if p[2] != '':
            monthinfo[month_id]['avg_temp'].append(float(p[2]))
        if p[7] != '':
            monthinfo[month_id]['precip'].append(float(p[7]))

        # construct data double array
        for i, v in enumerate(p):
            if v == '': v = 0
            data[i].append(float(v) if i > 0 else int2date(v))
        line = f.readline()
        
# plot 1

fig, ax1 = plt.subplots()
color = 'tab:red'
ax1.set_xlabel('date')
ax1.set_ylabel('Average Temperature, F')
ax1.plot(data[0], data[2], color=color)
ax1.tick_params(axis='y', labelcolor=color)
ax2 = ax1.twinx()  
color = 'tab:blue'
ax2.set_ylabel('Average Wind Speed, mph')
ax2.plot(data[0], data[4], color=color)
ax2.tick_params(axis='y', labelcolor=color)
fig.tight_layout() 
plt.show()

# plot 2

plt.hist(data[4], bins=24, color='green', lw=1, edgecolor='black')
plt.show()

# plot 3

plt.scatter(data[1], data[3], c ="black", s=2)
ax1.set_xlabel('Average Dew Point (F)')
ax1.set_ylabel('Average Relative Humidity (%)')
plt.show()

# plot 4

months = []
avg_temps = []
max_temps = []
min_temps = []
avg_precip = []

for i, (k, v) in enumerate(monthinfo.items()):
    months.append(i + 1)
    avg_temps.append(np.mean(v['avg_temp']))
    max_temps.append(np.max(v['avg_temp']))
    min_temps.append(np.min(v['avg_temp']))
    avg_precip.append(np.mean(v['precip']))
    
plt.figure()          
plt.bar(months, avg_temps, color='gold', width = 0.4)
plt.ylabel('Bar plot')      

plt.plot(months, max_temps, color='r', label='High T')
plt.plot(months, min_temps, color='b', label='Low T')
plt.plot(months, avg_precip, color='cyan', label='Precip')

plt.show()
