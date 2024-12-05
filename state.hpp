#ifndef _State_is_the_only_reason_to_go_forward_

#define _State_is_the_only_reason_to_go_forward_
#include <iostream>
#include <array>

template <typename acc_type, int dimension, int elements> class State{
public:

    acc_type v[elements][dimension] = {0};

    State(){
        //std::cout << "constructor1. address: " << this << '\n';
    }

    //State() {std::cout << "constructor2. address: " << this << '\n'; }
    //State(State const&) { std::cout << "copy constructor\n"; }
    //State(State&&) { std::cout << "move constructor\n"; }
    //~State() { std::cout << "destructor. address: " << this << '\n';}
    
    State<acc_type, dimension, elements> operator = (State ob){
        std::swap(ob.v, v);
        return *this;
    }

    const acc_type* operator[] (int i) const {
       return v[i];         
    }
        
    acc_type* operator[] (int i){
       return v[i];         
    }

};

//template <typename acc_type, int dimension, int elements>
//acc_type* operator[] (const State<acc_type, dimension, elements>& ob, int i) {
//    
 //      return ob.v[i];         
 //   }


template <typename acc_type, int dimension, int elements>
State<acc_type, dimension, elements> operator + (const State<acc_type, dimension, elements>&  a, const State<acc_type, dimension, elements>&  b){
    State<acc_type, dimension, elements> A;
    for(int i = 0; i < elements; i++){
        for(int j = 0; j < dimension; j++){
            A.v[i][j] = a.v[i][j] + b.v[i][j]; 
        }
    } 

    
    return A;         
}

template <typename acc_type, int dimension, int elements>
State<acc_type, dimension, elements> operator - (const State<acc_type, dimension, elements>&  a, const State<acc_type, dimension, elements>& b){
    State<acc_type, dimension, elements> A;
    for(int i = 0; i < elements; i++){
        for(int j = 0; j < dimension; j++){
            A.v[i][j] = a.v[i][j] - b.v[i][j]; 
        }
    } 

    
    return A;         
}

template <typename acc_type, int dimension, int elements>
State<acc_type, dimension, elements> operator * (acc_type l, const State<acc_type, dimension, elements>&  ob){
    State<acc_type, dimension, elements> A;
    
    for(int i = 0; i < elements; i++){
        for(int j = 0; j < dimension; j++){
            A.v[i][j] = ob.v[i][j] * l; 
        }
    }      
    return A;    
}

template <typename acc_type, int dimension, int elements>
State<acc_type, dimension, elements> operator * (const State<acc_type, dimension, elements>&  ob, acc_type l){
    State<acc_type, dimension, elements> A;
    
    for(int i = 0; i < elements; i++){
        for(int j = 0; j < dimension; j++){
            A.v[i][j] = ob.v[i][j] * l;  
        }
    }      
    return A;    
}

#endif
