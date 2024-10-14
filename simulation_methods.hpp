#ifndef The_methods_that_only_simulate_pathetic_fraction_of_our_beautiful_reality

#define The_methods_that_only_simulate_pathetic_fraction_of_our_beautiful_reality

#include <fstream>
#include "json.hpp"
#include <string>
#include "vector.hpp"
#include <chrono>

using json = nlohmann::json;

class Method{
public:
    double c[6] = {0, (double)1/4, (double)3/8, (double)12/13, 1, (double)1/2};
    double b1[6] = {(double)16/135, 0, (double)6656/12825, (double)28561/56430, (double)-9/50, (double)2/55};
    double b2[6] = {(double)25/216, 0, (double)1408/2565, (double)2197/4104, (double)-1/5, 0};
    double a[6][6] = {
                      {0, 0, 0, 0, 0, 0},
                      {(double)1/4, 0, 0, 0, 0, 0},
                      {(double)3/32, (double)9/32, 0, 0, 0, 0},
                      {(double)1932/2197, (double)-7200/2197, (double)7296/2197, 0, 0, 0},
                      {(double)439/216, (double)-8, (double)3680/513, (double)-845/4104, 0, 0},
                      {(double)-8/27, (double)2, (double)-3544/2565, (double)1859/4104, (double)-11/40, 0}    
                     };
    
    int n;
    int N;
    int dim;
    double t = 0;
    double dt;
    Vector y;
    Vector k1;
    Vector k2;
    Vector k3;
    Vector k4;
    Vector k5;
    Vector k6;
    Vector y_1;
    Vector y_2;
    std::ofstream out_file;  
    json conf;
    void (*xn_f)(double, Vector*, Vector*, json*);

    Method(void (*func)(double, Vector*, Vector*, json*), json config, Vector initial_conditions){
        conf = config;
        xn_f = func;
        n = conf["order"].get<int>();
        dim = conf["dimension"].get<int>();
        y = initial_conditions;
        dt = conf["dt"].get<double>();
        N = conf["N"].get<int>();
        out_file.open(conf["output_file"].get<std::string>(), std::ios::out | std::ios_base::trunc);
    }  

    Vector f(double t, Vector y){
        Vector y_d(dim, n);
        for(int i = 0; i < n-1; i++){
            for(int j = 0; j < dim; j++){
                y_d.v[i][j] = y.v[i+1][j];
            }
        }
        xn_f(t, &y, &y_d, &conf); 
        return y_d;
    }
    
    void solve(){
        if(conf["type"].get<std::string>() == "rungecutta"){
            solve_rungecut();
        } else if(conf["type"].get<std::string>()== "heun"){
            solve_heun();
        } else if(conf["type"].get<std::string>() == "euler"){
            solve_euler();
        } 
        out_file<<std::endl;
        out_file.close();
    }

    void solve_rungecut(){
        auto start = std::chrono::steady_clock::now();
        Vector comp(dim, n);
        Vector err(dim, n);
        Vector tr(dim, n);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < dim; j++){
                comp.v[i][j] = 0;
            }
        }
        for(int i = 1; i < N; i++){
            k1 = f(t, y);
            k2 = f(t + c[1] * dt, y + (dt * (a[1][0] * k1)));
            k3 = f(t + c[2] * dt, y + dt * (a[2][0] * k1 + a[2][1] * k2));
            k4 = f(t + c[3] * dt, y + dt * (a[3][0] * k1 + a[3][1] * k2 + a[3][2] * k3));
            k5 = f(t + c[4] * dt, y + dt * (a[4][0] * k1 + a[4][1] * k2 + a[4][2] * k3 + a[4][3] * k4));
            k6 = f(t + c[5] * dt, y + dt * (a[5][0] * k1 + a[5][1] * k2 + a[5][2] * k3 + a[5][3] * k4 + a[5][4] * k5));

            err = dt * (b1[0] * k1 + b1[1] * k2 + b1[2] * k3 + b1[3] * k4 + b1[4] * k5 + b1[5] * k6) - comp;
            tr = y + err;
            comp = (tr - y) - err;

            y_2 = y + dt * (b2[0] * k1 + b2[1] * k2 + b2[2] * k3 + b2[3] * k4 + b2[4] * k5 + b2[5] * k6);
            y = tr;
            t += dt;
            for(int j = 0; j < dim; j++){
                out_file<<y.v[0][j]<<' ';                  
            }
            out_file<<std::endl;
        }
        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
        out_file << std::chrono::duration<double>(diff).count();
    }
    
    void solve_heun(){
        Vector comp(dim, n);
        Vector err(dim, n);
        Vector tr(dim, n);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < dim; j++){
                comp.v[i][j] = 0;
            }
        }
        for(int i = 1; i < N; i++){
            y_1 = y + dt * f(t, y);
    
            err = (dt / 2) * (f(t, y) + f(t + dt, y_1)) - comp;
            tr = y + err;            
            comp = (tr - y) - err;            

            y = tr;
            t += dt;
            for(int j = 0; j < dim; j++){
                out_file<<y.v[0][j]<<' ';                  
            }
            out_file<<std::endl;
        } 
    }
    
    void solve_euler(){
        for(int i = 1; i < N; i++){
            y_1 = y + dt * f(t, y);
            y = y_1;
            t += dt;
            for(int j = 0; j < dim; j++){
                out_file<<y.v[0][j]<<' ';                  
            }
            out_file<<std::endl;
        }
    }
    
};

#endif
