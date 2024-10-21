#include <fstream>
#include "state.hpp"
#include "json.hpp"
#include "simulation_methods.hpp"
#include <cmath>
using json = nlohmann::json;


template <typename acc_type> void equation(acc_type t, State<acc_type>* y, State<acc_type>* y_d, json* config){

        acc_type l = (*config)["l"].get<acc_type>();
        acc_type g = (*config)["g"].get<acc_type>();     

        acc_type x = (*y).v[0][0];
        acc_type v = (*y).v[1][0];    


        (*y_d).v[1][0] = - g * std::sin(x / l);
}



int main(){
    std::ifstream f("config.json");
    json conf = json::parse(f);
    if(conf["acc_type"].get<std::string>() == "float"){
        State<float> y_0(conf["dimension"].get<int>(), conf["order"].get<int>());
        y_0.v[0][0] = conf["x_0"].get<float>();
        y_0.v[1][0] = conf["u_0"].get<float>();  
        Method<float> mp(equation<float>, conf, y_0);  
        mp.solve();           
    } else if(conf["acc_type"].get<std::string>() == "double"){
        State<double> y_0(conf["dimension"].get<int>(), conf["order"].get<int>());
        y_0.v[0][0] = conf["x_0"].get<double>();
        y_0.v[1][0] = conf["u_0"].get<double>();
        Method<double> mp(equation<double>, conf, y_0);  
        mp.solve();
    }

    return 0;
}
