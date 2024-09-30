#include <iostream>
#include <string> 

using namespace std;

void euler(double N, double dt, double x, double u, double w){
    for(int i = 1; i < N; i++){
        double x_1 = x + dt * u;
        double u_1 = u - dt * w * w * x;
        x = x_1;
        u = u_1;
        cout<<x<<' ';//<<' '<<u<<' ';
    } 
}

void heun(double N, double dt, double x, double u, double w){
    for(int i = 1; i < N; i++){
        double x_0 = x + dt * u;
        double u_0 = u - dt * w * w * x;
        double x_1 = x + (dt / 2) * (u + u_0);
        double u_1 = u - (dt / 2) * w * w * (x + x_0);
        x = x_1;
        u = u_1;
        cout<<x<<' ';//<<' '<<u<<' ';
    }
}

void rk(double N, double dt, double x, double u, double w){
    for(int i = 1; i < N; i++){
        double xk_1 = u;
        double uk_1 = - w * w * x;
        double xk_2 = u + (dt / 2) * uk_1;
        double uk_2 = - w * w * (x + (dt / 2) * xk_1);
        double xk_3 = u + (dt / 2) * uk_2;
        double uk_3 = - w * w * (x + (dt / 2) * xk_2);
        double xk_4 = u + dt * uk_3;
        double uk_4 = - w * w * (x + dt * xk_3);

        double x_1 = x + (dt / 6) * (xk_1 + 2 * xk_2 + 2 * xk_3 + xk_4);
        double u_1 = u + (dt / 6) * (uk_1 + 2 * uk_2 + 2 * uk_3 + uk_4);
        
        x = x_1;
        u = u_1;

        cout<<x<<' ';
    }
}






int main(int argc, char *argv[]){
    
    
    
    double N = stod(argv[1]);
    double t = stod(argv[2]);
    double u = stod(argv[3]);
    double x = stod(argv[4]);
    double w = stod(argv[5]);
    
    
    double dt = t / N;    
    
    euler(N, dt, x, u, w);
    heun(N, dt, x, u, w);
    rk(N, dt, x, u, w);
    

}
