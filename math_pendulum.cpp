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

        y_0.v[0][0] = conf["x_0"].get<float>();
        y_0.v[1][0] = conf["u_0"].get<float>();  

        float dt = conf["dt"].get<float>();
        int N = conf["N"].get<int>();

        float w = conf["w"].get<float>();
        float gamma = conf["gamma"].get<float>();

        std::string out_file = conf["output_file"].get<std::string>();

        if(conf["type"].get<std::string>() == "rungecutta"){
            Rungecutta<float, task_dimensions, equation_order> mp(y_0, dt, N, out_file, w, gamma); 
            mp.solve();   
        } else if(conf["type"].get<std::string>()== "heun"){
            Heun<float, task_dimensions, equation_order> mp(y_0, dt, N, out_file, w, gamma); 
            mp.solve();   
        } else if(conf["type"].get<std::string>() == "euler"){
            Euler<float, task_dimensions, equation_order> mp(y_0, dt, N, out_file, w, gamma); 
            mp.solve();   
        }         
    } else if(conf["acc_type"].get<std::string>() == "double"){
        State<double, task_dimensions, equation_order> y_0;

        y_0.v[0][0] = conf["x_0"].get<double>();
        y_0.v[1][0] = conf["u_0"].get<double>();

        double dt = conf["dt"].get<double>();
        int N = conf["N"].get<int>();

        double w = conf["w"].get<double>();
        double gamma = conf["gamma"].get<double>();

        std::string out_file = conf["output_file"].get<std::string>();

        if(conf["type"].get<std::string>() == "rungecutta"){
            Rungecutta<double, task_dimensions, equation_order> mp(y_0, dt, N, out_file, w, gamma); 
            mp.solve();   
        } else if(conf["type"].get<std::string>()== "heun"){
            Heun<double, task_dimensions, equation_order> mp(y_0, dt, N, out_file, w, gamma); 
            mp.solve();   
        } else if(conf["type"].get<std::string>() == "euler"){
            Euler<double, task_dimensions, equation_order> mp(y_0, dt, N, out_file, w, gamma); 
            mp.solve();   
        } 
    }

    return 0;
}
