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
	
	cout << "[ Вычисление при помощи Матричного Метода ]" << endl << "[ ";
	for (int16_t i = 0; i < method_result->size(); i++) cout << "x" << to_string(i + 1) << " = " << (*method_result)[i] << "; ";
	cout << "]" << endl;

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

	cout << "[ Вычисление при помощи Метода Гауса ]" << endl << "[ ";
	for (int16_t i = 0; i < method_result->size(); i++) cout << "x" << to_string(i + 1) << " = " << (*method_result)[i] << "; ";
	cout << "]" << endl;

	if (method_result_check(task_const_values::matrix, task_const_values::stripe, *method_result))
	{ cout << "Вывод: Уравнение решено верно" << endl << endl; }
	else { cout << "Вывод: Уравнение решено неверно" << endl << endl; }

	delete method_result;
}

IterationResult* task3::jacobi_method(SquareMatrix matrix, std::vector<double> stripe, double esp)
{
	const int column_size = matrix.size() + 1, row_size = matrix.size();
	matrix_t value_array;

	for (uint16_t i = 0; i < stripe.size(); i++)
	{
		value_array.push_back(std::vector<double>{});

		for (uint16_t j = 0; j < stripe.size(); j++) value_array[i].push_back(matrix.get_cell(j, i));
		value_array[i].push_back(stripe[i]);
	}

	for (uint16_t row = 0; row < matrix.size() - 1; row++)
	{
		for (uint16_t col = row + 1; col < matrix.size(); col++)
		{
			const double S = value_array[col][row] / value_array[row][row];
			for (uint16_t j = 0; j <= matrix.size(); j++)
			{ value_array[col][j] = value_array[col][j] - S * value_array[row][j]; }
		}
	}

	std::vector<double> current_value_list(stripe.size(), 0);
	matrix_t iter_storing;

	for(uint16_t iter = 0; true; iter++)
	{
		std::vector<double> new_value_list(stripe.size(), 0);
		iter_storing.push_back(vector<double>{});

		for (uint16_t i = 0; i < stripe.size(); i++)
		{
			new_value_list[i] = value_array[i][stripe.size()];
			for (uint16_t j = 0; j < stripe.size(); j++)
			{
				if (i != j) new_value_list[i] -= value_array[i][j] * current_value_list[j];
			}
			new_value_list[i] /= value_array[i][i];
			iter_storing[iter].push_back(new_value_list[i]);
		}
		double failing_value(0);
		for (uint16_t i = 0; i < stripe.size(); i++) failing_value += std::fabs(new_value_list[i] - current_value_list[i]);
		if (failing_value < esp) return new IterationResult(iter_storing, current_value_list);
		current_value_list = new_value_list;
	}
}

void print_iteration_table(IterationResult* method_result) 
{
	lab4::matrix_t iter_items = method_result->get_iter();
	auto draw_horiz_stripe = [&](void) -> void
	{
		for (int16_t i = 0; i < method_result->get_size(); i++) { cout << "------------------"; }
		cout << endl;
	};
	cout << endl;
	draw_horiz_stripe();
	cout << "i" << setw(10);
	for (int16_t i = 0; i < method_result->get_size(); i++)
	{
		cout << "x" << to_string(i + 1);
		if (i != method_result->get_size() - 1) cout << setw(20);
	}
	cout << endl;
	draw_horiz_stripe();

	for (uint16_t y = 0; y < iter_items.size(); y++) 
	{
		cout << y << setw(10);
		for (int16_t x = 0; x < method_result->get_size(); x++) 
		{
			cout << iter_items[y][x];
			if (x != method_result->get_size() - 1) cout << setw(20);
		}
		cout << endl << endl;;
	}
	draw_horiz_stripe();
	cout << endl;
}

void task3::run(const double ESP)
{
	IterationResult* method_result = jacobi_method(task_const_values::matrix, task_const_values::stripe, ESP);
	if (method_result == nullptr) { cout << "Произошла ошибка в вычислениях" << endl; return; }

	cout << "[ Вычисление при помощи Метода простых итераций (Якоби) (ESP = " + to_string(ESP) + " ) ]" << endl << "[ ";
	for (int16_t i = 0; i < method_result->get_size(); i++) cout << "x" << to_string(i + 1) << " = " << method_result->get_result(i) << "; ";
	cout << "]" << endl;

	std::vector<double> results;
	for (uint16_t i = 0; i < method_result->get_size(); i++) results.push_back(method_result->get_result(i));

	if (method_result_check(task_const_values::matrix, task_const_values::stripe, results))
	{ cout << "Вывод: Уравнение решено верно" << endl << endl; }
	else { cout << "Вывод: Уравнение решено неверно" << endl << endl; }

	print_iteration_table(method_result);

	delete method_result;
}

IterationResult* task4::zeidel_method(SquareMatrix matrix, std::vector<double> stripe, double esp)
{
	std::vector<vector<double>> value_array(matrix.size(), std::vector<double>{});
	const uint16_t size = stripe.size();

	for (uint16_t array_index = 0; array_index < matrix.size(); array_index++)
	{
		for (uint16_t k = 0; k < stripe.size(); k++)
			value_array[array_index].push_back(matrix.get_cell(k, array_index));
		value_array[array_index].push_back(stripe[array_index]);
	}

	for (int16_t y = 0; y < size - 1; y++)
	{
		for (int16_t x = y + 1; x < size; x++)
		{
			const float result_value_1 = value_array[x][y], result_value_2 = value_array[y][y];
			for (int16_t index = 0; index <= size; ++index)
			{
				value_array[x][index] = value_array[x][index] - (result_value_1 / result_value_2) 
					* value_array[y][index];
			}
		}
	}
	std::vector<double> last_mass(size, 0), now_mass(size, 0);
	std::vector<vector<double>> iter_storing;

	uint16_t iter(0); do {
		iter_storing.push_back(std::vector<double>{});
		for (int y_index = 0; y_index < size; y_index++)
		{
			now_mass[y_index] = value_array[y_index][size];
			for (int x_index = 0; x_index < size; x_index++)
			{
				if (y_index == x_index) continue;
				now_mass[y_index] -= value_array[y_index][x_index] * last_mass[x_index];
			}
			now_mass[y_index] /= value_array[y_index][y_index];
			iter_storing[iter].push_back(now_mass[y_index]);
		}	++iter;
		if (fabs(now_mass[0] - last_mass[0]) < esp) 
			return new IterationResult(iter_storing, last_mass);
		last_mass = now_mass;	
	} while (true);
}

void task4::run(const double ESP)
{
	IterationResult* method_result = zeidel_method(task_const_values::matrix, task_const_values::stripe, ESP);
	if (method_result == nullptr) { cout << "Произошла ошибка в вычислениях" << endl; return; }

	cout << "[ Вычисление при помощи Метода Зейделя (ESP = " + to_string(ESP) + " ) ]" << endl << "[";
	for (int16_t i = 0; i < method_result->get_size(); i++) cout << "x" << to_string(i + 1) << " = " << method_result->get_result(i) << "; ";
	cout << "]" << endl;

	std::vector<double> results;
	for (uint16_t i = 0; i < method_result->get_size(); i++) results.push_back(method_result->get_result(i));

	if (method_result_check(task_const_values::matrix, task_const_values::stripe, results))
	{
		cout << "Вывод: Уравнение решено верно" << endl << endl;
	}
	else { cout << "Вывод: Уравнение решено неверно" << endl << endl; }

	print_iteration_table(method_result);

	delete method_result;
}

void lab4::lab(void) 
{
	cout << "===========================[Матричный Метод]===========================" << endl << endl;
	task1::run();
	cout << "===========================[Метод Гаусса]===========================" << endl << endl;
	task2::run();
	cout << "===========================[Метод Якоби]===========================" << endl << endl;
	task3::run(0.01);	task3::run(0.00001);
	cout << "===========================[Метод Зейделя]===========================" << endl << endl;
	task4::run(0.01);	task4::run(0.00001);
}