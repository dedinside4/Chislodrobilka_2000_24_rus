#include <cmath>
#include <random>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <climits>

int main(){

    std::ofstream out_file;
    out_file.open("data.txt", std::ios::out | std::ios_base::trunc);

    std::random_device r;

    std::default_random_engine e1(r());

    int b = 10000;

    std::uniform_real_distribution<double> uniform_dist(-b, b);

    //double mean = uniform_dist(e1);
    //double disp = uniform_dist(e1);

    //std::cout << "Randomly-chosen mean: " << mean << '\n';

    //std::mt19937 e2(r());

    //std::normal_distribution<> normal_dist(mean, disp);

    int a = 100;

    double k1;
    double k2;

    for (int n = 0; n != 1000000; ++n){
        double pre_value = uniform_dist(e1);
        if (pre_value < 0){
            k1 = b / a / a;
            k2 = 2 * b / a;          
        } else{
            k1 = - b / a / a;
            k2 = 2 * b / a;  
        }
        double value = (std::sqrt(k2 * k2 + 4 * pre_value * k1) - k2) / 2 / k1; 
        out_file<<value<<' ';
    }

    return 0;
}
