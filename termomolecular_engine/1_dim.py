import numpy as np
import pygame
import random
import os
import time

with open("base.txt", "w") as file:
    total_time = 10000
    L = 1000
    m1 = 2
    m2 = 3
    r1 = 11
    r2 = 21
    N = 19
    file.write(str(total_time) + ' ' + str(L) + ' ' + str(m1) + ' ' + str(m2) + ' ' + str(r1) + ' ' + str(r2) + ' ' + str(N))

with open("start.txt", "w") as file:
    #succeded = False
    #while succeded != True:
        #succeded = True
        #try:    
    typs = []
    text = ''
    x = 0
    for i in range(0, N):
        typ = random.randint(1,2)
        typs.append(typ)
        x = random.randint(L // N * i + eval(f"r{typ}"), L // N * (i + 1) - eval(f"r{typ}"))
        v = random.randint(-20, 20) / 10
        text += str(typ) + ' ' + str(x) + ' ' + str(v) + '\n'
        #except:
            #succeded = False
    file.write(text)
'''

with open("start.txt", "w") as file:
    typs = []
    text = ''

    typ = 2
    typs.append(typ)
    x = 12
    v = 0.03
    text += str(typ) + ' ' + str(x) + ' ' + str(v) + '\n'

    typ = 2
    typs.append(typ)
    x = 21
    v = 0
    text += str(typ) + ' ' + str(x) + ' ' + str(v) + '\n'

    typ = 2
    typs.append(typ)
    x = 30
    v = -0.03
    text += str(typ) + ' ' + str(x) + ' ' + str(v) + '\n'

    file.write(text)
'''

os.system("./a.out")

with open("path.txt") as file:
    data = file.read()
    path = data.split()
    tracks = []
    times = []
    for i in range(0, N):
        track = []
        for j in range(0, len(path) // (N + 1)):
            track.append(float(path[j * (N + 1) + i]))
        tracks.append(track)
    for j in range(0, len(path) // (N + 1)):
        times.append(float(path[j * (N + 1) + N]))

pygame.init()
width = 1000
height = 760
screen = pygame.display.set_mode((width, height))
screen.fill((255, 255, 255))

now = 0

start_time = time.perf_counter() * 1000

cur_time = start_time

while cur_time - start_time < total_time:
    cur_time = time.perf_counter() * 1000
    print(cur_time - start_time)
    if now < len(times) and cur_time - start_time > times[now]:
        screen.fill((255, 255, 255))
        for i in range(0, N):
            pygame.draw.circle(screen, (0, 0, 0), (tracks[i][now], height // 2), eval(f"r{typs[i]}"))
        now += 1
    pygame.display.flip()


