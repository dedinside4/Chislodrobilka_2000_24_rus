import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation
import os
import json

def get_results(config):      
    f = open('config.json', 'w')
    json.dump(config, f)
    f.close()

    #f = open("magic_equation_template.hpp", 'r')
    #t = f.read()
    #t = t.replace("GAMMA", str(config['gamma']))
    #t = t.replace("W", str(config['w']))
    #f.close()

    #f = open("magic_equation.hpp", 'w')
    #f.write(t)
    #f.close()

    os.system("./a.out")
    f = open(config["output_file"], 'r')
    t = f.read()
    f.close()


    a = t.split()


    x = [config["x_0"]]
    t = [0]


    for i in range(0, (len(a) - 1) // config["dimension"]):
        x.append(float(a[i * config["dimension"]]))
        t.append(t[i] + config["dt"])
    x = np.array(x) 
    t = np.array(t)

    return x, t

os.system("g++ math_pendulum.cpp -O3")

dt  = 0.001
time = 50

N = int(time // dt)

u_0 = 0
x_0 = 1


l = 0.6
g = 10

w = 4

gamma = 0.25


method_type = "heun"
out_file = "xu.txt"
order = 2
dimension = 1
acc_type = "double"

config = eval(f'{{"dt" : {dt}, "N" : {N}, "order" : {order}, "dimension" : {dimension}, "x_0" : {x_0}, "u_0" : {u_0}, "w" : {w},"gamma" : {gamma},"g" : {g}, "l" : {l}, "type" : "{method_type}", "output_file" : "{out_file}", "acc_type" : "{acc_type}"}}')

x_1, t_1 = get_results(config)


#perf_2 = []

config["dt"] = 0.03
config["N"] = int(time // 0.03)

x_2, t_2 = get_results(config)

#config["type"] = "euler"

#x_3, t_3 = get_results(config)

y = x_0 * np.exp(-gamma * t_1) * np.cos(np.sqrt(w**2 - gamma**2) * t_1) + x_0 * gamma / (np.sqrt(w**2 - gamma**2)) * np.exp(-gamma * t_1) * np.sin(np.sqrt(w**2 - gamma**2) * t_1)

x_max = []
gammas = np.linspace(0.255, 0.2555, 100)

#for gamma in gammas:
#    config['gamma'] = gamma
#    x, t = get_results(config)
#    x_max.append(max(x))

fig, ax = plt.subplots()

#time1 = ax.scatter(n, perf_1, color ='tab:red')
#time2 = ax.scatter(n, perf_2, color ='tab:blue')

#line1 = ax.plot(gammas, x_max, color ='yellow')[0]
#line2 = ax.plot(gammas, [0.5] * len(gammas), color ='black')[0]

pen1 = ax.plot(t_1, x_1, color ='tab:red')[0]
pen2 = ax.plot(t_2, x_2, color ='tab:blue')[0]
#pen3 = ax.plot(t_3, x_3, color ='tab:green')[0]
line3 = ax.plot(t_1, y, color ='black')[0]

ax.set(xlabel= 't', ylabel='x')

#ax.set(xlabel= 'N', ylabel='time, s')

ax.legend()


def update(iteration):
    # for each frame, update the data stored on each artist.

    frame = int(iteration * delay / dt / 1000)

    # update the line plot:
    pen1.set_offsets([x_1[frame], y_1[frame]])
    pen2.set_offsets([x_2[frame],y_2[frame]])
    pen3.set_offsets([x_3[frame],y_3[frame]])

    return 

animation_time = 3

delay = 5

iterations = animation_time * 1000 // delay - 3

#ani = animation.FuncAnimation(fig=fig, func=update, frames=iterations, interval=delay, repeat_delay=4000)
plt.show()
