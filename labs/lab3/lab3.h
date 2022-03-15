#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>

namespace lab3 
{
	using namespace std;

	//x3 – 3 * x + 1 = 0
	//double get_func(double x) { return pow(log(x), 2) + 0.25 * x - 3; }
	//double get_derivative(double x) { return 2 * log(x) / x + 0.25; }
	//double get_derivative2(double x) { return 2 * (-log(x) + 1) / pow(x, 2); }

	double get_func(double x);
	double get_derivative(double x);
	double get_derivative2(double x);

	namespace isolation_interval 
	{

#define ISOLATION_STEP 0.1
#define ISOLATION_MAX_LENGTH 3
#define ISOLATION_MAX_ITER 12

		using interval_t = pair<double, double>;

		interval_t get_isolation(double begin);
		vector<interval_t> get_isolation_list(double begin);
	}

	namespace task1 
	{
		pair<double, double>* method_dichotomies(double a, double b);
		void run(void);
	}

	namespace task2
	{
		pair<double, double>* method_chord(double a, double b);
		void run(void);
	}

	namespace task3
	{
		pair<double, double>* method_newton(double a, double b);
		void run(void);
	}

	namespace task4
	{
		pair<double, double>* method_iterations(double a, double b);
		void run(void);
	}

	void lab(void);
}