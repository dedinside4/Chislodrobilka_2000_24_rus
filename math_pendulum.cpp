#include <fstream>
#include "vector.hpp"
#include "json.hpp"
#include "simulation_methods.hpp"
#include <cmath>
using json = nlohmann::json;


void func(double t, Vector* y, Vector* y_d, json* config){
        int n = (*config)["order"].get<int>();
        double l = (*config)["l"].get<double>();
        double g = (*config)["g"].get<double>();
        double k = (*config)["k"].get<double>();        

        double dx = (*y).v[0][0];
        double dy = -(*y).v[0][1];
        double cosa = dy / l;
        double sina = dx / l;

        double T = k * (std::sqrt(dx * dx + dy * dy) - l); 
        if(T < 0){
            T = 0;        
        }  

        (*y_d).v[n - 1][0] = -T * sina;
        (*y_d).v[n - 1][1] = -g + T * cosa;
}


int main(){
    std::ifstream f("config.json");
    json conf = json::parse(f);
    
    
    Vector y_0(conf["dimension"].get<int>(), conf["order"].get<int>());
    y_0.v[0][0] = conf["x_0"].get<double>();
    y_0.v[0][1] = conf["y_0"].get<double>();
    y_0.v[1][0] = conf["ux_0"].get<double>();
    y_0.v[1][1] = conf["uy_0"].get<double>();
    Method mp(func, conf, y_0);
    mp.solve();
}
