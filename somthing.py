import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation
import os
import json
import re


fig, ax = plt.subplots()

f = open('config.json', 'r')
t = f.read()
config = json.loads(t)
f.close()
l1 = config["l1"]
l2 = config["l2"]
m1 = config["m1"]
m2 = config["m2"]
g = config["g"]

def results(q_0, q_1, method):

    config["q_0"] = q_0
    config["q_1"] = q_1
    config["method_type"] = method

    f = open('config.json', 'w')
    json.dump(config, f)
    f.close()

    os.system("./a.out")
    f = open(config["output_file"], 'r')
    t = f.read()
    f.close()

    a = t.split()

    x_1 = []
    y_1 = []
    x_2 = []
    y_2 = []
    T1 = []
    T2 = []
    P = []
    t = [0]

    n = config["dimension"] * 2 

    print((len(a) - 1) // n)

    for i in range(0, (len(a) - 1) // n ):
        f1 = float(a[i * n])
        f2 = float(a[i * n + 2])
        f1d = float(a[i * n + 1])
        f2d = float(a[i * n + 3])
        x_1.append(np.sin(float(a[i * n])) * l1)
        y_1.append(-np.cos(float(a[i * n])) * l1)
        x_2.append(np.sin(float(a[i * n])) * l1 + np.sin(float(a[i * n + 2])) * l2)
        y_2.append(-np.cos(float(a[i * n])) * l1 - np.cos(float(a[i * n + 2])) * l2)

        T2.append((f1d**2 * l1**2 + f2d**2 * l2**2 + 2 * l1 * l2 * f1d * f2d * np.cos(f1 - f2)) * m2 / 2) 
        T1.append(f1d**2 * l1**2 * m1 / 2)

        P.append(- m1 * g * l1 * np.cos(f1) - m2 * g * (np.cos(f1) * l1 + np.cos(f2) * l2))

        t.append(t[i] + config["dt"] * 100)
    x_1 = np.array(x_1) 
    y_1 = np.array(y_1) 
    x_2 = np.array(x_2) 
    y_2 = np.array(y_2)
    T1 = np.array(T1)
    T2 = np.array(T2)
    P = np.array(P)
    t = np.array(t)

    return x_1, y_1, x_2, y_2#, T1, T2, P, t


x_1, y_1, x_2, y_2 = results(np.pi / 2, np.pi / 2, "rungecutta")#, T1, T2, P, t = results(1, 1, "rungecutta")

#E = T1 + T2 + P

#ax.scatter(t[:-1], T1, color = "red", label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')
#ax.scatter(t[:-1], T2, color = "yellow", label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')
#ax.scatter(t[:-1], P, color = "green", label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')
#ax.scatter(t[:-1], E, color = "blue", label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')
#plt.show()
pen_1 = ax.scatter(x_1[0], y_1[0], color ='tab:red', label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')
pen_2 = ax.scatter(x_2[0], y_2[0], color ='tab:red', label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')
line_1 = ax.plot(x_2[0], y_2[0], color ='tab:red', label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')[0]

x_3, y_3, x_4, y_4 = results(np.pi / 2, np.pi / 2 + 0.00001, "rungecutta")

pen_3 = ax.scatter(x_3[0], y_3[0], color ='tab:blue', label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')
pen_4 = ax.scatter(x_4[0], y_4[0], color ='tab:blue', label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')
line_2 = ax.plot(x_4[0], y_4[0], color ='tab:blue', label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')[0]

#x_5, y_5, x_6, y_6 = results(1, 1 + 0.00000001, "rungecutta")

#pen_5 = ax.scatter(x_5[0], y_5[0], color ='tab:green', label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')
#pen_6 = ax.scatter(x_6[0], y_6[0], color ='tab:green', label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')



ax.set(xlim=[-(l1 + l2), (l1 + l2)], ylim=[-(l1 + l2), (l1 + l2)], xlabel= 'x', ylabel='y')

def update(frame):
    # for each frame, update the data stored on each artist.

    cur_frame = frame * frames_factor

    # update the line plot:
    pen_1.set_offsets([x_1[cur_frame],y_1[cur_frame]])
    pen_2.set_offsets([x_2[cur_frame],y_2[cur_frame]])
    pen_3.set_offsets([x_3[cur_frame],y_3[cur_frame]])
    pen_4.set_offsets([x_4[cur_frame],y_4[cur_frame]])
    #pen_5.set_offsets([x_5[cur_frame],y_5[cur_frame]])
    #pen_6.set_offsets([x_4[cur_frame],y_6[cur_frame]])

    # update the line plot:
  
    line_1.set_xdata(x_2[:cur_frame])
    line_1.set_ydata(y_2[:cur_frame])
    line_2.set_xdata(x_4[:cur_frame])
    line_2.set_ydata(y_4[:cur_frame])

    return 


animation_time = config["time"]

delay = 15

frames_factor = int(delay / config["dt"] / 100000)

print(frames_factor)

iterations = int(animation_time * 1000 // delay)

ani = animation.FuncAnimation(fig=fig, func=update, frames=iterations, interval=delay, repeat_delay=4000)
plt.show()
