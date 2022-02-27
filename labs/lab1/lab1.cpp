#include "lab1.h"

void lab1::task1::run(void)
{
    cout << fixed;
    cout.precision(8);

    // �������� ������ ��� ������� �1
    const double a1 = 16. / 19., a2 = 0.842;
    const double b1 = sqrt(55), b2 = 7.416;

    cout << "\t" << "1) 16 / 19 = 0.842" << endl
        << "\t" << "2) sqrt(55) = 7.416" << endl << endl;

    cout << "\t" << "������ ��������:" << endl
        << "\t" << "1) " << a1 << endl
        << "\t" << "2) " << b1 << endl << endl;

    // ������ ���������� ������������ ��� ���� �������
    double a_absolute_error = fabs(a1 - a2), b_absolute_error = fabs(b1 - b2);

    cout << "\t" << "���������� �����������: " << endl
        << "\t" << "1) " << a_absolute_error << endl
        << "\t" << "2) " << b_absolute_error << endl << endl;

    // ������ ������������� ������������ ��� ���� �������
    double a_relatively_error = a_absolute_error / fabs(a2) * 100,
        b_relatively_error = b_absolute_error / fabs(b2) * 100;

    cout << "\t" << "������������� �����������: " << endl
        << "\t" << "1) " << a_relatively_error << "%" << endl
        << "\t" << "2) " << b_relatively_error << "%" << endl << endl;

    // ����������� ����� ������� ��������� �� ������ ������������� �����������
    cout << "\t" << "����� ������ ���������: " << ((a_relatively_error < b_relatively_error) ?
        "16 / 19 = 0.842" : "sqrt(55) = 7.416") << endl;
}

// ������������ ���������� ���� ����� �������
#define MAXIMUM_DIGITS_DECIMAL 20

void lab1::task2::run(void)
{
    // �������� ������ ��� ������� �2
    const double x = 17.356, relatively_error = 0.11;
    // ���������� ���������� �����������
    const double absolute_error = relatively_error / 100 * x;

    cout << fixed;
    cout.precision(4);

    cout << "\t" << "�������� ��������: " << x << endl << endl;
    cout << "\t" << "������������� ����������� ������������ ��������: " << relatively_error << "%" << endl;
    cout << "\t" << "���������� ����������� ������������ ��������: " << absolute_error << endl << endl;

    // decimal_part - ���������� ��� �������� ����� � ������� �������
    // result_x - ���������� ��� �������� ������������ �����
    double decimal_part = 0, result_x = 0;
    for (int i = 0; i < MAXIMUM_DIGITS_DECIMAL; i++)
    {
        // �������� �� �������� �������� ���������� ������� (i) ����� �������
        if (pow(10, -i) < absolute_error)
        {
            // ����� ����� ����� ��������� ����� � ����������� ������� �����
            result_x = int(x) + decimal_part;
            break;
        }
        // ������ �������� ����������� ������� � ���������� � ����������� ������� ����� ����������
        decimal_part += int(double(x - int(x)) / pow(10, -i)) % 10 * pow(10, -i);
    }

    cout << "\t" << "���������: " << result_x << endl;
    cout << "\t" << "���������� ����������� ����������: " << fabs(result_x - x) << endl;
}

void lab1::task3::run(void)
{
    // �������� ������ ��� ������� �3
    const double x = 0.5718, decimal_digit = 4;
    cout << fixed;
    cout.precision(5);

    // ���������� ���������� � ������������� �����������.
    // (����� ���������� ���������� ����������� �� �������, �� ��� ���������� 
    // �������� ������� ���������� ����������� �������. )
    const double absolute_error = pow(10, -decimal_digit) / 2;
    const double relative_error = absolute_error / x * 100;

    cout << "\t" << "�������� ��������: " << x << endl;
    cout << "\t" << "���������� ����������� ����������: " << absolute_error << endl;
    cout << "\t" << "������������� ����������� ����������: " << relative_error << "%" << endl;
}

void lab1::lab(void) 
{
    cout << "������� 1: " << endl;
    // ������ ��������� ��� ������� ������� �1
    task1::run();
    cout << endl << endl;

    cout << "������� 2: " << endl;
    // ������ ��������� ��� ������� ������� �2
    task2::run();
    cout << endl << endl;

    cout << "������� 3: " << endl;
    // ������ ��������� ��� ������� ������� �3
    task3::run();
    cout << endl << endl;
}