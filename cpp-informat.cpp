#include <iostream>
#include <locale>

import lab6_module;
using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");
    lab6::run_calculator();

    return 0;
}