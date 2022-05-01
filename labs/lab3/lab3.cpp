#include "lab3.h"

using namespace lab3;
using isolation_interval::interval_t;

double lab3::get_func(double x) { return pow(log(x), 2) + 0.25 * x - 3; }
double lab3::get_derivative(double x) { return 2 * log(x) / x + 0.25; }
double lab3::get_derivative2(double x) { return (2 - 2 * log(x)) / pow(x, 2); }
//double lab3::get_func(double x) { return pow(x, 3) - 3 * x + 1; }
//double lab3::get_derivative(double x) { return 3 * pow(x, 2) - 3; }
//double lab3::get_derivative2(double x) { return 6*x; }

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
				if (get_func(begin) * get_func(x) < 0) 
				{
					begin = (begin < x - 2 * ISOLATION_STEP) ? x - 2 * ISOLATION_STEP : begin;
					return pair<double, double>(begin, x + ISOLATION_STEP);
				}	
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
	const double eps = MY_EPS;
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
	const double eps = MY_EPS;
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

//pair<double, double>* task3::method_newton(double a, double b)
//{
//	const double eps = 0.001;
//	if ((get_func(a) * get_func(b) >= 0) 
//		|| get_derivative(a) == 0 || get_derivative(b) == 0
//		|| get_derivative2(a) == 0 || get_derivative2(b) == 0) return nullptr;
//
//	double f = get_func(b), f2 = get_derivative2(b);
//	double x = a, h, n;
//
//	if (f * f2 > 0) x = b;
//
//	for (n = 1; true; n++) 
//	{
//		const double f1 = get_derivative(x);
//		f = get_func(x);
//		
//		h = f / f1;
//		x -= h;
//
//		if (fabs(h) <= eps) break;
//	}
//	
//	cout << "n: " << n << endl;
//	return new pair<double, double>(x, f);
//}

pair<double, double>* task3::method_newton(double a, double b)
{
	const double eps = MY_EPS;
	if (get_func(a) * get_func(b) >= 0) return nullptr;

	double f = get_func(b), f2 = get_derivative2(b), h, x, f1;
	int n;

	if (f * f2 > 0) x = b;
	else x = a;

	for (n = 1; true; n++) 
	{
		f = get_func(x);
		f1 = get_derivative(x);

		h = f / f1;
		x -= h;

		if (fabs(h) <= eps) break;
	}

	cout << "n: " << n << endl;
	return new pair<double, double>(x, get_func(x));
}

void task3::run(void)
{
	const shared_ptr<pair<double, double>*> my_value = make_shared<pair<double, double>*>(method_newton(0, 1));

	if (*my_value.get() == nullptr) cout << "не подходит интервал" << endl;
	else cout << "x: " << (*my_value.get())->first << "\tf(x): " << (*my_value.get())->second << endl;
}

pair<double, double>* task4::method_iterations(double a, double b) 
{
	const double eps = MY_EPS, N = 100;
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

pair<double, double>* task5::method_secant(double a, double b)
{
	const double eps = MY_EPS;
	if (get_func(a) * get_func(b) >= 0) return nullptr;

	int n;
	double f1 = get_func(a), f2 = get_func(b), x3, f3;

	for (n = 1; true; n++) 
	{
		x3 = b - ((f2 * (b - a)) / (f2 - f1));
		f3 = get_func(x3);

		if (fabs(f3) < eps) break;
		
		a = b, b = x3;
		f1 = f2, f2 = f3;
	}
	cout << "n: " << n << endl;
	return new pair<double, double>(x3, f3);
}

void task5::run(void) 
{
	const shared_ptr<pair<double, double>*> my_value = make_shared<pair<double, double>*>(method_secant(0, 1));

	if (*my_value.get() == nullptr) cout << "не подходит интервал" << endl;
	else cout << "x: " << (*my_value.get())->first << "\tf(x): " << (*my_value.get())->second << endl;
}

pair<double, double>* task6::method_combined(double a, double b)
{
	const double eps = MY_EPS;
	if (get_func(a) * get_func(b) >= 0) return nullptr;

	int n;
	
	/*double x0 = a;
	double x11 = x0 - get_func(x0) / get_derivative(x0);
	double x12 = a - ((b - a) * get_func(a) / (get_func(b) - get_func(a)));

	double e1 = (x11 + x12) / 2.;

	for (n = 1; true; n++) 
	{	
		a = x11, b = x12;
		x11 = a - get_func(a) / get_derivative(a);
		x12 = a - ((b - a) * get_func(a) / (get_func(b) - get_func(a)));

		e1 = (x11 + x12) / 2.;

		if (fabs(e1 - x11) <= eps) break;
	}
	
	cout << "n: " << n << endl;
	return new pair<double, double>(x11, get_func(x11));*/

	double f1, f2, fx, x;
	for (n = 1; true; n++) 
	{
		f1 = get_func(a), f2 = get_func(b);

		b = b - f2 * (b - a) / (f2 - f1);
		a = a - f1 / get_derivative(a);

		x = (a + b) / 2.;
		fx = get_func(x);

		if (fabs(fx) <= eps) break;
	}

	cout << "n: " << n << endl;
	return new pair<double, double>(x, fx);
}

void task6::run(void)
{
	const shared_ptr<pair<double, double>*> my_value = make_shared<pair<double, double>*>(method_combined(0, 1));

	if (*my_value.get() == nullptr) cout << "не подходит интервал" << endl;
	else cout << "x: " << (*my_value.get())->first << "\tf(x): " << (*my_value.get())->second << endl;
}

void test_method(pair<double, double>* (*method)(double a, double b), double begin) 
{
	for (auto i : isolation_interval::get_isolation_list(begin))
	{
		interval_t* result = method(i.first, i.second);

		if (!result) cout << "[ " << i.first << "; " << i.second << " ]" << endl;
		else cout << "[ " << i.first << "; " << i.second << " ]\tx = " << result->first << "; f(x) = " << result->second << endl;

		delete result;
	}
}

void lab3::lab(void) 
{
	cout << "[ Метод Дихотомии (поиск корней: х = -7) ]" << endl;
	test_method(task1::method_dichotomies, -7);
	cout << "------------------------------" << endl;

	cout << "[ Метод Хорд (поиск корней: х = -7) ]" << endl;
	test_method(task2::method_chord, -7);
	cout << "------------------------------" << endl;

	cout << "[ Метод Ньютона (поиск корней: х = -7) ]" << endl;
	test_method(task3::method_newton, -7);
	cout << "------------------------------" << endl;

	cout << "[ Метод Итераций (поиск корней: х = -7) ]" << endl;
	test_method(task4::method_iterations, -7);
	cout << "------------------------------" << endl;

	cout << "[ Метод Секущих (поиск корней: х = -7) ]" << endl;
	test_method(task5::method_secant, -7);
	cout << "------------------------------" << endl;

	cout << "[ Комбинированный Метод (поиск корней: х = -7) ]" << endl;
	test_method(task6::method_combined, -7);
	cout << "------------------------------" << endl;
}