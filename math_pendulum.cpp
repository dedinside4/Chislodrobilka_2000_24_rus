#include <fstream>
#include "state.hpp"
#include "json.hpp"
#include "simulation_methods.hpp"
#include <cmath>
using json = nlohmann::json;

void naive(int gay, json conf){
    float x = conf["x_0"].get<float>();
    float u = conf["u_0"].get<float>();  
    float dt = conf["dt"].get<float>();
    float w = conf["w"].get<float>();
    int N = conf["N"].get<int>();
    float t = 0;

    for(int i = 0; i < N; i++){
        float x_1 = x + dt * u;
        float u_1 = u - dt * w * w * x;
        x = x_1;
        u = u_1;
        t += dt;
    }
    std::cout<<x<<u;
}

void generic(int N, json conf){
    const int dim = 1;//conf["dimension"].get<int>();
    const int n = 2;//conf["order"].get<int>();

    State<float, dim, n> y_0;

    y_0.v[0][0] = conf["x_0"].get<float>();
    y_0.v[1][0] = conf["u_0"].get<float>(); 

    Euler<float, dim, n> mp(conf, y_0);
    mp.solve();
}


int main(){
    std::ifstream f("config.json");
    json conf = json::parse(f);

    using namespace std::chrono;

    const int N = 1000000000; 

    auto start = high_resolution_clock::now();
    naive(N, conf);
    auto stop = high_resolution_clock::now();
    
    auto duration = duration_cast<milliseconds>(stop - start);
    std::cout << "naive timing: " << duration.count() << std::endl;

    start = high_resolution_clock::now();
    generic(N, conf); 
    stop = high_resolution_clock::now();    
    duration = duration_cast<milliseconds>(stop - start);
    std::cout << "generic algorithm timing: " << duration.count() << std::endl;


    //if(conf["acc_type"].get<std::string>() == "float"){
    //    State<float> y_0(conf["dimension"].get<int>(), conf["order"].get<int>());
    //    y_0.v[0][0] = conf["x_0"].get<float>();
    //    y_0.v[1][0] = conf["u_0"].get<float>();  
    //    Method<float> mp(equation<float>, conf, y_0);  
    //    mp.solve();           
    //} else if(conf["acc_type"].get<std::string>() == "double"){
    //    State<double> y_0(conf["dimension"].get<int>(), conf["order"].get<int>());
    //    y_0.v[0][0] = conf["x_0"].get<double>();
    //    y_0.v[1][0] = conf["u_0"].get<double>();
    //    Method<double> mp(equation<double>, conf, y_0);  
    //    mp.solve();
    //}

    return 0;
}
