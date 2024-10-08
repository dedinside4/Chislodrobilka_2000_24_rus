#ifndef _Vector_is_the_only_reason_to_go_forawrd_

#define _Vector_is_the_only_reason_to_go_forawrd_


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

#endif
