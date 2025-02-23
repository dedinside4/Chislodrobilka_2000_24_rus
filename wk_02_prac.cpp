#include <fstream>
#include <random>

int check(bool* sample, int K){
    for(int i = 0; i < K; i++){
        if(not sample[i]){
            return 0;        
        }
    }
    return 1;
}

int main(){

    std::ofstream out_file;
    out_file.open("data.txt", std::ios::out | std::ios_base::trunc);

    std::random_device r;
    std::default_random_engine e1(r());

    int K = 37;
    
    std::uniform_int_distribution<int> uniform_dist(0, K - 1);
    
    int N_MAX = 125;    
    
    bool sample[K] = {true};

    int total_iters = 100000;

    //float p[N_MAX];

    for(int N = 0; N < N_MAX; N++){
        int succeeded = 0; 
        for(int iter = 0; iter < total_iters; iter++){          
            for(int i = 0; i <= N; i++){
                sample[uniform_dist(e1)] = true;
            }
            succeeded += check(sample, K);
            for(int i = 0; i < K; i++){
                sample[i] = false;
            }     
        }

        float p = (float)succeeded / (float)total_iters;
        out_file<<p<<' ';        
    }
    
    
    
    return 0;
}
