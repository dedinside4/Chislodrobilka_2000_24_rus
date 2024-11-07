#ifndef The_methods_that_only_simulate_pathetic_fraction_of_our_beautiful_reality

#define The_methods_that_only_simulate_pathetic_fraction_of_our_beautiful_reality

#include <fstream>
#include "json.hpp"
#include <string>
#include "state.hpp"
#include <chrono>
#include <algorithm>
#include <iostream>
#include <initializer_list>

using json = nlohmann::json;

template <typename acc_type, int dim, int n> class Method{
public:
    
    int N;
    acc_type t = 0;
    acc_type dt;  
    
    std::ofstream out_file;  

    State<acc_type, dim, n> y;

    Method(State<acc_type, dim, n>& initial_conditions, acc_type dt, int N, std::string output_file) : y(initial_conditions), dt(dt), N(N){
        out_file.open(output_file, std::ios::out | std::ios_base::trunc);
    }  
    
    ~Method(){
        out_file.close();
    }

    State<acc_type, dim, n> f(const acc_type t, const State<acc_type, dim, n>& y){
       State<acc_type, dim, n> y_d;
       for(int i = 0; i < n-1; i++){
            for(int j = 0; j < dim; j++){
                y_d.v[i][j] = y.v[i+1][j];
            }
        }
        #include "magic_equation.hpp"
        return y_d;
    }   
    
};

template <typename acc_type, int dim, int n> class Euler: public Method<acc_type, dim, n>{
public:

    using Method<acc_type, dim, n>::N;
    using Method<acc_type, dim, n>::t;
    using Method<acc_type, dim, n>::dt;
    
    using Method<acc_type, dim, n>::out_file;  

    using Method<acc_type, dim, n>::y; 

    using Method<acc_type, dim, n>::f; 


    Euler(State<acc_type, dim, n>& y_0, acc_type dt, int N, std::string out_file) : Method<acc_type, dim, n>(y_0, dt, N, out_file){ }    

    //State<acc_type, dim, n> c;    
    
    //State<acc_type, dim, n> dy;

    State<acc_type, dim, n> y_t;
    
    void solve(){
        for(int i = 1; i < N; i++){

            y_t = y + dt * f(t, y);
            y = y_t;
            //dy = dt * f(t, y);
            //y_t = y + dy;
            //c = (y_t - y) - dy;  
            //y = y_t;        

            t += dt;
            for(int j = 0; j < dim; j++){
                out_file<<y.v[0][j]<<' ';             
            }
            out_file<<std::endl;
        }
    }

};

template <typename acc_type, int dim, int n> class Heun: public Method<acc_type, dim, n>{
public:

    using Method<acc_type, dim, n>::N;
    using Method<acc_type, dim, n>::t;
    using Method<acc_type, dim, n>::dt;
    
    using Method<acc_type, dim, n>::out_file;  

    using Method<acc_type, dim, n>::y; 

    using Method<acc_type, dim, n>::f; 

    State<acc_type, dim, n> y_1;

    Heun(State<acc_type, dim, n>& y_0, acc_type dt, int N, std::string out_file) : Method<acc_type, dim, n>(y_0, dt, N, out_file){ }    

    void solve(){
        for(int i = 1; i < N; i++){
            y_1 = y + dt * f(t, y);
    
            y = y + (dt / 2) * (f(t, y) + f(t + dt, y_1));

            t += dt;
            for(int j = 0; j < dim; j++){
                out_file<<y.v[0][j]<<' ';                  
            }
            out_file<<std::endl;
        } 
    }

};

template <typename acc_type, int dim, int n> class Rungecutta: public Method<acc_type, dim, n>{
public:

    using Method<acc_type, dim, n>::N;
    using Method<acc_type, dim, n>::t;
    using Method<acc_type, dim, n>::dt;
    
    using Method<acc_type, dim, n>::out_file;  

    using Method<acc_type, dim, n>::y; 

    using Method<acc_type, dim, n>::f; 

    acc_type c[6] = {0, (acc_type)1/4, (acc_type)3/8, (acc_type)12/13, 1, (acc_type)1/2};
    acc_type b1[6] = {(acc_type)16/135, 0, (acc_type)6656/12825, (acc_type)28561/56430, (acc_type)-9/50, (acc_type)2/55};
    acc_type b2[6] = {(acc_type)25/216, 0, (acc_type)1408/2565, (acc_type)2197/4104, (acc_type)-1/5, 0};
    acc_type a[6][6] = {
                      {0, 0, 0, 0, 0, 0},
                      {(acc_type)1/4, 0, 0, 0, 0, 0},
                      {(acc_type)3/32, (acc_type)9/32, 0, 0, 0, 0},
                      {(acc_type)1932/2197, (acc_type)-7200/2197, (acc_type)7296/2197, 0, 0, 0},
                      {(acc_type)439/216, (acc_type)-8, (acc_type)3680/513, (acc_type)-845/4104, 0, 0},
                      {(acc_type)-8/27, (acc_type)2, (acc_type)-3544/2565, (acc_type)1859/4104, (acc_type)-11/40, 0}    
                     };

    State<acc_type, dim, n> k1;
    State<acc_type, dim, n> k2;
    State<acc_type, dim, n> k3;
    State<acc_type, dim, n> k4;
    State<acc_type, dim, n> k5;
    State<acc_type, dim, n> k6;

    Rungecutta(State<acc_type, dim, n>& y_0, acc_type dt, int N, std::string out_file) : Method<acc_type, dim, n>(y_0, dt, N, out_file){ }    

    void solve(){
        for(int i = 1; i < N; i++){
            k1 = f(t, y);
            k2 = f(t + c[1] * dt, y + (dt * (a[1][0] * k1)));
            k3 = f(t + c[2] * dt, y + dt * (a[2][0] * k1 + a[2][1] * k2));
            k4 = f(t + c[3] * dt, y + dt * (a[3][0] * k1 + a[3][1] * k2 + a[3][2] * k3));
            k5 = f(t + c[4] * dt, y + dt * (a[4][0] * k1 + a[4][1] * k2 + a[4][2] * k3 + a[4][3] * k4));
            k6 = f(t + c[5] * dt, y + dt * (a[5][0] * k1 + a[5][1] * k2 + a[5][2] * k3 + a[5][3] * k4 + a[5][4] * k5));

            y = y + dt * (b2[0] * k1 + b2[1] * k2 + b2[2] * k3 + b2[3] * k4 + b2[4] * k5 + b2[5] * k6);

            t += dt;
             for(int j = 0; j < dim; j++){
                out_file<<y.v[0][j]<<' ';                  
            }
            out_file<<std::endl;
        }
    }

};



#endif
