import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation


def lis_hist(a, b, d):

    bitterness = 20000

    t = np.linspace(0, 2 * np.pi, bitterness)
    x = np.sin(a*t + d)
    y = np.sin(b*t)

    dots = np.stack((x, y), axis=1)
    print(dots[0])    
    
    self_crossed_x = []
    self_crossed_y = []
    
    i = 1
    while i < bitterness - 1:
        l = np.linalg.norm((dots[:i] - dots[i]), axis=1)
        
        l_min = l[-1] / 1.5
        l = l[:-1]
        
        if np.any(l - l_min < 0):
            self_crossed_x.append(dots[i][0])
            self_crossed_y.append(dots[i][1])
            i += 10
        i += 1
            
        
    plt.scatter(self_crossed_x, self_crossed_y)
    plt.show()


lis_hist(3, 2, np.pi / 4)
