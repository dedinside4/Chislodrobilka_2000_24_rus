import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation
import os
import json

def get_results(config):      
    f = open('config.json', 'w')
    json.dump(config, f)
    f.close()



    os.system("g++ math_pendulum.cpp")
    os.system("./a.out")
    f = open(config["output_file"], 'r')
    t = f.read()
    f.close()

    a = t.split()


    x = [x0]
    t = [0]

    for i in range(0, len(a)):
        x.append(float(a[i]))
        t.append(t[i] + dt)
    x_1 = np.array(x) 
    t = np.array(t)

    return x_1, t

dt  = 0.01
N = 50

u0 = 0
x0 = 1
w = 7.3

method_type = "rungecat"
out_file = "xu.txt"
order = 2

config = eval(f'{{"dt" : {dt}, "N" : {N}, "order" : {order}, "x_0" : {x0}, "u_0" : {u0}, "w" : {w}, "type" : "{method_type}", "output_file" : "{out_file}"}}')

x_1, t = get_results(config)

config["type"] = "heun"

x_2, t = get_results(config)

config["type"] = "euler"

x_3, t = get_results(config)

y = np.cos(w * t)

fig, ax = plt.subplots()

line0 = ax.plot(t, y, color ='yellow')[0] 
line1 = ax.plot(t, x_1, color ='tab:red')[0]
line2 = ax.plot(t, x_2, color ='tab:blue')[0]
line3 = ax.plot(t, x_3, color ='tab:green')[0]
ax.set(xlabel='t', ylabel='x')
ax.legend()


plt.show()
