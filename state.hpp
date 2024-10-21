#ifndef _State_is_the_only_reason_to_go_forward_

#define _State_is_the_only_reason_to_go_forward_


template <typename acc_type> class State{
public:

    acc_type v[3][3];     
    int elements;
    int dimension;
    State(int dim, int n){
        elements = n;
        dimension = dim;
    }

    State(){ }

    State operator + (State ob){
        State<acc_type> A(dimension, elements);
        for(int i = 0; i < elements; i++){
            for(int j = 0; j < dimension; j++){
                A.v[i][j] = v[i][j] + ob.v[i][j]; 
            }
        } 

        
        return A;         
    }

    State operator - (State ob){
        State<acc_type> A(dimension, elements);
        for(int i = 0; i < elements; i++){
            for(int j = 0; j < dimension; j++){
                A.v[i][j] = v[i][j] - ob.v[i][j]; 
            }
        } 

        
        return A;         
    }


    friend State operator * (acc_type l, State ob){
        State<acc_type> A(ob.dimension, ob.elements);
        
        for(int i = 0; i < ob.elements; i++){
            for(int j = 0; j < ob.dimension; j++){
                A.v[i][j] = ob.v[i][j] * l; 
            }
        }      
        return A;    
    }

    friend State operator * (State ob, acc_type l){
        State<acc_type> A(ob.dimension, ob.elements);
        
        for(int i = 0; i < ob.elements; i++){
            for(int j = 0; j < ob.dimension; j++){
                A.v[i][j] = ob.v[i][j] * l;  
            }
        }      
        return A;    
    }

};

#endif
