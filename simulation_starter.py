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

    #config["method_type"] = input("Enter method type\n")

    dt = config["dt"] = float(input("Enter dt\n"))
    time = config["time"] = float(input("Enter total time\n"))
    config["N"] = int(time // dt)


    f = open('config.json', 'w')
    json.dump(config, f)
    f.close()
 
def afc():
    global colours
    global ax

    f = open('config.json', 'r')
    t = f.read()
    config = json.loads(t)
    f.close()

    N = int(70 // config["dt"])

    w0 = config["w0"]
    
    freqs = np.linspace(0.1 * w0, 2 * w0, 300)    
    
    ampls = []

    for w in freqs:

        config["w"] = w

        f = open('config.json', 'w')
        json.dump(config, f)
        f.close()

        os.system("./a.out")
        f = open(config["output_file"], 'r')
        t = f.read()
        f.close()

        a = t.split()

        x_max = max([float(a[i]) for i in range(N, config["N"] - 100)])
        ampls.append(x_max)
        
    
    ax.plot(freqs, ampls, color = next(colours), label=f'{config["method_type"]}, dt = {config["dt"]}')
    
    ax.set(xlabel= 'w', ylabel='x_max')
    ax.legend()     
        
   
def activate():
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
    #config = {"output_file" : "xu.txt"}

    #config["method_type"] = input("Enter method type\n")
    #order = config["order"] = int(input("Enter order of the equation\n"))
    #dimension = config["dimension"] = int(input("Enter dimension of the task\n"))
    #config["acc_type"] = input("Enter accuracy type\n")

    #for i in range(0, order):
    #    for j in range(0, dimension):
    #        config[f"y_{i}_{j}"] = float(input(f"Enter {j} component of {i}th derivative\n"))

    #arg_names = []
    #arg = input("Enter name of additional arguement(if none enter '')\n")
    #while arg != "":
    #    arg_names.append(arg)
    #    arg = input("\n")
    #config["arg_names"] = arg_names

    #equation = config["equation"] = input("Enter differential equation for last derivative using previous names\n")

    #sutra = ""    

    #sutra += f'''#define task_dimensions {config["dimension"]}\n#define equation_order {config["order"]}\n'''

    #equation = f'\ty_d.v[{config["order"] - 1}][0] = ' + re.sub(r'y_(\d)_(\d)',r'y.v[\1][\2]', equation) + ';'

    #sutra += equation



    #f = open('config.json', 'w')
    #json.dump(config, f)
    #f.close()

    os.system("g++ math_pendulum.cpp -O3")
 
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


actions = ["running = False", "configure()", "configure_all()", "activate()", "afc()", "show()"]
running = True

while running:
    inp = int(input("1 - configure, 2 - configure from the start, 3 - ACTIVATE, 4 - AFC , 5 - show graphs, 0 - shut down\n"))
    exec(actions[inp])



