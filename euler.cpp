#include <fstream>
#include <iostream>

int main(){
    double x = 1;
    double u = 0;   
    double dt = 0.001;
    double w = 4;
    double gamma = 0.25;

    std::ofstream out_file;

    out_file.open("xu_1.txt", std::ios::out | std::ios_base::trunc);

    for(int i = 0; i < 50000; i++){
        double x_1 = x + dt * u;
        double u_1 = u - dt * w * w * x - 2 * gamma * u;
        x = x_1;
        u = u_1;
        std::cout<<x<<std::endl;
    }
    std::cout<<x;
    return 0;
}
