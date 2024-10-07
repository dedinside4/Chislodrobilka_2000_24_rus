import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation
import os
import json

dt  = 0.1
N = 1423

u0 = 0
x0 = 1
w = 1.3

method_type = "rungecat"
out_file = "xu.txt"
order = 2

config = eval(f'{{"dt" : {dt}, "N" : {N}, "order" : {order}, "x_0" : {x0}, "u_0" : {u0}, "w" : {w}, "type" : "{method_type}", "output_file" : "{out_file}"}}')

f = open('config.json', 'w')
json.dump(config, f)
f.close()



os.system("g++ simulation_methods.cpp")
os.system("./a.out")
f = open(out_file, 'r')
t = f.read()
f.close()

a = t.split()


x = [x0]
t = [0]

for i in range(0, N - 1):
    x.append(float(a[i]))
    t.append(t[i] + dt)
x_1 = np.array(x)
'''
x = [x0]
for i in range(N - 1, 2 * N - 2):
    x.append(float(a[i]))
x_2 = np.array(x)

x = [x0]
for i in range(2 * N - 2, 3 * N - 3):
    x.append(float(a[i]))
x_3 = np.array(x)
'''

t = np.array(t)

y = np.cos(w * t)

dx_1 = x_1 - y

#dx_2 = x_2 - y

#dx_3 = x_3 - y

fig, ax = plt.subplots()

line0 = ax.plot(t, y, color ='yellow')[0] 
line1 = ax.plot(t, x_1, color ='tab:red')[0]
#line2 = ax.plot(t, x_2, color ='tab:blue')[0]
#line3 = ax.plot(t, x_3, color ='tab:green')[0]
ax.set(xlabel='t', ylabel='x')
ax.legend()


plt.show()
