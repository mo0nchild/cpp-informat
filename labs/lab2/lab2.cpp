#include "lab2.h"

lab2::function_result_t lab2::my_sin(double x, double e)
{
    // анонимная функция для вычисления факториала.
    auto factorial = [](int x) -> double
    {
        double result = 1;
        for (int i = 1; i <= x; i++) result *= i;
        return result;
    };

    // переменная для хранения вычисленного значения функции.
    double result = 0;
    for (int k = 1; true; k++)
    {
        // расчет слагаемого (k)
        double iter = (pow(-1., k + 1) * pow(x, 2 * k - 1)) / factorial(2 * k - 1);
        // проверка условия погрешности.
        if (fabs(iter) < e)
        {
            return lab2::function_result_t(k - 1, result);
        }
        // добавления слагаемого в перемнную
        result += iter;
    }
}

void lab2::task1::run(void) 
{
    // установка константных значений для исходных данных 
    const double xn = 1.1, xk = 10.1, dx = 0.1, E1 = 0.1, E2 = 0.000001;
    cout << "\t" << "xn = " << xn << "\t" << "xk = " << xk << "\t" << "dx = " << dx << endl << endl;

    // формирования шапки таблицы
    printf(
        "\t|%10s|%15s|%10s|%15s|%10s|%10s|%15s|%10s|\n",
        "X", "SIN (CMATH)", "ESP1", "F1 (EPS1)", "COUNT1", "ESP2", "F2 (EPS2)", "COUNT2"
    );
    for (double x = xn; x <= xk; x += dx)
    {
        // вызов метода "my_sin" для двух погрешностей
        const function_result_t func1 = my_sin(x, E1), func2 = my_sin(x, E2);
        const double func = sin(x);

        // вывод текущей строки таблицы
        printf("\t|%10s|%15s|%10s|%15s|%10s|%10s|%15s|%10s|\n",
            to_string(x).c_str(), to_string(func).c_str(),
            to_string(E1).c_str(), to_string(func1.result).c_str(), to_string(func1.iter_count).c_str(),
            to_string(E2).c_str(), to_string(func2.result).c_str(), to_string(func2.iter_count).c_str()
        );
    }
}

void lab2::task2::run(void)
{
    // исходные данные задания
    const double a = 0.10, E = 0.0001;
    // вывод значения правой части равенства lim(x0; x1; x2) = pow(a, 1/3)
    cout << "\t" << "pow(a, 1/3) = " << pow(a, 1. / 3.)
        << "\t" << "E = " << E << endl << endl;

    // вычисление значения левой части равенства lim(x0; x1; x2) = pow(a, 1/3)
    // расчет значения х0
    double x = a / 3;
    for (int n = 0; true; n++)
    {
        // вычисления значения элемента последовательности
        x = 2. / 3. * (x + a / (2. * pow(x, 2)));
        cout << "\t" << x << endl;
        // проверка на соответствие погрешности 
        if (fabs(x - pow(a, 1. / 3.)) < E) break;
    }
    cout << endl << "\t" << "lim = " << x << endl;
}

void lab2::task3::run(void)
{
    // исходные данные задания
    const double n = 6;
    double min = 0;

    cout << "\t" << "Ряд чисел:" << "\t" << "n = " << n << endl << endl;

    for (int k = 1; k <= n; k++)
    {
        // вычисления ждемента ряда
        double iter = pow(k, 3) * sin(n + (double(k) / n));
        cout << "\t" << "\t" << iter << endl;

        // проверка, является ли текущее число наименьшим
        if (iter < min || k == 1) min = iter;
    }

    cout << endl << "\t" << "Минимальное число: " << min << endl;
}

void lab2::task4::run(void)
{
    // исходные данные задания
    const double n = 10;
    double a = 1, b = 1, sum = a * b;

    for (int k = 2; k <= n; k++)
    {
        // копирование предыдущего значения переменной "a"
        double buffer = a;
        // вычисление нового значения "а"
        a = (sqrt(b) + a / 2) / 2;
        // вычисление нового значения "b"
        b = 2 * pow(buffer, 2) + b;

        cout << "\t" << a * b << "\t\tk = " << k << endl;
        // добавление произведения в качестве нового слагаемого
        sum += (a * b);
    }
    cout << endl << "\t" << "n = " << n << "\t"
        << "Сумма ряда = " << sum << endl;
}

void lab2::task5::run(void)
{
    // исходные данные задания
    const double E = 0.001;
    cout << "\t" << "Предел 1 (lim(sin(x)/x) = 1): " << "\t" << "E = " << E << endl;
    for (int i = 0; true; i++)
    {
        // вычисление текущего аргумента функции
        double x = 1. / pow(2, i);
        // вычисление элемента последовательности (левая часть равенства)
        double iter = (sin(x) / x);
        cout << "\t\t" << iter << endl;

        // сравнение отличия левой и правой части равества с погрешностью
        if (fabs(iter - 1) < E) break;
    }
    cout << endl << "\t" << "Предел 2 (lim(1+1/n) = e): " << "\t" << "E = " << E << endl;
    for (int n = 1; true; n++)
    {
        // вычисление элемента последовательности (левая часть равенства)
        double iter = pow(1 + 1. / n, n);

        // сравнение отличия левой и правой части равества с погрешностью
        if (fabs(iter - MATH_E) < E)
        {
            cout << "\t\t" << "n = " << n << "\tlim = " << iter << endl;
            break;
        }
    }
    cout << endl;
}

void lab2::lab(void)
{
    cout << "Задание 1:" << endl;
    task1::run();
    cout << endl;

    cout << "Задание 2:" << endl;
    task2::run();
    cout << endl;

    cout << "Задание 3:" << endl;
    task3::run();
    cout << endl;

    cout << "Задание 4:" << endl;
    task4::run();
    cout << endl;

    cout << "Задание 5:" << endl;
    task5::run();
    cout << endl;
}