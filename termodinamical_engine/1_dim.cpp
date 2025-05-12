#include <iostream>
#include <fstream>
#include <cmath>
#include <iostream>


class Particle{
public:
    double m = 0;
    double r = 0;
    double v = 0;
    double x = 0;
};


double time_processing(Particle* particles, int N, double L){ //TODO improve negative time handling
    double min_t = INFINITY;

    double l = particles[0].x - particles[0].r;
    
    double col_t = INFINITY;

    if (-particles[0].v > 0){
        col_t = l / (-particles[0].v);   
    } else{
        col_t = INFINITY;  
    }

    //std::cout<<l<<' '<<col_t<<' ';

    if (col_t < min_t){
        min_t = col_t;
    }

    for (int i = 0; i < N - 1; i++){
        l = (particles[i + 1].x - particles[i + 1].r) - (particles[i].x + particles[i].r);

        if ((particles[i].v - particles[i + 1].v) > 0.00000000001){
            col_t = l / (particles[i].v - particles[i + 1].v);   
        } else{
            col_t = INFINITY;  
        }

        //std::cout<<l<<' '<<col_t<<' ';

        if (col_t < min_t){
            min_t = col_t;
        }
    }

    l = L - (particles[N - 1].x + particles[N - 1].r);

    if (particles[N - 1].v > 0){
        col_t = l / particles[N - 1].v;   
    } else{
        col_t = INFINITY;  
    }
    
    //std::cout<<l<<' '<<col_t<<' '<<std::endl;

    if (col_t < min_t){
        min_t = col_t;
    }
    
   return min_t;   
}

void COLLIDE(Particle* particles, int N, double L, int& collisions){
    double l = particles[0].x - particles[0].r;
    if (l <= 0 and particles[0].v < 0){
        particles[0].v *= -1;       
        collisions += 1;
    }   
    
    for(int i = 0; i < N - 1; i++){
        l = (particles[i + 1].x - particles[i + 1].r) - (particles[i].x + particles[i].r);
        if (l <= 0.00000000001 and (particles[i].v - particles[i + 1].v) > 0){
            double v2 = (2 * particles[i].v + (particles[i + 1].m / particles[i].m - 1) * particles[i + 1].v) / (1 + particles[i + 1].m / particles[i].m);
            double v1 = v2 + particles[i + 1].v - particles[i].v;
            particles[i].v = v1;
            particles[i + 1].v = v2;
            collisions += 1;
        }
    }
    
    l = L - (particles[N - 1].x + particles[N - 1].r);
    if (l <= 0 and particles[N - 1].v > 0){
        particles[N - 1].v *= -1;
        collisions += 1;
    }

}



int main(){

    std::ofstream path_file;
    std::ofstream data_file;
    path_file.open("path.txt", std::ios::out | std::ios_base::trunc);
    data_file.open("data.txt", std::ios::out | std::ios_base::trunc);

    path_file.precision(16);
    data_file.precision(16);

    std::ifstream base("base.txt");
    std::ifstream cond("start.txt");
    
    double m[2];
    double r[2];    
    int N;

    double L;
    double time_limit;
    
    base>>time_limit>>L>>m[0]>>m[1]>>r[0]>>r[1]>>N;

    Particle particles[N];
    
    int k;

    for(int i = 0; i < N; i++){
        cond>>k;
        particles[i].m = m[k - 1];
        particles[i].r = r[k - 1];
        cond>>particles[i].x;
        cond>>particles[i].v; 
        //std::cout<<particles[i].m<<' '<<particles[i].r<<' '<<particles[i].v<<' '<<particles[i].x<<std::endl; 
    }
    
    double total_time = 0;
    
    double dt = 10;

    int collisions = 0;
    
    while(total_time < time_limit){

        double time = time_processing(particles, N, L);
        //std::cout<<time<<std::endl;
        //while (time < 0.001){
        //    time *= 1;
        //}

        while (time > dt){
            for(int i = 0; i < N; i++){
                path_file<<particles[i].x<<' ';
                particles[i].x += particles[i].v * dt;
            }
            path_file<<total_time<<std::endl;
            total_time += dt;
            time -= dt;
        }
    
        double kinetic1 = 0;
        double kinetic2 = 0;
        
        for(int i = 0; i < N; i++){
            //path_file<<particles[i].x<<' ';
            particles[i].x += particles[i].v * time;

            if(particles[i].m == m[0]){
                kinetic1 += m[0] * particles[i].v * particles[i].v / 2;
            } else{
                kinetic2 += m[1] * particles[i].v * particles[i].v / 2;
            }
        }

        //path_file<<total_time<<std::endl;
        data_file<<total_time<<' '<<collisions<<' '<<kinetic1<<' '<<kinetic2<<std::endl;

        COLLIDE(particles, N, L, collisions);

        total_time += time;
    }

    return 0;
}
