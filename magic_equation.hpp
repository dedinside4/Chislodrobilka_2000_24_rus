#define task_dimensions 1
#define equation_order 2
	y_d.v[1][0] = - args.w0 * args.w0 * y.v[0][0] - args.gamma * y.v[1][0] + std::cos(args.w * t) * args.F;
