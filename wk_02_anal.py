from math import factorial
from matplotlib import pyplot as plt
import numpy as np

def C(N, k):
    return factorial(N) / factorial(k) / factorial(N - k)

def anal(K, N):

    q = 0

    for i in range(1, K):
        q += (-1)**(i + 1) * C(K, i) * ((K - i) / K)**N

    p = 1 - q

    return p

K = 37

Ns = np.array([i for i in range(1, 126)])

plt.plot(Ns, anal(K, Ns))

with open("data.txt") as data_file:
    data = [float(i) for i in data_file.read().split()]
    plt.plot(Ns, data)    

plt.show()
