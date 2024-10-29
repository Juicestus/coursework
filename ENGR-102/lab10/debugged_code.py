# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 10
# Date:         22 Oct 2024
#


def interpolate(x1, y1, x2, y2, x):
    '''This function interpolates between two points'''
    slope = (y2 - y1) / (x2 - x1)
    y = slope * (x - x1) + y1
    return y 

##### 5 MPa Data #####
# temperature in degrees C
temp5 = [0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220, 240, 260]
# specific volume in m^3/kg
v5 = [0.0009977, 0.0009996, 0.0010057, 0.0010149, 0.0010267, 0.001041, 
      0.0010576, 0.0010769, 0.0010988, 0.001124, 0.0011531, 0.0011868, 
      0.0012268, 0.0012755]
# internal energy in kJ/kg
u5 = [0.04, 83.61, 166.92, 250.29, 333.82, 417.65, 501.91, 586.8, 672.55,
      759.47, 847.92, 938.39, 1031.6, 1128.5]
# enthalpy in kJ/kg
h5 = [5.03, 88.61, 171.95, 255.36, 338.96, 422.85, 507.19, 592.18, 
      678.04, 765.09, 853.68, 944.32, 1037.7, 1134.9]
# entropy in kJ/(kg K)
s5 = [0.0001, 0.2954, 0.5705, 0.8287, 1.0723, 1.3034, 1.5236, 1.7344, 
      1.9374, 2.1338, 2.3251, 2.5127, 2.6983, 2.8841]

##### 10 MPa Data #####
# temperature in degrees C
temp10 = [0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220, 240, 260]
# specific volume in m^3/kg
v10 = [0.0009952, 0.0009973, 0.0010035, 0.0010127, 0.0010244, 0.0010385,
       0.0010549, 0.0010738, 0.0010954, 0.0011200, 0.0011482, 0.0011809,
       0.0012192, 0.0012653]
# internal energy in kJ/kg
u10 = [0.12, 83.31, 166.33, 249.43, 332.69, 416.23, 500.18, 584.72,
       670.06, 756.48, 844.32, 934.01, 1026.2, 1121.6]
# enthalpy in kJ/kg
h10 = [10.07, 93.28, 176.37, 259.55, 342.94, 426.62, 510.73, 595.45,
       681.01, 767.68, 855.8, 945.82, 1038.3, 1134.3]
# entropy in kJ/(kg K)
s10 = [0.0003, 0.2943, 0.5685, 0.826, 1.0691, 1.2996, 1.5191, 1.7293,
       1.9316, 2.1271, 2.3174, 2.5037, 2.6876, 2.871]

##### do calculations #####
# get temperature and pressure from user
temp = float(input("Enter a temperature between 0 and 260 deg C: "))
pres = float(input("Enter a pressure between 5 and 10 MPa: "))

# loop over temperatures in list to find the two that bound
# the temperature entered by the user
for i in range(len(temp5)):
    if temp == temp5[i]:        # if equal to lower bound
        vl, vh = v5[i], v10[i]   # l for lower, h for upper
        ul, uh = u5[i], u10[i]   # 5 for 5 MPa, 10 for 10 MPa
        hl, hh = h5[i], h10[i]
        sl, sh = s5[i], s10[i]
        break
    elif temp == temp5[i + 1]:  # if equal to upper bound
        vl, vh = v5[i + 1], v10[i + 1]
        ul, uh = u5[i + 1], u10[i + 1]
        hl, hh = h5[i + 1], h10[i + 1]
        sl, sh = s5[i + 1], s10[i + 1]
        break
    elif temp < temp5[i + 1]:   # if in between bounds, interpolate
        vl = interpolate(temp5[i], v5[i], temp5[i + 1], v5[i + 1], temp)
        vh = interpolate(temp10[i], v10[i], temp10[i + 1], v10[i + 1], temp)
        ul = interpolate(temp5[i], u5[i], temp5[i + 1], u5[i + 1], temp)
        uh = interpolate(temp10[i], u10[i], temp10[i + 1], u10[i + 1], temp)
        hl = interpolate(temp5[i], h5[i], temp5[i + 1], h5[i + 1], temp)
        hh = interpolate(temp10[i], h10[i], temp10[i + 1], h10[i + 1], temp)
        sl = interpolate(temp5[i], s5[i], temp5[i + 1], s5[i + 1], temp)
        sh = interpolate(temp10[i], s10[i], temp10[i + 1], s10[i + 1], temp)
        break

# now interpolate with pressure
v = interpolate(5, vl, 10, vh, pres)
u = interpolate(5, ul, 10, uh, pres)
h = interpolate(5, hl, 10, hh, pres)
s = interpolate(5, sl, 10, sh, pres)

##### print results #####
print('Properties at {} deg C and {} MPa are:'.format(temp, pres))
print('Specific volume (m^3/kg): {:.7f}'.format(v))
print('Specific internal energy (kJ/kg): {:.2f}'.format(u))
print('Specific enthalpy (kJ/kg): {:.2f}'.format(h))
print('Specific entropy (kJ/kgK): {:.4f}'.format(s))