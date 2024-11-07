#include <fstream>
#include "state.hpp"
#include "json.hpp"
#include "simulation_methods.hpp"
#include <cmath>
using json = nlohmann::json;

int main(){
    std::ifstream f("config.json");
    json conf = json::parse(f);

    if(conf["acc_type"].get<std::string>() == "float"){
        State<float, task_dimensions, equation_order> y_0;

        y_0.v[0][0] = conf["y_0_0"].get<float>();
        y_0.v[1][0] = conf["y_1_0"].get<float>();  

        float dt = conf["dt"].get<float>();
        int N = conf["N"].get<int>();

        std::string out_file = conf["output_file"].get<std::string>();

        if(conf["method_type"].get<std::string>() == "rungecutta"){
            Rungecutta<float, task_dimensions, equation_order> mp(y_0, dt, N, out_file); 
            mp.solve();   
        } else if(conf["method_type"].get<std::string>()== "heun"){
            Heun<float, task_dimensions, equation_order> mp(y_0, dt, N, out_file); 
            mp.solve();   
        } else if(conf["method_type"].get<std::string>() == "euler"){
            Euler<float, task_dimensions, equation_order> mp(y_0, dt, N, out_file); 
            mp.solve();   
        }         
    } else if(conf["acc_type"].get<std::string>() == "double"){
        State<double, task_dimensions, equation_order> y_0;

        y_0.v[0][0] = conf["y_0_0"].get<double>();
        y_0.v[1][0] = conf["y_1_0"].get<double>();

        double dt = conf["dt"].get<double>();
        int N = conf["N"].get<int>();

        std::string out_file = conf["output_file"].get<std::string>();

        if(conf["method_type"].get<std::string>() == "rungecutta"){
            Rungecutta<double, task_dimensions, equation_order> mp(y_0, dt, N, out_file); 
            mp.solve();   
        } else if(conf["method_type"].get<std::string>()== "heun"){
            Heun<double, task_dimensions, equation_order> mp(y_0, dt, N, out_file); 
            mp.solve();   
        } else if(conf["method_type"].get<std::string>() == "euler"){
            Euler<double, task_dimensions, equation_order> mp(y_0, dt, N, out_file); 
            mp.solve();   
        } 
    }

    return 0;
}
