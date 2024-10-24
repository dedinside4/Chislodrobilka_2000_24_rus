#ifndef The_methods_that_only_simulate_pathetic_fraction_of_our_beautiful_reality

#define The_methods_that_only_simulate_pathetic_fraction_of_our_beautiful_reality

#include <fstream>
#include "json.hpp"
#include <string>
#include "state.hpp"
#include <chrono>
#include <algorithm>
#include <iostream>

using json = nlohmann::json;

template <typename acc_type, int dim, int n> class Method{
public:
    
    int N;
    acc_type t = 0;
    acc_type dt;
    
    std::ofstream out_file;  
    json conf;

    State<acc_type, dim, n> y;

    Method(json config, State<acc_type, dim, n>& initial_conditions){
        conf = config;
        y = initial_conditions;
        dt = conf["dt"].get<acc_type>();
        N = conf["N"].get<int>();
        out_file.open(conf["output_file"].get<std::string>(), std::ios::out | std::ios_base::trunc);
    }  

    State<acc_type, dim, n> f(const acc_type t, const State<acc_type, dim, n>& y){
       State<acc_type, dim, n> y_d;
       for(int i = 0; i < n-1; i++){
            for(int j = 0; j < dim; j++){
                y_d.v[i][j] = y.v[i+1][j];
            }
        }
        //#include "magic_equation.hpp"
        return y_d;
    }   
    
};

template <typename acc_type, int dim, int n> class Euler{ //: public Method<acc_type, dim, n>{
public:

    int N;
    acc_type t = 0;
    acc_type dt;
    
    //std::ofstream out_file;  
    //json conf;

    State<acc_type, dim, n> y;


    Euler(json config, State<acc_type, dim, n>& initial_conditions){
        //conf = config;
        y = initial_conditions;
        dt = 0.00001;//config["dt"].get<acc_type>();
        N = 1000000000;//config["N"].get<int>();
        //out_file.open(conf["output_file"].get<std::string>(), std::ios::out | std::ios_base::trunc);
    }  

    State<acc_type, dim, n> f(const acc_type t, const State<acc_type, dim, n>& y_temp){
       State<acc_type, dim, n> y_d;
       for(int i = 0; i < n-1; i++){
            for(int j = 0; j < dim; j++){
                y_d.v[i][j] = y_temp.v[i+1][j];
            }
        }
        y_d.v[1][0] = - y_temp.v[0][0];
        //#include "magic_equation.hpp"
        return y_d;
    }

    void solve(){
        for(int i = 1; i < N; i++){

            y = y + dt * f(t, y);
            
            t += dt;
            //for(int j = 0; j < dim; j++){
            //    out_file<<y.v[0][j]<<' ';             
            //}
            //out_file<<std::endl;
        }
        std::cout<<y.v[0][0]<<y.v[1][0];
        //out_file.close();
    }

};



#endif
