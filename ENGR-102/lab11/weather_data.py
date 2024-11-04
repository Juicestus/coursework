# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 11
# Date:         4 Nov 2024


# cols = [ "Date", 
# "Average Dew Point (F)", 
# "Average Temperature (F)", 
# "Average Relative Humidity (%)",
# "Average Daily Wind Speed (mph)", 
# "Maximum Temperature (F)",
# "Minimum Temperature (F)",
# "Precipitation (in)"]

data = []

maxtemp = 0
mintemp = 10000000

with open("WeatherDataCLL.csv") as f:
    cols = f.readline().strip().split(",")
    data = [ [] for _ in cols ]
    line = f.readline()
    while line != '':
        for i, v in enumerate(line.strip().split(",")):
            if i == 5 and v != '': maxtemp = max(maxtemp, float(v))
            if i == 6 and v != '': mintemp = min(mintemp, float(v))
            if v == '': v = 0
            data[i].append(float(v) if i > 0 else v)
        line = f.readline()
        
# print(data)
print(f"10-year maximum temperature: {round(maxtemp)} F")
print(f"10-year minimum temperature: {round(mintemp)} F")

month = input("Please enter a month: ")
# July
year = input("Please enter a year: ")
# 2024

print(f"For {month} {year}:")

month = {
    "January": '01',
    "February": '02',
    "March": '03',
    "April": '04',
    "May": '05',
    "June": '06',
    "July": '07',
    "August": '08',
    "September": '09',
    "October": '10',
    "November": '11',
    "December": '12'
}[month]

# filter for specified month
spec_data = [ [] for _ in cols ]
for i in range(len(data[0])):
    if data[0][i].startswith(f"{year}-{month}"):
        for j in range(len(cols)):
            spec_data[j].append(data[j][i])
            
data = spec_data

mean_avg_temp = sum(data[2]) / len(data[2])
print(f"Mean average daily temperature: {mean_avg_temp:.1f} F")

mean_avg_dewpt = sum(data[1]) / len(data[1])
print(f"Mean average daily dew point: {mean_avg_dewpt:.1f} F")

mean_rel_hum = sum(data[3]) / len(data[3])
print(f"Mean relative humidity: {mean_rel_hum:.1f}%")

mean_daily_windspeed = sum(data[4]) / len(data[4])
print(f"Mean daily wind speed: {mean_daily_windspeed:.2f} mph")

n_precip = sum([ int(p > 0) for p in data[7] ])
p_precip = (n_precip / len(data[7])) * 100
print(f"Percentage of days with precipitation: {p_precip:.1f}%")
