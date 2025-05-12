import numpy as np
import pygame
import random
import os
import time
import matplotlib.pyplot as plt

'''
def set_start_rays(total_time, m1, m2, r1, r2, N):
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


'''








def register(start_pos, finish_pos, pos_type):
    if start_pos != None and finish_pos != None:
        x1, y1 = start_pos
        x2, y2 = finish_pos
        y1 = height - y1
        y2 = height - y2

        detA = x1 * y2 - y1 * x2;

        if detA != 0:
            a = (y2 - y1) / detA;
            b = (-x2 + x1) / detA;
            c = 1
        else:
            a = y1
            b = -x1
            c = 0  

        if pos_type == 'seg':
            detA = x1 * y2 - y1 * x2;

            if detA != 0:
                a = (y2 - y1) / detA;
                b = (-x2 + x1) / detA;
                c = 1
            else:
                a = y1
                b = -x1
                c = 0  

            segments.append([(x1, y1), (x2, y2), (a, b, c)])
            return 
        
        alpha = np.arctan((y2 - y1) / (x2- x1))
        rays.append([(x1, y1), alpha])

def info_save():
    with open("segments.txt", "w") as file:
        file.write(str(len(segments)) + '\n')
        for seg in segments:
            x1, y1 = seg[0]
            x2, y2 = seg[1]
            a, b, c = seg[2]
            file.write(str(x1) + ' ' + str(y1) + ' ' + str(x2) + ' ' + str(y2) + ' ' + str(a) + ' ' + str(b) + ' ' + str(c) + '\n')

    with open("rays.txt", "w") as file:
        file.write(str(len(rays)) + '\n')
        for ray in rays:
            x1, y1 = ray[0]
            alpha = ray[1]
            file.write(str(x1) + ' ' + str(y1) + ' ' + str(alpha) + '\n')

def info_send():
    os.system("./a.out")

def results_get():
    with open("path.txt") as file:
        data = file.read()
        paths = data.split('_')
        tracks = []
        for way in paths:
            path = way.split()
            track = []
            for i in range(0, len(path) // 2):
                track.append((float(path[i * 2]), height - float(path[i * 2 + 1])))
            tracks.append(track)
        #if tracks[-1].is_empty():
        tracks = tracks[:-1]
    return tracks  


pygame.init()
width = 1200
height = 760
screen = pygame.display.set_mode((width, height))
screen.fill((255, 255, 255))  
clock =  pygame.time.Clock()          
                

start_pos = None
finish_pos = None
pos_type = "seg"

segments = []
rays = []

register((0, 0), (width, 0), pos_type)
register((width, 0), (width, height), pos_type)
register((width, height), (0, height), pos_type)
register((0, 0), (0, height), pos_type)

sent = False

while True:

    clock.tick(60)    

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
        elif event.type == pygame.KEYDOWN and not sent:
            if event.key == pygame.K_r:
                start_pos = None
                finish_pos = None  
                pos_type = "ray"                          
            elif event.key == pygame.K_s:
                start_pos = None
                finish_pos = None
                pos_type = "seg"
            elif event.key == pygame.K_SPACE:
                #start_pos = None
                #finish_pos = None
                info_save()   
            elif event.key == pygame.K_RETURN:
                start_pos = None
                finish_pos = None
                info_send()   
                sent = True
                tracks = results_get()
            elif event.key == pygame.K_p:
                start_pos = None
                finish_pos = None
                sent = True
                tracks = results_get()
        elif event.type == pygame.MOUSEBUTTONDOWN and not sent:
            if event.button == 1:
                register(start_pos, finish_pos, pos_type)
                start_pos = event.pos
                finish_pos = None
            elif event.button == 3:
                finish_pos = event.pos


    screen.fill((255, 255, 255))
    for seg in segments:
        x1, y1 = seg[0]
        y1 = height - y1     
        x2, y2 = seg[1]
        y2 = height - y2    
        pygame.draw.circle(screen, (143, 143, 143), (x1, y1), 7)
        pygame.draw.circle(screen, (143, 143, 143), (x2, y2), 7)
        pygame.draw.line(screen, (143, 143, 143), (x1, y1), (x2, y2), width = 4)
    if not sent:
        for ray in rays:
            x1, y1 = ray[0]
            x2 = x1 + 37 * np.cos(ray[1])
            y2 = y1 + 37 * np.sin(ray[1])
            y1 = height - y1
            y2 = height - y2
            pygame.draw.circle(screen, (182, 39, 246), (x1, y1), 7)
            pygame.draw.line(screen, (182, 39, 246), (x1, y1), (x2, y2))
    else:
        for dots in tracks:
            pygame.draw.circle(screen, (182, 39, 246), dots[0], 7)
            for i in range(0, len(dots) - 1):
                pygame.draw.line(screen, (182, 39, 246), dots[i], dots[i+1], width = 2)   
    if start_pos != None:
        if pos_type == 'seg':
            pygame.draw.circle(screen, (255, 140, 0), start_pos, 7)
        else:
            pygame.draw.circle(screen, (220, 20, 60), start_pos, 7)
        if finish_pos != None:
            if pos_type == 'seg':
                pygame.draw.circle(screen, (6, 100, 152), finish_pos, 7)
            else:
                pygame.draw.circle(screen, (182, 39, 246), finish_pos, 7)
    pygame.display.flip()


