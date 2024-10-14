#ifndef _Vector_is_the_only_reason_to_go_forawrd_

#define _Vector_is_the_only_reason_to_go_forawrd_


class Vector{
public:

    double v[3][3];     
    int elements;
    int dimension;
    Vector(int dim, int n){
        elements = n;
        dimension = dim;
    }
    Vector(){
    }
    ~Vector(){
        //delete[] v;
    }

    Vector operator + (Vector ob){
        Vector A(dimension, elements);
        for(int i = 0; i < elements; i++){
            for(int j = 0; j < dimension; j++){
                A.v[i][j] = v[i][j] + ob.v[i][j]; 
            }
        } 

        
        return A;         
    }

    Vector operator - (Vector ob){
        Vector A(dimension, elements);
        for(int i = 0; i < elements; i++){
            for(int j = 0; j < dimension; j++){
                A.v[i][j] = v[i][j] - ob.v[i][j]; 
            }
        } 

        
        return A;         
    }


    friend Vector operator * (double l, Vector vector){
        Vector A(vector.dimension, vector.elements);
        
        for(int i = 0; i < vector.elements; i++){
            for(int j = 0; j < vector.dimension; j++){
                A.v[i][j] = vector.v[i][j] * l; 
            }
        }      
        return A;    
    }

    friend Vector operator * (Vector vector, double l){
        Vector A(vector.dimension, vector.elements);
        
        for(int i = 0; i < vector.elements; i++){
            for(int j = 0; j < vector.dimension; j++){
                A.v[i][j] = vector.v[i][j] * l;  
            }
        }      
        return A;    
    }

};

#endif
