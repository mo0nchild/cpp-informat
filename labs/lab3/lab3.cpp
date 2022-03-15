#include "lab3.h"

using namespace lab3;
using isolation_interval::interval_t;

double lab3::get_func(double x) { return pow(x, 3) - 3 * x + 3; }
double lab3::get_derivative(double x) { return 3 * pow(x, 2) - 3; }
double lab3::get_derivative2(double x) { return 6 * x; }

interval_t isolation_interval::get_isolation(double begin)
{
	for(int iter = 0; iter < ISOLATION_MAX_ITER; iter++)
	{
		double begin_derivative = get_derivative(begin), x;
		for (x = begin + ISOLATION_STEP; fabs(begin - x) <= ISOLATION_MAX_LENGTH; x += ISOLATION_STEP)
		{
			const double derivative = get_derivative(x);
			if ((begin_derivative / fabs(begin_derivative)) != (derivative / fabs(derivative)))
			{
				begin_derivative = get_derivative(begin = x);
				continue;
			}
			else 
			{
				if (get_func(begin) * get_func(x) < 0) return pair<double, double>(begin, x + ISOLATION_STEP);
			}
		}
		begin = x;
	}
	return pair<double, double>(0, 0);
}

vector<interval_t> isolation_interval::get_isolation_list(double begin)
{
	vector<interval_t> result;
	interval_t isolation = get_isolation(begin);

	while (isolation.first != isolation.second)
	{
		result.push_back(isolation);
		isolation = get_isolation(isolation.second);
	}

	return result;
}

pair<double, double>* task1::method_dichotomies(double a, double b) 
{
	const double eps = 0.001;
	if (get_func(a) * get_func(b) >= 0) return nullptr;

	double f1 = get_func(a), f2;
	int n;

	for (n = 1; true; n++) 
	{
		const double t = (a + b) / 2.;
		f2 = get_func(t);

		if (f1 * f2 < 0) b = t;
		else
		{
			a = t;
			f1 = f2;
		}
		if (fabs(b - a) <= eps) break;
	}

	cout << "n: " << n << endl;
	return new pair<double, double>((a + b) / 2., get_func((a + b) / 2.));
}

void task1::run(void) 
{
	const shared_ptr<pair<double, double>*> my_value = make_shared<pair<double, double>*>(method_dichotomies(0, 1));
	cout << "x: " << (*my_value.get())->first << "\tf(x): " << (*my_value.get())->second << endl;
}

pair<double, double>* task2::method_chord(double a, double b)
{
	const double eps = 0.001;
	if (get_func(a) * get_func(b) >= 0) return nullptr;

	double f1 = get_func(a), f2 = get_derivative2(a);

	struct my_pair { double x, z; };
	my_pair values = (f1 * f2 > 0 ? my_pair{ b, a } : my_pair{ a, b });

	int n;
	double fz = get_func(values.z), h;

	for (n = 1; true; n++)
	{
		f1 = get_func(values.x);
		h = (values.x - values.z) / (f1 - fz) * f1;
		values.x -= h;

		if (fabs(h) <= eps) break;
	}

	cout << "n: " << n << endl;
	return new pair<double, double>(values.x, f1);
}

void task2::run(void) 
{
	const shared_ptr<pair<double, double>*> my_value = make_shared<pair<double, double>*>(method_chord(0, 1));

	if (*my_value.get() == nullptr) cout << "не подходит интервал" << endl;
	else cout << "x: " << (*my_value.get())->first << "\tf(x): " << (*my_value.get())->second << endl;
}

pair<double, double>* task3::method_newton(double a, double b)
{
	const double eps = 0.001;
	if (get_func(a) * get_func(b) >= 0) return nullptr;

	double f = get_func(b), f2 = get_derivative2(b);
	double x = a, h, n;

	if (f * f2 > 0) x = b;

	for (n = 1; true; n++) 
	{
		const double f1 = get_derivative(x);
		f = get_func(x);
		
		h = f / f1;
		x -= h;

		if (fabs(h) <= eps) break;
	}
	
	cout << "n: " << n << endl;
	return new pair<double, double>(x, f);
}

void task3::run(void)
{
	const shared_ptr<pair<double, double>*> my_value = make_shared<pair<double, double>*>(method_newton(0, 1));

	if (*my_value.get() == nullptr) cout << "не подходит интервал" << endl;
	else cout << "x: " << (*my_value.get())->first << "\tf(x): " << (*my_value.get())->second << endl;
}

pair<double, double>* task4::method_iterations(double a, double b) 
{
	const double eps = 0.001, N = 100;
	if (get_func(a) * get_func(b) >= 0) return nullptr;

	auto G = [&](double x) -> double { return x - get_func(x) / get_derivative(x); };
	double x0 = a, n, x;

	for (n = 1; true; n++) 
	{
		x = G(x0);
		if (fabs(x - x0) <= eps || n >= N) break;
		else x0 = x;
	}

	cout << "n: " << n << endl;
	return new pair<double, double>(x, get_func(x));
}

void task4::run(void) 
{
	const shared_ptr<pair<double, double>*> my_value = make_shared<pair<double, double>*>(method_iterations(0, 1));

	if (*my_value.get() == nullptr) cout << "не подходит интервал" << endl;
	else cout << "x: " << (*my_value.get())->first << "\tf(x): " << (*my_value.get())->second << endl;
}

void lab3::lab(void) 
{
	/*task1::run();
	task2::run();
	task3::run();
	task4::run();*/

	for (auto i : isolation_interval::get_isolation_list(-7)) 
	{
		interval_t* result = task2::method_chord(i.first, i.second);

		cout << "[ " << i.first << "; " << i.second << " ]\tx = " << result->first << "; f(x) = " << result->second << endl;

		delete result;
	}
}