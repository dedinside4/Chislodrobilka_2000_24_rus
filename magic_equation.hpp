#define w 1.0
#define gamma 0.7
#define task_dimensions 1
#define equation_order 2
	y_d.v[1][0] = -w * w * y.v[0][0] - 2 * gamma * y.v[1][0];