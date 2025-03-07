from math import factorial
from matplotlib import pyplot as plt
import numpy as np
import scipy.optimize as opt

def C(N, k):
    return factorial(N) / factorial(k) / factorial(N - k)

def anal(K, N):

    q = 0

    for i in range(1, K):
        q += (-1)**(i + 1) * C(K, i) * ((K - i))**N

    p = K**N - q

    return q

def true_anal(N, *k):
    K = 3
    f = 1
    for i in range(0, K):
        f *= N - i
    f *= 1
    return f 

K = 3

N = 24

Ks = np.array([i for i in range(3, 17)])
Ns = np.array(np.linspace(3, 27, 1000))

#ks = opt.curve_fit(true_anal, Ns, anal(K, Ns), [1, 1, 1, 1, 1])[0]

#print(ks)

'''
N!
 ________

K!(N-K)!
'''

plt.scatter(Ns, [true_anal(N) for N in Ns], color="red")

plt.scatter(Ns, anal(K, Ns), color="green")
'''
with open("data.txt") as data_file:
    data_preord = [float(i) for i in data_file.read().split()]
    dots_mean = []
    dots_std = []
    for i in range(37):
        dot = []   
        for j in range(100):
            dot.append(data_preord[37 * j + i])
        dot = np.array(dot)
        dots_mean.append(dot.mean())  
        dots_std.append(dot.std()) 

dots_mean = np.array(dots_mean)
dots_std = np.array(dots_std)
'''

'''
with open("data.txt") as data_file:
    data = np.array([float(i) for i in data_file.read().split()])
    
    
dots = np.array([i * 1000 for i in range(len(data))])
plt.scatter(dots, abs(anal(K, 13) - data), color="green") 

with open("data1.txt") as data_file:
    data = np.array([float(i) for i in data_file.read().split()])
    
    
dots = np.array([i * 1000 for i in range(len(data))])
plt.scatter(dots, abs(anal(K, 13) - data), color="red")
'''
 
plt.show()
