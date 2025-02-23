import matplotlib.pyplot as plt
import numpy as np

with open("data.txt") as file:
    data = file.read()
    info = data.split()
    
sample = [float(i) for i in info]
print(sample)
plt.hist(sample, bins=200)
plt.show()
