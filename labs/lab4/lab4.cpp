#include "lab4.h"

using namespace lab4;

SquareMatrix::SquareMatrix(int size)
{
	for (int i = 0; i < size; i++)
	{
		matrix.push_back(vector<double>());
		for (int k = 0; k < size; k++) matrix[i].push_back(double(0));
	}
}

void SquareMatrix::print_matrix(SquareMatrix& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int k = 0; k < matrix.size(); k++) std::cout << matrix.get_cell(k, i) << "\t";
		std::cout << endl << endl;
	}
}

SquareMatrix math_operation::transpose(SquareMatrix& matrix)
{
	SquareMatrix result(matrix.size());

	for (int y = 0; y < matrix.size(); y++)
	{
		for (int x = 0; x < matrix.size(); x++) result.get_cell(x, y) = matrix.get_cell(y, x);
	}
	return result;
}

SquareMatrix math_operation::minor_matrix(SquareMatrix matrix, int x_rm, int y_rm)
{
	SquareMatrix result(matrix.size() - 1);
	for (int y = 0, result_y = 0; y < matrix.size(); y++)
	{
		if (y == y_rm) continue;
		for (int x = 0, result_x = 0; x < matrix.size(); x++)
		{
			if (x == x_rm) continue;
			result.get_cell(result_x++, result_y) = matrix.get_cell(x, y);
		}
		result_y++;
	}
	return result;
}

double math_operation::determinant(SquareMatrix matrix)
{
	if (matrix.size() <= 2)
	{
		return matrix.get_cell(0, 0) * matrix.get_cell(1, 1)
			- (matrix.get_cell(1, 0) * matrix.get_cell(0, 1));
	}

	double result = 0;
	for (int i = 0; i < matrix.size(); i++)
	{
		SquareMatrix new_matrix = minor_matrix(matrix, i, 0);
		result += (i % 2 == 0 ? 1 : -1) * matrix.get_cell(i, 0) * determinant(new_matrix);
	}
	return result;
}

SquareMatrix* math_operation::inverse_matrix(SquareMatrix matrix)
{
	double det = determinant(matrix);
	if (det == 0) return nullptr;

	SquareMatrix* result = new SquareMatrix(matrix.size());
	matrix = transpose(matrix);

	for (int y = 0; y < result->size(); y++)
	{
		for (int x = 0; x < result->size(); x++)
		{
			result->get_cell(x, y) = pow(-1, x + y) * determinant(minor_matrix(matrix, x, y)) * (1. / det);
		}
	}
	return result;
}

std::vector<double> math_operation::multiply_matrix_to_stripe(SquareMatrix matrix, std::vector<double> stripe)
{
	std::vector<double> result = {};
	if (matrix.size() != stripe.size()) return result;
	
	for (uint16_t i = 0; i < stripe.size(); i++)
	{
		double element(0);
		for (uint16_t j = 0; j < stripe.size(); j++) { element += (matrix.get_cell(j, i) * stripe[j]); }
		result.push_back(element);
	}
	return result;
}

bool lab4::method_result_check(SquareMatrix left_origin, std::vector<double> right_origin, std::vector<double> result)
{
	cout.precision(3);
	cout << fixed << "\n[ Проверка полученных результатов ]" << endl;
	for (uint16_t i = 0; i < right_origin.size(); i++)
	{
		double value(0);
		for (uint16_t j = 0; j < left_origin.size(); j++)
		{
			cout << "( " << left_origin.get_cell(j, i) << " * " << result[j] << " )";
			value += (left_origin.get_cell(j, i) * result[j]);
			if (j != left_origin.size() - 1) cout << " + ";
		}
		cout << " = " << value << "\n[ " << to_string(value) << " = " << to_string(right_origin[i]) << " ]\n" << endl;
		if (fabs(value - right_origin[i]) > METHOD_RESULT_CHECK_ESP) return false;
	}
	return true;
}

vector<double>* task1::matrix_method(SquareMatrix matrix, vector<double> stripe)
{
	vector<double>* method_result = nullptr;
	SquareMatrix* inversed_matrix = math_operation::inverse_matrix(matrix);
	
	vector<double> values = math_operation::multiply_matrix_to_stripe(*inversed_matrix, stripe);
	delete inversed_matrix;
	
	if (values.size() == 0) return nullptr;
	method_result = new vector<double>();

	for (auto item : values) { method_result->push_back(item); }
	return method_result;
}

void task1::run(void) 
{
	auto method_result = matrix_method(task_const_values::matrix, task_const_values::stripe);
	if (method_result == nullptr) { cout << "Произошла ошибка в вычислениях" << endl; return; }

	cout << "[ Вычисление при помощи Матричного Метода ]" << endl;
	cout << "[ x1 = " << (*method_result)[0] << ";\tx2 = " << (*method_result)[1] << ";\tx3 = " << (*method_result)[2] << "; ]\n";
	
	if (method_result_check(task_const_values::matrix, task_const_values::stripe, *method_result))
	{ cout << "Вывод: Уравнение решено верно" << endl << endl; }
	else { cout << "Вывод: Уравнение решено неверно" << endl << endl; }
	
	delete method_result;
}

vector<double>* task2::gauss_method(SquareMatrix matrix, vector<double> stripe) 
{
	vector<double>* method_result = nullptr;
	auto matrix_transformation = [&](int16_t row, int16_t x) -> void
	{
		double subtraction_value = ((matrix.get_cell(x, row + 1) < 0 == matrix.get_cell(x, row) < 0) ? -1 : 1) *
			(matrix.get_cell(x, row + 1) / matrix.get_cell(x, row));
		
		stripe[row + 1] += (stripe[row] * subtraction_value);
		for (uint16_t i = 0; i < matrix.size(); i++)
		{ matrix.get_cell(i, row + 1) += (matrix.get_cell(i, row) * subtraction_value); }
	};
	for (uint16_t j = 0; j < matrix.size(); j++)
	{ for (int16_t i = matrix.size() - 2; i >= j; i--) { matrix_transformation(i, j); } }

	method_result = new vector<double>();
	for (int16_t i = matrix.size() - 1; i >= 0; i--) 
	{
		double result(stripe[i]);
		for (int16_t j = i + 1; j < matrix.size(); j++) 
		{ result -= (matrix.get_cell(j, i) * (*method_result)[matrix.size() - j - 1]); }
		
		result /= matrix.get_cell(i, i);
		method_result->push_back(result); 
	}
	std::reverse(method_result->begin(), method_result->end());
	return method_result;
}

void task2::run(void)
{
	auto method_result = gauss_method(task_const_values::matrix, task_const_values::stripe);
	if (method_result == nullptr) { cout << "Произошла ошибка в вычислениях" << endl; return; }

	cout << "[ Вычисление при помощи Метода Гауса ]" << endl;
	cout << "[ x1 = " << (*method_result)[0] << ";\tx2 = " << (*method_result)[1] << ";\tx3 = " << (*method_result)[2] << "; ]\n";

	if (method_result_check(task_const_values::matrix, task_const_values::stripe, *method_result))
	{ cout << "Вывод: Уравнение решено верно" << endl << endl; }
	else { cout << "Вывод: Уравнение решено неверно" << endl << endl; }

	delete method_result;
}

void lab4::lab(void) 
{
	task1::run();
	task2::run();
}