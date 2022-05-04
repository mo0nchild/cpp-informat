#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

namespace lab5
{
	using namespace std;

	namespace task_const_values 
	{
		const double integration_begin = 0.6, integration_end = 2;
		double F(const double x);
		double F0(const double x);
	}

	double newton_method(double a, double b, double (*func)(double x));

	namespace task1
	{
		double rectangle_method(double a, double b, const int n);
		void run(void);
	}

	namespace task2
	{
		double trapezoid_method(double a, double b, const int n);
		void run(void);
	}

	namespace task3
	{
		double parabola_method(double a, double b, const int n);
		void run(void);
	}

	namespace task4 
	{
		double left_rectangle_method(double a, double b, const int n);
		void run(void);
	}

	namespace task5
	{
		double right_rectangle_method(double a, double b, const int n);
		void run(void);
	}

	void lab(void);
}