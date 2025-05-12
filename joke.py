import matplotlib.pyplot as plt
import numpy as np
import scipy.optimize as opt
import os

colors_list = ["red", "blue", "green", "yellow", "purple", "black"]

N = 1000

#r_sample = [0.5]

r_sample = np.linspace(0, 4, 40000)

print(r_sample)

y0 = 0.25 * max(r_sample)#np.linspace(0, 0.5, 10)

x0_sample = [0.5]

index = 0


for x0 in x0_sample:
    xn = []
    rs = []
    for r in r_sample: 
        x = x0  
        for i in range(1, 9 * N // 10):
            x = r * x * (1 - x)
        for i in range(9 * N // 10 , N):
            x = r * x * (1 - x)
            xn.append(x)  
            rs.append(r) 
        #n = np.array([i for i in range(1, N)])

        #x = []

        #x = np.array(x)
plt.scatter(rs, xn, color = colors_list[index])
plt.show()




'''
#for y0 in y0_sample:
for r in r_sample:   
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

    plt.scatter(n, y, color = colors_list[index])
    index += 1    

    
    plt.show()

'''

