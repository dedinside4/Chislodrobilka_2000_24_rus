import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation



fig, ax = plt.subplots()

a = 5
b = 3
t = np.linspace(0, 2 * np.pi, 1000)
d = np.linspace(0, 2 * np.pi, 1000)



x = np.sin(a*t + d[0])
y = np.sin(b*t)


line2 = ax.plot(x, y)[0]
ax.set(xlim=[-1.1, 1.1], ylim=[-1.1, 1.1], xlabel='x', ylabel='y')
ax.legend()


def update(frame):
    # for each frame, update the data stored on each artist.
    
    x = np.sin(a*t[:frame + 1] + np.pi / 4)      
    y = np.sin(b*t[:frame + 1])
    # update the line plot:
    line2.set_xdata(x)
    line2.set_ydata(y)
    ax.set(xlim=[-1.1, 1.1], ylim=[-1.1, 1.1], xlabel= 'x', ylabel='y')
    return (line2)

def lis_hist(a, b, d):
    t = np.linspace(0, 2 * np.pi * (a - b), 1000)
    x = np.sin(a*t + d)
    y = np.sin(b*t)
    np.stack(x, y)   

    xs = np.linspace(-1, 1, 1000)
    
    

ani = animation.FuncAnimation(fig=fig, func=update, frames=1000, interval=1, repeat_delay=10000)
plt.show()
