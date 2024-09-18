import numpy as np 

n = 11

x = np.linspace(0, 10, n)

k = 2

b = 0.5



y = x * k + b + np.random.standard_normal(n)



b = np.matmul(np.stack((x, np.linspace(1, 1, n))), y)
a = np.matmul(np.stack((x, np.linspace(1, 1, n))), np.stack((x, np.linspace(1, 1, n)), axis=-1))

#print(a)

#print(b)

print(np.linalg.solve(a,b))
