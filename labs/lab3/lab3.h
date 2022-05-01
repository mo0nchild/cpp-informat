#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>

namespace lab3 
{
	using namespace std;

#define BEGIN_SEARCHING -7.
#define MY_EPS 0.001

	double get_func(double x); // функция варианта	
	double get_derivative(double x); // первая производная функции
	double get_derivative2(double x); // вторая производная функции

	namespace isolation_interval 
	{

#define ISOLATION_STEP 0.1
#define ISOLATION_MAX_LENGTH 3
#define ISOLATION_MAX_ITER 12

		using interval_t = pair<double, double>;

		// фукнция для получения интервала изоляции корня от begin
		interval_t get_isolation(double begin);
		 // фукнция для получения множества интервалов изоляции корня от begin
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

	namespace task5 
	{
		pair<double, double>* method_secant(double a, double b);
		void run(void);
	}

	namespace task6
	{
		pair<double, double>* method_combined(double a, double b);
		void run(void);
	}

	void lab(void);
}