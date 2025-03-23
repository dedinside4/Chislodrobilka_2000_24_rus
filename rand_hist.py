import matplotlib.pyplot as plt
import numpy as np
import scipy.optimize as opt


def norm_density(x, mean, ster, norm):
    return norm * np.exp(-(x - mean)**2 / 2 / ster**2) / ster / np.sqrt(2 * np.pi)  
    



with open("data.txt") as file:
    data = file.read()
    info = data.split()
    
N = np.array([i * 10000 for i in range(1, 10000)])

#sample1 = np.array([float(info[3 * i]) for i in range(len(info) // 3)])

#sample2 = np.array([float(info[3 * i + 1]) for i in range(len(info) // 3)])

#sample3 = np.array([float(info[3 * i + 2]) for i in range(len(info) // 3)])

sample = np.array([float(info[i]) for i in range(1, 70 * 10000)])



#print(sample)
hist = np.histogram(sample, bins=int(np.max(sample) - np.min(sample)) // 2)[0]

x = np.array([i + np.min(sample) for i in range(0, len(hist))])

res = opt.curve_fit(norm_density, x, hist)

print(res)

m, q, n = res[0]

print(m, q)

#plt.scatter(x, hist)

plt.plot(x, norm_density(x, m, q, n))


#std1 = [sample1[:i].std() / sample1[:i].mean() for i in range(1,70)]
#std2 = [sample2[:i].std() / sample2[:i].mean() for i in range(1,70)]
#std3 = [sample3[:i].std() / sample3[:i].mean() for i in range(1,70)]


#plt.scatter(N , std1)
#plt.scatter(N , std2)
#plt.scatter(N , std3)

plt.show()
