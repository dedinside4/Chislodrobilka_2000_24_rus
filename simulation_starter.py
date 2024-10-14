import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation
import os
import json

def get_results(config):      
    f = open('config.json', 'w')
    json.dump(config, f)
    f.close()



    os.system("g++ math_pendulum.cpp -O2")
    os.system("./a.out")
    f = open(config["output_file"], 'r')
    t = f.read()
    f.close()


    a = t.split()


    x = [config["x_0"]]
    y = [config["y_0"]]
    t = [0]

    for i in range(0, len(a) // config["dimension"]):
        x.append(float(a[i * config["dimension"]]))
        y.append(float(a[i * config["dimension"] + 1]))
        t.append(t[i] + config["dt"])
    x = np.array(x) 
    y = np.array(y)
    t = np.array(t)

    return x, y, t

dt  = 0.005
time = 40

N = int(time // dt)

ux_0 = 0
uy_0 = 0

x_0 = 4
y_0 = -3

l = 5
g = 982 * l /2.3
k = 100000

method_type = "rungecutta"
out_file = "xu.txt"
order = 2
dimension = 2

config = eval(f'{{"dt" : {dt}, "N" : {N}, "order" : {order}, "dimension" : {dimension}, "x_0" : {x_0}, "y_0" : {y_0}, "ux_0" : {ux_0}, "uy_0" : {uy_0}, "g" : {g}, "l" : {l}, "k" : {k}, "type" : "{method_type}", "output_file" : "{out_file}"}}')

#x_t = []
#y_t = []

x_1, y_1, t_1 = get_results(config)

#config["dt"] = 0.2
#config["N"] = time // config["dt"]

#config["type"] = "euler"

#x_2, y_2, t_2= get_results(config)

#config["type"] = "heun"

#x_3, y_3, t_3 = get_results(config)

#y = x0 * np.cos(np.sqrt(l / g) * t)

fig, ax = plt.subplots()

x = np.linspace(-l, l, 1000)
y = -np.sqrt(l**2 - x**2)

line0 = ax.plot(x, y, color ='yellow')[0] 

#graph_1 = ax.scatter(x_t, y_t)

pen1 = ax.scatter(x_1[0], y_1[0], color ='tab:red')
#pen2 = ax.scatter(x_2[0], y_2[0], color ='tab:blue')
#pen3 = ax.scatter(x_3[0], y_3[0], color ='tab:green')

ax.set(xlim=[-2*l, 2*l], ylim=[-2*l, 2*l], xlabel= 'x', ylabel='y')

#ax.set(xlabel= 'N', ylabel='time, s')

ax.legend()


def update(iteration):
    # for each frame, update the data stored on each artist.

    frame = int(iteration * delay / dt / 1000)

    # update the line plot:
    pen1.set_offsets([x_1[frame],y_1[frame]])
    #pen2.set_offsets([x_2[frame],y_2[frame]])
    #pen3.set_offsets([x_3[frame],y_3[frame]])

    return 

animation_time = 40

delay = 5

iterations = animation_time * 1000 // delay - 3

ani = animation.FuncAnimation(fig=fig, func=update, frames=iterations, interval=delay, repeat_delay=4000)
plt.show()
