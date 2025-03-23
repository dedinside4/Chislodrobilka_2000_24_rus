import matplotlib.pyplot as plt
import numpy as np
import scipy.optimize as opt
import os

colors_list = ["red", "blue", "green", "yellow", "purple", "black"]

N = 70

#r_sample = [0.5]

r = -1.0001

print(r)#_sample)

y0_sample = np.linspace(0, -r, 20)

print(y0_sample)

index = 0

for y0 in y0_sample:
 #   for r in r_sample:   
    with open("input.txt", 'w') as file:
        file.write(str(r) + ' ' + str(y0) + ' ' + str(N))

    os.system("./b.out < input.txt")    

    with open("joke.txt") as file:
        data = file.read()
        info = data.split()


    n = np.array([i for i in range(1, N)])

    y = []

    for i in range(1, N):
        y.append(float(info[i-1]))

    y = np.array(y)

    plt.scatter(n, y)#, color = colors_list[index])
    index += 1    
    
plt.show()



