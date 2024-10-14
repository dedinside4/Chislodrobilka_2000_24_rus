import time 

from numba import jit

@jit
def iteration(x, u, dt, w):
    x_1 = x + dt * u;
    u_1 = u - dt * w * w * x;
    x = x_1;
    u = u_1;
    return x, u

@jit
def eul(n):
    x = 1;
    u = 0;   
    dt = 0.00005;
    w = 1;

    for i in range(0,n):
        x, u = iteration(x, u, dt, w)
    return u


def main():
    start = time.perf_counter()
    u = eul(1)
    end = time.perf_counter()
    print(end-start)
    print(u)

    start = time.perf_counter()
    u = eul(1)
    end = time.perf_counter()
    print(end-start)
    print(u)    

    start = time.perf_counter()
    u = eul(1000000000)    
    end = time.perf_counter()
    print(end-start)
    print(u)


main()




