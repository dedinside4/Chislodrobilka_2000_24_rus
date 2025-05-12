#include <fstream>





























int main(){

const int N = 10000;

std::ifstream dims("start.txt");
std::ifstream segs("phi0.txt");
std::ifstream rays("phi1.txt");

double dx;
double dy;

dims>>dx;
dims>>dy;

dx /= N;
dy /= N;

double phi[N + 2][N + 2] = {0}; 
double sigma[N + 2][N + 2] = {0};

double phi0[N];
double phi1[N];


double dt = 1e-5;

double iterations = 1e8;

for(int i = 0; i < iterations; i++){

    
    for(int x = 1; x <= N ; x++){
        for(int y = 1; y <= N; y++){
            double jxp = 2 * sigma[x - 1][y] * sigma[x][y] / (sigma[x - 1][y] + sigma[x][y]) * (phi[x - 1][y] - phi[x][y]) / dx;
            double jyp = 2 * sigma[x][y - 1] * sigma[x][y] / (sigma[x][y - 1] + sigma[x][y]) * (phi[x][y - 1] - phi[x][y]) / dy;
            double jxn = 2 * sigma[x][y] * sigma[x + 1][y] / (sigma[x][y] + sigma[x + 1][y]) * (phi[x][y] - phi[x + 1][y]) / dx;
            double jyn = 2 * sigma[x][y] * sigma[x][y + 1] / (sigma[x][y] + sigma[x][y + 1]) * (phi[x][y] - phi[x][y + 1]) / dy;
            
            phi[x][y] += ((jxp - jxn) / dx + (jyp - jyn) / dy) * dt;        
        }
    }
    for(int y = 1; y <= N; y++){
        phi[0][y] = 2 * phi0[y] - phi[1][y];
        phi[N + 1][y] = 2 * phi1[y] - phi[N][y];
    }


}



return 0;
    
}


