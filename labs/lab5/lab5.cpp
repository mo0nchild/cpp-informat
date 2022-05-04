#include "lab5.h"

using namespace lab5;

double task_const_values::F(const double x) { return pow(x, 2) / (sqrt(pow(x, 2) + 2)); }
double task_const_values::F0(const double x) { return (x * sqrt(pow(x, 2) + 2) - 2 * log(fabs(sqrt(pow(x, 2) + 2) + x))) / 2.; }
double lab5::newton_method(double a, double b, double (*func)(double x)) { return fabs(func(b) - func(a)); }

double task1::rectangle_method(double a, double b, const int n)
{
	double h = (b - a) / n, S = 0;
	for (uint16_t i = 1; i <= n; i++) S += task_const_values::F(a + (i - 0.5) * h);
	return h * S;
}

void task1::run(void) 
{
	cout << "====================[ Метод средних прямоугольников ]====================" << endl << endl;

	cout << "Значение интеграла (n = 10): " << rectangle_method(task_const_values::integration_begin, 
		task_const_values::integration_end, 10) << endl;

	cout << "Значение интеграла (n = 50): " << rectangle_method(task_const_values::integration_begin,
		task_const_values::integration_end, 50) << endl;

	cout << "Значение интеграла (n = 100): " << rectangle_method(task_const_values::integration_begin,
		task_const_values::integration_end, 100) << endl;

	cout.precision(4);
	cout << "Абсолютная погрешность (n = 10): " << fabs(rectangle_method(task_const_values::integration_begin, task_const_values::integration_end, 10)
		- newton_method(task_const_values::integration_begin, task_const_values::integration_end, task_const_values::F)) << endl;

	cout << "Абсолютная погрешность (n = 50): " << fabs(rectangle_method(task_const_values::integration_begin, task_const_values::integration_end, 50)
		- newton_method(task_const_values::integration_begin, task_const_values::integration_end, task_const_values::F)) << endl;

	cout << "Абсолютная погрешность (n = 100): " << fabs(rectangle_method(task_const_values::integration_begin, task_const_values::integration_end, 100)
		- newton_method(task_const_values::integration_begin, task_const_values::integration_end, task_const_values::F)) << endl << endl;
}

double task2::trapezoid_method(double a, double b, const int n)
{
	double h = (b - a) / n, S = 0;
	for (uint16_t i = 1; i < n; i++) S += task_const_values::F(a + i * h);
	return h * ((task_const_values::F(a) + task_const_values::F(b)) / 2 + S);
}

void task2::run(void) 
{
	cout << "============================[ Метод трапеций ]============================" << endl << endl;

	cout << "Значение интеграла (n = 10): " << trapezoid_method( task_const_values::integration_begin,
		task_const_values::integration_end, 10) << endl;

	cout << "Значение интеграла (n = 50): " << trapezoid_method(task_const_values::integration_begin,
		task_const_values::integration_end, 50) << endl;

	cout << "Значение интеграла (n = 100): " << trapezoid_method(task_const_values::integration_begin,
		task_const_values::integration_end, 100) << endl;

	cout.precision(4);
	cout << "Абсолютная погрешность (n = 10): " << fabs(trapezoid_method(task_const_values::integration_begin, task_const_values::integration_end, 10)
		- newton_method(task_const_values::integration_begin, task_const_values::integration_end, task_const_values::F)) << endl;

	cout << "Абсолютная погрешность (n = 50): " << fabs(trapezoid_method(task_const_values::integration_begin, task_const_values::integration_end, 50)
		- newton_method(task_const_values::integration_begin, task_const_values::integration_end, task_const_values::F)) << endl;

	cout << "Абсолютная погрешность (n = 100): " << fabs(trapezoid_method(task_const_values::integration_begin, task_const_values::integration_end, 100)
		- newton_method(task_const_values::integration_begin, task_const_values::integration_end, task_const_values::F)) << endl << endl;
}

double task3::parabola_method(double a, double b, const int n)
{
	if (n % 2 != 0) return 0;
	double h = (b - a) / n, S1 = 0, S2 = 0;
	
	for (uint16_t i = 1; i < n; i++) 
	{
		if (i % 2 == 0) S1 += task_const_values::F(a + i * h);
		else S2 += task_const_values::F(a + i * h);
	}

	return h / 3. * (task_const_values::F(a) + task_const_values::F(b) + 2 * S1 + 4 * S2);
}

void task3::run(void) 
{
	cout << "====================[ Метод парабол (формула Симпсона) ]====================" << endl << endl;

	cout << "Значение интеграла (n = 10): " << parabola_method(task_const_values::integration_begin,
		task_const_values::integration_end, 10) << endl;

	cout << "Значение интеграла (n = 50): " << parabola_method(task_const_values::integration_begin,
		task_const_values::integration_end, 50) << endl;

	cout << "Значение интеграла (n = 100): " << parabola_method(task_const_values::integration_begin,
		task_const_values::integration_end, 100) << endl;

	cout.precision(4);
	cout << "Абсолютная погрешность (n = 10): " << fabs(parabola_method(task_const_values::integration_begin, task_const_values::integration_end, 10)
		- newton_method(task_const_values::integration_begin, task_const_values::integration_end, task_const_values::F)) << endl;

	cout << "Абсолютная погрешность (n = 50): " << fabs(parabola_method(task_const_values::integration_begin, task_const_values::integration_end, 50)
		- newton_method(task_const_values::integration_begin, task_const_values::integration_end, task_const_values::F)) << endl;

	cout << "Абсолютная погрешность (n = 100): " << fabs(parabola_method(task_const_values::integration_begin, task_const_values::integration_end, 100)
		- newton_method(task_const_values::integration_begin, task_const_values::integration_end, task_const_values::F)) << endl << endl;
}

double task4::left_rectangle_method(double a, double b, const int n)
{
	double S = 0, h = (b - a) / n;
	for (uint16_t i = 1; i <= n; i++) S += task_const_values::F(a + h * (i - 1));
	return S * h;
}

void task4::run(void)
{
	cout << "====================[ Метод левых прямоугольников ]====================" << endl << endl;

	cout << "Значение интеграла (n = 10): " << left_rectangle_method(task_const_values::integration_begin,
		task_const_values::integration_end, 10) << endl;

	cout << "Значение интеграла (n = 50): " << left_rectangle_method(task_const_values::integration_begin,
		task_const_values::integration_end, 50) << endl;

	cout << "Значение интеграла (n = 100): " << left_rectangle_method(task_const_values::integration_begin,
		task_const_values::integration_end, 100) << endl;

	cout.precision(4);
	cout << "Абсолютная погрешность (n = 10): " << fabs(left_rectangle_method(task_const_values::integration_begin, task_const_values::integration_end, 10)
		- newton_method(task_const_values::integration_begin, task_const_values::integration_end, task_const_values::F)) << endl;

	cout << "Абсолютная погрешность (n = 50): " << fabs(left_rectangle_method(task_const_values::integration_begin, task_const_values::integration_end, 50)
		- newton_method(task_const_values::integration_begin, task_const_values::integration_end, task_const_values::F)) << endl;

	cout << "Абсолютная погрешность (n = 100): " << fabs(left_rectangle_method(task_const_values::integration_begin, task_const_values::integration_end, 100)
		- newton_method(task_const_values::integration_begin, task_const_values::integration_end, task_const_values::F)) << endl << endl;

}

double task5::right_rectangle_method(double a, double b, const int n)
{
	double S = 0, h = (b - a) / n;
	for (uint16_t i = 1; i <= n; i++) S += task_const_values::F(a + h * i);
	return S * h;
}

void task5::run(void)
{
	cout << "====================[ Метод правых прямоугольников ]====================" << endl << endl;

	cout << "Значение интеграла (n = 10): " << right_rectangle_method(task_const_values::integration_begin,
		task_const_values::integration_end, 10) << endl;

	cout << "Значение интеграла (n = 50): " << right_rectangle_method(task_const_values::integration_begin,
		task_const_values::integration_end, 50) << endl;

	cout << "Значение интеграла (n = 100): " << right_rectangle_method(task_const_values::integration_begin,
		task_const_values::integration_end, 100) << endl;

	cout.precision(4);
	cout << "Абсолютная погрешность (n = 10): " << fabs(right_rectangle_method(task_const_values::integration_begin, task_const_values::integration_end, 10)
		- newton_method(task_const_values::integration_begin, task_const_values::integration_end, task_const_values::F)) << endl;

	cout << "Абсолютная погрешность (n = 50): " << fabs(right_rectangle_method(task_const_values::integration_begin, task_const_values::integration_end, 50)
		- newton_method(task_const_values::integration_begin, task_const_values::integration_end, task_const_values::F)) << endl;

	cout << "Абсолютная погрешность (n = 100): " << fabs(right_rectangle_method(task_const_values::integration_begin, task_const_values::integration_end, 100)
		- newton_method(task_const_values::integration_begin, task_const_values::integration_end, task_const_values::F)) << endl << endl;
}

void lab5::lab(void) 
{
	cout << endl << "Ньютона-Лейбница: " << newton_method(task_const_values::integration_begin,
		task_const_values::integration_end, task_const_values::F0) << endl;

	task1::run();
	task2::run();
	task3::run();
	task4::run();
	task5::run();
}