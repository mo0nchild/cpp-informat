#include "lab1.h"

void lab1::task1::run(void)
{
    cout << fixed;
    cout.precision(8);

    // исходные данные для задания №1
    const double a1 = 16. / 19., a2 = 0.842;
    const double b1 = sqrt(55), b2 = 7.416;

    cout << "\t" << "1) 16 / 19 = 0.842" << endl
        << "\t" << "2) sqrt(55) = 7.416" << endl << endl;

    cout << "\t" << "Точные знаяения:" << endl
        << "\t" << "1) " << a1 << endl
        << "\t" << "2) " << b1 << endl << endl;

    // расчёт абсолютных погрешностей для двух случаев
    double a_absolute_error = fabs(a1 - a2), b_absolute_error = fabs(b1 - b2);

    cout << "\t" << "Абсолютная погрешность: " << endl
        << "\t" << "1) " << a_absolute_error << endl
        << "\t" << "2) " << b_absolute_error << endl << endl;

    // расчёт относительных погрешностей для двух случаев
    double a_relatively_error = a_absolute_error / fabs(a2) * 100,
        b_relatively_error = b_absolute_error / fabs(b2) * 100;

    cout << "\t" << "Относительная погрешность: " << endl
        << "\t" << "1) " << a_relatively_error << "%" << endl
        << "\t" << "2) " << b_relatively_error << "%" << endl << endl;

    // определение более точного выражения по основе относительной погрешности
    cout << "\t" << "Более точное равенство: " << ((a_relatively_error < b_relatively_error) ?
        "16 / 19 = 0.842" : "sqrt(55) = 7.416") << endl;
}

// максимальное количество цифр после запятой
#define MAXIMUM_DIGITS_DECIMAL 20

void lab1::task2::run(void)
{
    // исходные данные для задания №2
    const double x = 17.356, relatively_error = 0.11;
    // вычисление абсолютной погрешности
    const double absolute_error = relatively_error / 100 * x;

    cout << fixed;
    cout.precision(4);

    cout << "\t" << "Исходное значение: " << x << endl << endl;
    cout << "\t" << "Относительная погрешность изначального значения: " << relatively_error << "%" << endl;
    cout << "\t" << "Абсолютная погрешность изначального значения: " << absolute_error << endl << endl;

    // decimal_part - переменная для хранения части с верными знаками
    // result_x - переменная для хранения округленного числа
    double decimal_part = 0, result_x = 0;
    for (int i = 0; i < MAXIMUM_DIGITS_DECIMAL; i++)
    {
        // проверка на верность текущего выбранного разряда (i) после запятой
        if (pow(10, -i) < absolute_error)
        {
            // сумма целой части исходного числа и расчитанной дробной части
            result_x = int(x) + decimal_part;
            break;
        }
        // расчет текущего подходящего разряда и добавление в расчитанную дробную части результата
        decimal_part += int(double(x - int(x)) / pow(10, -i)) % 10 * pow(10, -i);
    }

    cout << "\t" << "Результат: " << result_x << endl;
    cout << "\t" << "Абсолютная погрешность результата: " << fabs(result_x - x) << endl;
}

void lab1::task3::run(void)
{
    // исходные данные для задания №3
    const double x = 0.5718, decimal_digit = 4;
    cout << fixed;
    cout.precision(5);

    // вычисление абсолютной и относительной погрешности.
    // (когда предельная абсолютная погрешность не указана, то она составляет 
    // половину единицы последнего выписанного разряда. )
    const double absolute_error = pow(10, -decimal_digit) / 2;
    const double relative_error = absolute_error / x * 100;

    cout << "\t" << "Исходное значение: " << x << endl;
    cout << "\t" << "Абсолютная погрешность результата: " << absolute_error << endl;
    cout << "\t" << "Относительная погрешность результата: " << relative_error << "%" << endl;
}

void lab1::lab(void) 
{
    cout << "Задание 1: " << endl;
    // запуск процедуры для решения задания №1
    task1::run();
    cout << endl << endl;

    cout << "Задание 2: " << endl;
    // запуск процедуры для решения задания №2
    task2::run();
    cout << endl << endl;

    cout << "Задание 3: " << endl;
    // запуск процедуры для решения задания №3
    task3::run();
    cout << endl << endl;
}