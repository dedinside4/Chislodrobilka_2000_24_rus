#ifndef _State_is_the_only_reason_to_go_forward_

#define _State_is_the_only_reason_to_go_forward_

#include <iostream>

template <typename acc_type> class State{
public:

    acc_type v[3][3];     
    int elements = 2;
    int dimension = 1;
    State(int dim, int n){
        //std::cout << "constructor1. address: " << this << '\n';
        elements = n;
        dimension = dim;
    }


    State() { };// {std::cout << "constructor2. address: " << this << '\n'; }
    //State(State const&) { std::cout << "copy constructor\n"; }
    //State(State&&) { std::cout << "move constructor\n"; }
    //~State() { std::cout << "destructor. address: " << this << '\n';}


    State<acc_type>& operator = (const State<acc_type>&);
    State<acc_type>& operator + (const State<acc_type>&);
    State<acc_type>& operator - (const State<acc_type>&);
    
};

template <typename acc_type> struct StateBuffer{
    State<acc_type> state_array[40];
    unsigned int next = 0;
    void reset(){
        next = 0;
    }
    State<acc_type>& get_state(){
        next += 1;
       // std::cout<<next;
        return state_array[next - 1];
    }   
};


template<typename acc_type>
StateBuffer<acc_type> buffer;

template <typename acc_type>
State<acc_type>& State<acc_type>::operator = (const State<acc_type>& ob){
        for(int i = 0; i < elements; i++){
            for(int j = 0; j < dimension; j++){
                v[i][j] = ob.v[i][j]; 
            }
        }
        buffer<acc_type>.reset();
        return *this;
}

template <typename acc_type>
State<acc_type>& State<acc_type>::operator + (const State<acc_type>& b){
        for(int i = 0; i < elements; i++){
            for(int j = 0; j < dimension; j++){
                buffer<acc_type>.state_array[buffer<acc_type>.next].v[i][j] = v[i][j] + b.v[i][j]; 
            }
        } 
        return buffer<acc_type>.get_state();         
    }

template <typename acc_type>
State<acc_type>& State<acc_type>::operator - (const State<acc_type>& b){
        for(int i = 0; i < elements; i++){
            for(int j = 0; j < dimension; j++){
                buffer<acc_type>.state_array[buffer<acc_type>.next].v[i][j] = v[i][j] - b.v[i][j]; 
            }
        } 
        return buffer<acc_type>.get_state();         
    }

template <typename acc_type>
State<acc_type>& operator * (acc_type l, const State<acc_type>& ob){
        
        for(int i = 0; i < ob.elements; i++){
            for(int j = 0; j < ob.dimension; j++){
                buffer<acc_type>.state_array[buffer<acc_type>.next].v[i][j] = ob.v[i][j] * l; 
            }
        }      
        return buffer<acc_type>.get_state();    
    }
template <typename acc_type>
State<acc_type>& operator * (const State<acc_type>& ob, acc_type l){
        
        for(int i = 0; i < ob.elements; i++){
            for(int j = 0; j < ob.dimension; j++){
                buffer<acc_type>.state_array[buffer<acc_type>.next].v[i][j] = ob.v[i][j] * l; 
            }
        }      
        return buffer<acc_type>.get_state();    
    }

#endif
