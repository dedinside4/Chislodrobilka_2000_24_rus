
#include <iostream>

int main(){
    double x = 1;
    double u = 0;   
    double dt = 0.005;
    double w = 1;

    for(int i = 0; i < 1000000000; i++){
        double x_1 = x + dt * u;
        double u_1 = u - dt * w * w * x;
        x = x_1;
        u = u_1;
        //std::cout<<x;
    }
    std::cout<<x;
    return 0;
}
