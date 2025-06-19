#include <fstream>
#include <mpi.h>


int main(){

const int N = 100;

//std::ifstream dims("dimensions.txt");
std::ifstream sig("sigma.txt");
std::ifstream f1("phi0.txt");
std::ifstream f2("phi1.txt");

std::ofstream res("solution.txt");

double dx;
double dy;

//dims>>dx;
//dims>>dy;

dx = 1;
dy = 1;

double phi[N + 2][N + 2] = {0}; 
double phi_res[N + 2][N + 2] = {0}; 
double sigma[N + 2][N + 2] = {0};

double phi0[N + 2] = {0};
double phi1[N + 2] = {0};

for(int y = 0; y < N ; y++){
    f1>>phi0[y + 1];
    f2>>phi1[y + 1];
    phi[0][y + 1] = 2 * phi0[y + 1];
    phi[1][y + 1] = 2 * phi1[y + 1];
    for(int x = 0; x < N; x++){
        sig>>sigma[x + 1][y + 1];
    }   
    sigma[0][y + 1] = sigma[1][y + 1];
    sigma[N + 1][y + 1] = sigma[N][y + 1];
}

double dt = 1e-3;

double iterations = 1e7;

for(int i = 0; i < iterations; i++){
   
    for(int x = 1; x <= N ; x++){
        for(int y = 1; y <= N; y++){
            double jxp = 2 * sigma[x - 1][y] * sigma[x][y] / (sigma[x - 1][y] + sigma[x][y]) * (phi[x - 1][y] - phi[x][y]) / dx;
            double jyp = 2 * sigma[x][y - 1] * sigma[x][y] / (sigma[x][y - 1] + sigma[x][y]) * (phi[x][y - 1] - phi[x][y]) / dy;
            double jxn = 2 * sigma[x][y] * sigma[x + 1][y] / (sigma[x][y] + sigma[x + 1][y]) * (phi[x][y] - phi[x + 1][y]) / dx;
            double jyn = 2 * sigma[x][y] * sigma[x][y + 1] / (sigma[x][y] + sigma[x][y + 1]) * (phi[x][y] - phi[x][y + 1]) / dy;
            
            phi_res[x][y] = phi[x][y] + ((jxp - jxn) / dx + (jyp - jyn) / dy) * dt;    
            //phi[x][y] += ((jxp - jxn) / dx + (jyp - jyn) / dy) * dt;    
        }
    }
    for(int y = 1; y <= N; y++){
        for(int x = 1; x<=N; x++){
            phi[x][y] = phi_res[x][y];//TODO can optimize        
        }
        phi[0][y] = 2 * phi0[y] - phi[1][y];
        phi[N + 1][y] = 2 * phi1[y] - phi[N][y];
    }

}

for(int y = 1; y <= N; y++){
        for(int x = 1; x<=N; x++){
            res<<phi[x][y]<<' ';     
        }
    }


return 0;
    
}


