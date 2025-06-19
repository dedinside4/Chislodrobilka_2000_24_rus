import numpy as np
import matplotlib.pyplot as plt
import os


N = 100

def sigma_write():
    with open("sigma.txt", "w") as file:
        sigma = ''
        for y in range(0, N // 2):
            for x in range(0, N // 2):
                sigma += '1 '
            for x in range(N // 2, N):
                sigma += '3 '
        for y in range(N // 2, N):
            for x in range(0, N // 2):
                sigma += '2 '
            for x in range(N // 2, N):
                sigma += '10000 '
        file.write(sigma)

def f1_write():
    with open("phi0.txt", "w") as file:
        phi0 = ''
        for i in range(0, N):
            phi0 += '0 '
        file.write(phi0)

def f2_write():
    with open("phi1.txt", "w") as file:
        phi1 = ''
        for i in range(0, N):
            phi1 += '1 '
        file.write(phi1)
def activate():
    os.system("./a.out")


sigma_write()
f1_write()
f2_write()

activate()


with open("solution.txt", "r") as file:
    a = np.array([float(value) for value in file.read().split()])
    sol = a.reshape((N, N))

plt.pcolor(sol)

print(sol)

plt.show()

plt.plot([i for i in range(N)], sol[0])

plt.show()
