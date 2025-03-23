#include <iostream>
#include <fstream>





int main(){
    
    std::ofstream out_file;
    out_file.open("joke.txt", std::ios::out | std::ios_base::trunc);

    float r;
    std::cin>>r;

    float y;    
    std::cin>>y;  

    int N;    
    std::cin>>N;
    
    for(int i = 1; i < N; i++){  
        y = y * (r - y);
        out_file<<y<<std::endl;  
    }

    

    return 0;
}
