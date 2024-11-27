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
l = config["l"]

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
    t = [0]

    for i in range(0, (len(a) - 1) // config["dimension"]):
        x_1.append(np.sin(float(a[i * config["dimension"]])) * l)
        y_1.append(-np.cos(float(a[i * config["dimension"]])) * l)
        x_2.append((np.sin(float(a[i * config["dimension"]])) + np.sin(float(a[i * config["dimension"] + 1]))) * l)
        y_2.append(-(np.cos(float(a[i * config["dimension"]])) + np.cos(float(a[i * config["dimension"] + 1]))) * l)
        t.append(t[i] + config["dt"])
    x_1 = np.array(x_1) 
    y_1 = np.array(y_1) 
    x_2 = np.array(x_2) 
    y_2 = np.array(y_2) 
    t = np.array(t)

    return x_1, y_1, x_2, y_2


x_1, y_1, x_2, y_2 = results(1, 1, "rungecutta")

#ax.plot(t, x, color = next(colours), label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')
pen_1 = ax.scatter(x_1[0], y_1[0], color ='tab:red', label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')
pen_2 = ax.scatter(x_2[0], y_2[0], color ='tab:red', label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')
#line_1 = ax.plot(x_2[0], y_2[0], color ='tab:red', label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')[0]

x_3, y_3, x_4, y_4 = results(1, 1, "heun")

pen_3 = ax.scatter(x_3[0], y_3[0], color ='tab:blue', label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')
pen_4 = ax.scatter(x_4[0], y_4[0], color ='tab:blue', label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')
#line_2 = ax.plot(x_4[0], y_4[0], color ='tab:blue', label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')[0]

x_5, y_5, x_6, y_6 = results(1, 1 + 0.00000001, "rungecutta")

pen_5 = ax.scatter(x_5[0], y_5[0], color ='tab:green', label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')
pen_6 = ax.scatter(x_6[0], y_6[0], color ='tab:green', label=f'{config["method_type"]}, dt = {config["dt"]}, w = {config["w"]}')



ax.set(xlim=[-2*l, 2*l], ylim=[-2*l, 2*l], xlabel= 'x', ylabel='y')

def update(frame):
    # for each frame, update the data stored on each artist.

    cur_frame = frame * frames_factor

    # update the line plot:
    pen_1.set_offsets([x_1[cur_frame],y_1[cur_frame]])
    pen_2.set_offsets([x_2[cur_frame],y_2[cur_frame]])
    pen_3.set_offsets([x_3[cur_frame],y_3[cur_frame]])
    pen_4.set_offsets([x_4[cur_frame],y_4[cur_frame]])
    pen_5.set_offsets([x_5[cur_frame],y_5[cur_frame]])
    pen_6.set_offsets([x_4[cur_frame],y_6[cur_frame]])

    # update the line plot:
  
    #line_1.set_xdata(x_2[:cur_frame])
    #line_1.set_ydata(y_2[:cur_frame])
    #line_2.set_xdata(x_4[:cur_frame])
    #line_2.set_ydata(y_4[:cur_frame])

    return 


animation_time = config["time"]

delay = 15

frames_factor = int(delay / config["dt"] / 100000)

print(frames_factor)

iterations = int(animation_time * 1000 // delay)

ani = animation.FuncAnimation(fig=fig, func=update, frames=iterations, interval=delay, repeat_delay=4000)
plt.show()
