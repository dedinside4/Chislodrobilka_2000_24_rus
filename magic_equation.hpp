#define task_dimensions 2
#define equation_order 2
    using namespace std;
	//y_d[1][0] = - args.w0 * args.w0 * y[0][0] - 2 * args.gamma * y[1][0] + (std::cos(args.w * t) / std::abs(std::cos(args.w * t))) * args.F;
    y_d[1][0] = ( args.l * sin(y[0][0] - y[0][1]) * y[1][1] * y[1][1] - args.l * sin(y[0][0] - y[0][1]) * cos(y[0][0] - y[0][1]) * y[1][0] * y[1][0] - 2 * args.g * sin(y[0][0]) - args.g * cos(y[0][0] - y[0][1]) * sin(y[0][1]) ) / (args.l * (2 - cos(y[0][0] - y[0][1]) * cos(y[0][0] - y[0][1])));
    
    y_d[1][1] = ( -args.l * sin(y[0][0] - y[0][1]) * y[1][0] * y[1][0] + args.l * sin(y[0][0] - y[0][1]) * cos(y[0][0] - y[0][1]) * y[1][1] * y[1][1] / 2 - args.g * sin(y[0][1]) - args.g * cos(y[0][0] - y[0][1]) * sin(y[0][0]) ) / (args.l * (1 - cos(y[0][0] - y[0][1]) * cos(y[0][0] - y[0][1]) / 2));
