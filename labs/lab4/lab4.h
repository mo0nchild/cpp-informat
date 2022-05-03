#pragma once
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

namespace lab4
{
	using namespace std;	
	using matrix_t = std::vector<std::vector<double>>;

	struct SquareMatrix
	{
	private:	matrix_t matrix;
	public:		SquareMatrix(matrix_t matrix) { this->matrix = matrix; };
	public:		SquareMatrix(int size);
		int size() { return matrix.size(); }
		double& get_cell(int x, int y)
		{
			if ((x < matrix.size() && x >= 0) && (y < matrix.size() && y >= 0))
			{ return matrix[y][x]; }
			throw std::out_of_range("indexs_out_of_range");
		}
		static void print_matrix(SquareMatrix& matrix);
	};

	/*	x1=0.0184	x2=1.304	x3=-0.177	*/
	// система уравнений варианта
	namespace task_const_values
	{
		const std::vector<double> stripe = { -3.5, 2.7, 1.9 };
		const SquareMatrix matrix(matrix_t{
			{5.4, -2.3, 3.4},
			{4.2, 1.7, -2.3},
			{3.4, 2.4, 7.3}
		});
	}
	
	namespace math_operation
	{
		// функция транспортирования матрицы
		SquareMatrix transpose(SquareMatrix& matrix);
		// функция нахождения минора матрицы 
		SquareMatrix minor_matrix(SquareMatrix matrix, int x_rm, int y_rm);

		// функция перемножения матрицы и списка 
		std::vector<double> multiply_matrix_to_stripe(SquareMatrix matrix, std::vector<double> stripe);
		// функция нахождения обратной матрицы 
		SquareMatrix* inverse_matrix(SquareMatrix matrix);

		// функция нахождения определителя
		double determinant(SquareMatrix matrix);
	}

#define METHOD_RESULT_CHECK_ESP 0.4

	// функиця проверки решения СЛАУ
	bool method_result_check(SquareMatrix left_origin, std::vector<double> right_origin, std::vector<double> result);

	namespace task1
	{
		vector<double>* matrix_method(SquareMatrix matrix, std::vector<double> stripe);
		void run(void);
	}

	namespace task2
	{
		vector<double>* gauss_method(SquareMatrix matrix, std::vector<double> stripe);
		void run(void);
	}
	
	struct IterationResult 
	{
	private:	const matrix_t iteration_values;
	private:	const std::vector<double> method_result;
	public:
		const int& get_size(void) const noexcept { return this->method_result.size(); }
		const vector<vector<double>>& get_iter(void) const { return iteration_values; }
		const double get_result(int x_index) const
		{
			if (x_index < this->method_result.size() && x_index >= 0) { return method_result[x_index]; }
			throw std::out_of_range("indexs_out_of_range");
		}
	public:
		explicit IterationResult(matrix_t iter, std::vector<double> result)
			: iteration_values(iter), method_result(result) { }
	};

	namespace task3
	{
		IterationResult* jacobi_method(SquareMatrix matrix, std::vector<double> stripe, double esp);
		void run(const double ESP = 0.01);
	}

	namespace task4
	{
		IterationResult* zeidel_method(SquareMatrix matrix, std::vector<double> stripe, double esp);
		void run(const double ESP = 0.01);
	}

	void lab(void);
}