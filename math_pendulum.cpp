#include <fstream>
#include "vector.hpp"
#include "json.hpp"
#include "simulation_methods.hpp"
using json = nlohmann::json;


double func(double t, Vector y, json conf){

        return -conf["w"].get<double>() * conf["w"].get<double>() * y.v[0];
}


int main(){
    std::ifstream f("config.json");
    json conf = json::parse(f);
    
    
    Vector y_0(conf["order"].get<int>());
    y_0.v[0] = conf["x_0"].get<double>();
    y_0.v[1] = conf["u_0"].get<double>();
    Method mp(func, conf, y_0);
    mp.solve();
}
