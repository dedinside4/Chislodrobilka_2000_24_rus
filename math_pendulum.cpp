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

        y_0[0][0] = conf["q_0"].get<float>();
        //y_0[0][1] = conf["q_1"].get<float>(); 
        y_0[1][0] = conf["qd_0"].get<float>();
        //y_0[1][1] = conf["qd_1"].get<float>();  

        arg_data<float> args;

        args.dt = conf["dt"].get<float>();
        args.N = conf["N"].get<int>();
        args.l = conf["l"].get<float>();
        args.nu = conf["nu"].get<float>();
        args.a = conf["a"].get<float>();
        args.g = conf["g"].get<float>();
    

        std::string out_file = conf["output_file"].get<std::string>();

        if(conf["method_type"].get<std::string>() == "rungecutta"){
            Rungecutta<float, task_dimensions, equation_order> mp(y_0, args, out_file); 
            mp.solve();   
        } else if(conf["method_type"].get<std::string>()== "heun"){
            Heun<float, task_dimensions, equation_order> mp(y_0, args, out_file); 
            mp.solve();   
        } else if(conf["method_type"].get<std::string>() == "euler"){
            Euler<float, task_dimensions, equation_order> mp(y_0, args, out_file); 
            mp.solve();   
        }         
    } else if(conf["acc_type"].get<std::string>() == "double"){
        State<double, task_dimensions, equation_order> y_0;

        y_0[0][0] = conf["q_0"].get<float>();
        //y_0[0][1] = conf["q_1"].get<float>(); 
        y_0[1][0] = conf["qd_0"].get<float>();
        //y_0[1][1] = conf["qd_1"].get<float>();  

        arg_data<double> args;

        args.dt = conf["dt"].get<double>();
        args.N = conf["N"].get<int>();
        args.l = conf["l"].get<double>();
        args.nu = conf["nu"].get<double>();
        args.a = conf["a"].get<double>();
        args.g = conf["g"].get<double>();

        std::string out_file = conf["output_file"].get<std::string>();

        if(conf["method_type"].get<std::string>() == "rungecutta"){
            Rungecutta<double, task_dimensions, equation_order> mp(y_0, args, out_file); 
            mp.solve();   
        } else if(conf["method_type"].get<std::string>()== "heun"){
            Heun<double, task_dimensions, equation_order> mp(y_0, args, out_file); 
            mp.solve();   
        } else if(conf["method_type"].get<std::string>() == "euler"){
            Euler<double, task_dimensions, equation_order> mp(y_0, args, out_file); 
            mp.solve();   
        } 
    }

    return 0;
}
