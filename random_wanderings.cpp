#include <fstream>
#include <random>
#include <cmath>

int main(){

    std::ofstream out_file;
    out_file.open("data.txt", std::ios::out | std::ios_base::trunc);

    std::random_device r;
    std::default_random_engine e1(r());
    
    std::uniform_int_distribution<int> uniform_dist(-5, 6);  
    
    int total_sailors = 100000;

    int total_steps = 300;
    
    int sample_steps = 10;
        
    int sample_size = 10000;
    
    
    int samples = 80;

    for(int i = 70; i < samples; i++){
        int total_sailors = sample_size * i;
        float total_shift = 0;
        float total_abs_shift = 0;
        float total_sq_shift = 0;
        for(int sailor = 0; sailor < total_sailors; sailor++){
            float pos = 0;
            for(int step = 0; step < total_steps; step++){          
                pos += uniform_dist(e1);
            }
            total_shift += pos;
            total_abs_shift += std::abs(pos);
            total_sq_shift += pos * pos;   
            out_file << pos << ' '; 
        }
        //out_file << total_shift / total_sailors << ' ' << total_abs_shift / total_sailors << ' ' << total_sq_shift / total_sailors << ' ';
    }
    
    return 0;
}
