import numpy as np
import pygame
import random
import os
import time
import matplotlib.pyplot as plt

def set_base_conditions(total_time, m1, m2, r1, r2, N):
    with open("base.txt", "w") as file:
        file.write(str(total_time) + ' ' + str(L) + ' ' + str(m1) + ' ' + str(m2) + ' ' + str(r1) + ' ' + str(r2) + ' ' + str(N))

def set_random_start_conditions():
    with open("start.txt", "w") as file:   
        typs = []
        #typ = 2
        text = ''
        #x = L // (2 * N)
        #v = -7
        #text += str(typ) + ' ' + str(x) + ' ' + str(v) + '\n'
        for i in range(0, N):
            typ = random.randint(1,2)
            typs.append(typ)
            x = random.randint(L // N * i + eval(f"r{typ}"), L // N * (i + 1) - eval(f"r{typ}"))
            #x = random.randint(0, L)
            v = random.randint(-37, 37) / 69
            text += str(typ) + ' ' + str(x) + ' ' + str(v) + '\n'
            #except:
                #succeded = False
        file.write(text)
    return typs, x, v

def set_determined_start_conditions():
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

def start_processing():
    os.system("./a.out")

def read_path():
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

def read_data():
    with open("data.txt") as file:
        data = file.read()
        info = data.split()
        collisions = []
        collision_time = []
        kinetic1 = []
        kinetic2 = []
        impulse1 = []
        impulse2 = []
        T = []
        for i in range(0, len(info) // 4):
            collision_time.append(float(info[4 * i]))
            collisions.append(int(info[4 * i + 1]))
            kin1 = float(info[4 * i + 2])
            kin2 = float(info[4 * i + 3])
            kinetic1.append(kin1)
            impulse1.append(np.sqrt(2 * kin1 / m1) * m1)
            kinetic2.append(kin2)
            impulse2.append(np.sqrt(2 * kin2 / m2) * m2)
            T.append((kin1 + kin2) / N)
        kinetic1 = np.array(kinetic1) / typs.count(1)
        kinetic2 = np.array(kinetic2) / typs.count(2)
        impulse1 = np.array(impulse1)
        impulse2 = np.array(impulse2)


pygame.init()
width = 1800
height = 760
screen = pygame.display.set_mode((width, height))
screen.fill((255, 255, 255))

now = 0

#plt.scatter(collision_time, collisions)

plt.show()

#plt.plot(collision_time, kinetic1 * typs.count(1) + kinetic2 * typs.count(2))
#plt.scatter(collision_time, kinetic2)

dt = collision_time[10000]


kin_summ1 = 0
kin_summ2 = 0

last_time = 0

upd_kin1 = []
upd_kin2 = []

upd_time = []

i = 0

now_i = 0


while i < len(collision_time):
    kin_summ1 += kinetic1[i]
    kin_summ2 += kinetic2[i]
    if collision_time[i] - last_time > dt:
        upd_kin1.append(kin_summ1 / (i - now_i))
        upd_kin2.append(kin_summ2 / (i - now_i))
        kin_summ1 = 0
        kin_summ2 = 0
        now_i = i
        last_time = collision_time[now_i]
        upd_time.append(last_time)
        #i = now_i
    i += 1
        
print(len(collision_time))        
        
plt.plot(collision_time, kinetic1)
plt.plot(collision_time, kinetic2)    

plt.plot(upd_time, upd_kin1)
plt.plot(upd_time, upd_kin2)


plt.show()

#plt.plot(collision_time, impulse1 + impulse2)

plt.show()

start_time = time.perf_counter() * 1000

cur_time = start_time


while cur_time - start_time < total_time:
    cur_time = time.perf_counter() * 1000
    print(cur_time - start_time)
    if now < len(times) and cur_time - start_time > times[now]:
        screen.fill((255, 255, 255))
        for i in range(0, N):
            pygame.draw.circle(screen, (23 * i, 17 * i, 13 * i), (tracks[i][now], height // 2), eval(f"r{typs[i]}"))
        now += 1
    pygame.display.flip()


