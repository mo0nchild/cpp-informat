#include <iostream>
#include <locale>
#include <cmath>
#include <cstdio>
#include <string>

using namespace std;

#define MATH_E 2.7182818284

namespace lab2
{
	using namespace std;

	struct function_result_t
	{
		// количество слагаемых для достижения погрешности
		uint16_t iter_count;
		// результат вычисления
		double result;

		function_result_t() = delete;
		function_result_t(uint16_t iter_count, double result)
			: iter_count(iter_count), result(result)
		{ }
	};
	function_result_t my_sin(double x, double e);

	namespace task1 { void run(void); }

	namespace task2 { void run(void); }

	namespace task3 { void run(void); }

	namespace task4 { void run(void); }

	namespace task5 { void run(void); }

	void lab(void);
}