#include <fstream>
#include <iostream>
#include "json.hpp"
#include <string>
using json = nlohmann::json;

class Vector{
public:

    double v[40];     
    int n;
    Vector(int dimension){
        n = dimension;
    }
    Vector(){
    }
    ~Vector(){
        //delete[] v;
    }


    Vector operator + (Vector ob){
        Vector A(n);
        for(int i = 0; i < n; i++){
            A.v[i] = v[i] + ob.v[i]; 
        } 
        return A;         
    }

    friend Vector operator * (double l, Vector vector){
        Vector A(vector.n);
        for(int i = 0; i < vector.n; i++){
            A.v[i] = vector.v[i] * l; 
        }      
        return A;    
    }

    friend Vector operator * (Vector vector, double l){
        Vector A(vector.n);
        for(int i = 0; i < vector.n; i++){
            A.v[i] = vector.v[i] * l; 
        }      
        return A;    
   }

};

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
    double args[10];
    double (*xn_f)(double, Vector, double*);

    Vector f(double t, Vector y){
        Vector y_d(n);
        for(int i = 0; i < n-1; i++){
            y_d.v[i] = y.v[i+1];
        }
        y_d.v[n-1] = xn_f(t, y, args); 
        return y_d;
    }
    
    void solve(json conf){
        if(conf["type"].get<std::string>() == "rungecat"){
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
        for(int i = 1; i < N; i++){
            k1 = f(t, y);
            k2 = f(t + c[1] * dt, y + (dt * (a[1][0] * k1)));
            k3 = f(t + c[2] * dt, y + dt * (a[2][0] * k1 + a[2][1] * k2));
            k4 = f(t + c[3] * dt, y + dt * (a[3][0] * k1 + a[3][1] * k2 + a[3][2] * k3));
            k5 = f(t + c[4] * dt, y + dt * (a[4][0] * k1 + a[4][1] * k2 + a[4][2] * k3 + a[4][3] * k4));
            k6 = f(t + c[5] * dt, y + dt * (a[5][0] * k1 + a[5][1] * k2 + a[5][2] * k3 + a[5][3] * k4 + a[5][4] * k5));
            y_1 = y + dt * (b1[0] * k1 + b1[1] * k2 + b1[2] * k3 + b1[3] * k4 + b1[4] * k5 + b1[5] * k6);
            y_2 = y + dt * (b2[0] * k1 + b2[1] * k2 + b2[2] * k3 + b2[3] * k4 + b2[4] * k5 + b2[5] * k6);
            y = y_1;
            t += dt;
            out_file<<y.v[0]<<' ';
        }
    }
    
    void solve_heun(){
        for(int i = 1; i < N; i++){
            y_1 = y + dt * f(t, y);
            y_2 = y + (dt / 2) * (f(t, y) + f(t + dt, y_1));
            y = y_2;
            t += dt;
            out_file<<y.v[0]<<' ';
        } 
    }
    
    void solve_euler(){
        for(int i = 1; i < N; i++){
            y_1 = y + dt * f(t, y);
            y = y_1;
            t += dt;
            out_file<<y.v[0]<<' ';
        }
    }

    Method(double (*func)(double, Vector, double*), json conf, Vector initial_conditions){
        xn_f = func;
        n = conf["order"].get<int>();
        y = initial_conditions;
        dt = conf["dt"].get<double>();
        N = conf["N"].get<int>();
        out_file.open(conf["output_file"].get<std::string>(), std::ios::out | std::ios_base::trunc);
        args[0] = conf["w"].get<double>();
    }  
    

};

double func(double t, Vector y, double* args){

        return -args[0] * args[0] * y.v[0];
}


int main(){
    std::ifstream f("config.json");
    json conf = json::parse(f);
    
    
    Vector y_0(conf["order"].get<int>());
    y_0.v[0] = conf["x_0"].get<double>();
    y_0.v[1] = conf["u_0"].get<double>();
    Method rk45(func, conf, y_0);
    rk45.solve(conf);
}
