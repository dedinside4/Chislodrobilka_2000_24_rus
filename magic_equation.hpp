#ifndef w
#define w 1
#define task_dimensions 1
#define equation_order 2
#endif


//void equation(const acc_type t, const State<acc_type, dim, n>& y_temp, State<acc_type, dim, n> y_d){
    y_d.v[1][0] = - w * w * y.v[0][0];
//}



