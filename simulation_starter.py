import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation
import os
import json
import re

def configure():      
    f = open('config.json', 'r')
    t = f.read()
    config = json.loads(t)
    f.close()

    config["method_type"] = input("Enter method type\n")

    dt = config["dt"] = float(input("Enter dt\n"))
    time = config["time"] = float(input("Enter total time\n"))
    config["N"] = int(time // dt)

    arg_names = config["arg_names"]

    sutra = ""    

    for arg in arg_names:
        value = config[arg] = float(input(f"Enter value for {arg}\n"))
        sutra += "#define " + arg + f" {value}\n"

    sutra += f'''#define task_dimensions {config["dimension"]}\n#define equation_order {config["order"]}\n'''
    
    equation = config["equation"]

    equation = f'\ty_d.v[{config["order"] - 1}][0] = ' + re.sub(r'y_(\d)_(\d)',r'y.v[\1][\2]', equation) + ';'

    sutra += equation


    f = open('magic_equation.hpp', 'w')
    f.write(sutra)
    f.close()

    f = open('config.json', 'w')
    json.dump(config, f)
    f.close()

    os.system("g++ math_pendulum.cpp -O3")
    
def activate():
    print('gey')
    global colours
    global ax
    f = open('config.json', 'r')
    t = f.read()
    config = json.loads(t)
    f.close()

    os.system("./a.out")
    f = open(config["output_file"], 'r')
    t = f.read()
    f.close()

    a = t.split()

    x = [config["y_0_0"]]
    t = [0]

    for i in range(0, (len(a) - 1) // config["dimension"]):
        x.append(float(a[i * config["dimension"]]))
        t.append(t[i] + config["dt"])
    x = np.array(x) 
    t = np.array(t)
    ax.plot(t, x, color = next(colours), label=f'{config["method_type"]}, dt = {config["dt"]}')

    
def graph_colours():
    colors = ["red", "blue", "green", "yellow"]
    for i in range(0, 1000):
        yield colors[i % len(colors)]
    

def configure_all():
    config = {"output_file" : "xu.txt"}

    config["method_type"] = input("Enter method type\n")
    order = config["order"] = int(input("Enter order of the equation\n"))
    dimension = config["dimension"] = int(input("Enter dimension of the task\n"))
    config["acc_type"] = input("Enter accuracy type\n")

    for i in range(0, order):
        for j in range(0, dimension):
            config[f"y_{i}_{j}"] = float(input(f"Enter {j} component of {i}th derivative\n"))

    arg_names = []
    arg = input("Enter name of additional arguement(if none enter '')\n")
    while arg != "":
        arg_names.append(arg)
        arg = input("\n")
    config["arg_names"] = arg_names

    config["equation"] = input("Enter differential equation for last derivative using previous names\n")

    f = open('config.json', 'w')
    json.dump(config, f)
    f.close()
 
def show():
    global ax
    ax.legend()
    plt.show()
    fig, ax = plt.subplots()
   
colours = graph_colours()
fig, ax = plt.subplots()
ax.set(xlabel= 't', ylabel='x')
ax.legend()
pens = []


actions = ["running = False", "configure()", "configure_all()", "activate()", "show()"]
running = True

while running:
    inp = int(input("1 - configure, 2 - configure from the start, 3 - ACTIVATE, 4 - show graphs, 0 - shut down\n"))
    exec(actions[inp])



