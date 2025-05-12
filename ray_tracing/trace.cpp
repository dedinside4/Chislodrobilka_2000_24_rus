#include <iostream>
#include <fstream>
#include <cmath>
#include <iostream>

class Linear{
public:
    double a;
    double b;
    double c;

    Linear() { }

    Linear(double a, double b, double c) : a(a), b(b), c(c) { }

    double get_angle(){
        return std::atan(-a / b);
    }
};

class Quadric{
public:
    double a11;
    double a12;
    double a13;
    double a22;
    double a23;
    double a33;

    Quadric() { }

    Quadric(double a11, double a12, double a13, double a22, double a23, double a33) : a11(a11), a12(a12), a13(a13), a22(a22), a23(a23), a33(a33) { }

    Linear get_linear(double x, double y){
        double a = 2 * a12 * x + 2 * a22 * y + 2 * a23;
        double b = 2 * a11 * x + 2 * a12 * y + 2 * a13;
        double c = a * x + b * y;       
        return Linear(a, b, c);
    }
};

class Dot{
public:
    double x;
    double y;

    Dot() { }

    Dot(double x, double y) : x(x), y(y) { }
};

class Segment{ 
public:
    Dot start;
    Dot finish;
    Linear linear;
    
    Segment() { }

    Segment(double x1, double y1, double x2, double y2, double a, double b, double c){
        start = Dot(x1, y1);
        finish = Dot(x2, y2);
        linear = Linear(a, b, c);   
    }
};

class Segment2{ 
public:
    Dot start;
    Dot finish;
    Quadric quadric;
    
    Segment2() { }

    Segment2(double x1, double y1, double x2, double y2, double a11, double a12, double a13, double a22, double a23, double a33){
        start = Dot(x1, y1);
        finish = Dot(x2, y2);
        quadric = Quadric(a11, a12, a13, a22, a23, a33);   
    }
};

class Ray{
public:
    Dot start;
    double angle;
    Linear linear;
    double intensity; 

    Ray() { }

    Ray(double x, double y, double a){
        start = Dot(x, y);
        intensity = 1;
        angle = a; 
        process_linear();   
    }

    Linear process_linear(){ //TODO check rightfulness
        linear.a = std::sin(angle);
        linear.b = -std::cos(angle);
        linear.c = linear.a * start.x + linear.b * start.y;
        return Linear(linear.a, linear.b, linear.c);
    }
};


double reflected_angle(Ray ray, Linear surface){
    return 2 * surface.get_angle() - ray.angle;         
}



Dot get_intersection(Linear ray, Linear segment){


    double detA = ray.a * segment.b - ray.b * segment.a;

    //if(detA != 0){
    double x = (segment.b * ray.c - ray.b * segment.c) / detA;
    double y = (-segment.a * ray.c + ray.a * segment.c) / detA;
    //}
    std::cout<<x<<' '<<y<<std::endl;
    //double x = INFINITY;
    //double y = INFINITY;

    return Dot(x, y);     
}


Dot check_intersection(Ray& ray, Segment segment){
    Dot intersection = get_intersection(ray.process_linear(), segment.linear);

    if((intersection.x - ray.start.x) * std::cos(ray.angle) >= 0 and (intersection.y - ray.start.y) * std::sin(ray.angle) >= 0 and (segment.start.x - 1e-11 <= intersection.x and intersection.x <= segment.finish.x + 1e-11 or segment.start.x + 1e-11 >= intersection.x and intersection.x >= segment.finish.x - 1e-11) and (segment.start.y - 1e-11 <= intersection.y and intersection.y <= segment.finish.y + 1e-11 or segment.start.y + 1e-11 >= intersection.y and intersection.y >= segment.finish.y - 1e-11)){
        return intersection;          
    }   

    return Dot(INFINITY, INFINITY);      
}


Dot check_intersection_quad(Ray& ray, Segment2 segment){
    Dot intersection = get_intersection(ray.process_linear(), segment.linear);

    if((intersection.x - ray.start.x) * std::cos(ray.angle) >= 0 and (intersection.y - ray.start.y) * std::sin(ray.angle) >= 0 and (segment.start.x - 1e-11 <= intersection.x and intersection.x <= segment.finish.x + 1e-11 or segment.start.x + 1e-11 >= intersection.x and intersection.x >= segment.finish.x - 1e-11) and (segment.start.y - 1e-11 <= intersection.y and intersection.y <= segment.finish.y + 1e-11 or segment.start.y + 1e-11 >= intersection.y and intersection.y >= segment.finish.y - 1e-11)){
        return intersection;          
    }   

    return Dot(INFINITY, INFINITY);      
}












int main(){

    std::ofstream path_file;
    path_file.open("path.txt", std::ios::out | std::ios_base::trunc);

    std::ifstream segs("segments.txt");
    std::ifstream rays("rays.txt");

    int ray_count;
    rays>>ray_count;
    
    Ray* ray = new Ray[ray_count];  

    double x;
    double y; 
    double a;
    for(int i = 0; i < ray_count; i++){
        rays>>x;
        rays>>y;
        rays>>a;
        ray[i] = Ray(x, y, a);
    }

    int seg_count;
    segs>>seg_count;
    
    Segment* segments = new Segment[seg_count];    

    double x1;
    double y1;
    double x2; 
    double y2;
    double b;
    double c;
    for(int i = 0; i < seg_count; i++){
        segs>>x1;
        segs>>y1;
        segs>>x2;
        segs>>y2;
        segs>>a;
        segs>>b;
        segs>>c;
        segments[i] = Segment(x1, y1, x2, y2, a, b, c);
    }


    for(int j = 0; j < ray_count; j++){
        while(ray[j].intensity > 1e-2){
            double closest_range = INFINITY;
            int true_obstacle = 0;
            for(int i = 0; i < seg_count; i++){
                Dot intersection = check_intersection(ray[j], segments[i]);
                double now_range = std::pow(intersection.x - ray[j].start.x, 2) + std::pow(intersection.y - ray[j].start.y, 2);
                if(now_range < closest_range and now_range > 1e-13){
                    closest_range = now_range;
                    true_obstacle = i;        
                }  
            }
            std::cout<<closest_range<<std::endl;
            path_file<<ray[j].start.x<<' '<<ray[j].start.y<<std::endl;
            std::cout<<"obstacle number "<<true_obstacle<<std::endl;
            ray[j].start = get_intersection(ray[j].linear, segments[true_obstacle].linear);
            std::cout<<"now start "<<ray[j].start.x<<' '<<ray[j].start.y<<std::endl;
            ray[j].angle = reflected_angle(ray[j], segments[true_obstacle].linear);
            std::cout<<"now angle "<<ray[j].angle<<std::endl;
            ray[j].process_linear();
            ray[j].intensity *= 0.8;
        }
        path_file<<ray[j].start.x<<' '<<ray[j].start.y<<std::endl;
        path_file<<'_';
    }
    
    return 0;
}
