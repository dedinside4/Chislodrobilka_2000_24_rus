import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation



fig, ax = plt.subplots()

a = 3
b = 2
t = np.linspace(0, 2 * np.pi * (a - b), 40000)
d = np.linspace(0, 0 * np.pi, 1000)



x = np.sin(a*t + d[0])
y = np.sin(b*t)

#print(x)


line2 = ax.plot(x, y)[0]
ax.set(xlim=[-1.1, 1.1], ylim=[-1.1, 1.1], xlabel='x', ylabel='y')
ax.legend()


def update(frame):
    # for each frame, update the data stored on each artist.
    
    x = np.sin(a*t + d[frame])      

    # update the line plot:
    line2.set_xdata(x)
    line2.set_ydata(y)
    return (line2)


ani = animation.FuncAnimation(fig=fig, func=update, frames=1000, interval=30)
plt.show()
