#include <iostream>
#include "EquationSolver.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(65001); 
    EquationSolver solver; //створюється об'єкт класу який містить методи для розв'язання рівнянь.
    solver.setInterval(0, 0.8);  // Тепер проміжок [0, 0.8]
    solver.setTolerance(1e-6);

    std::cout << "f(a) = " << solver.function(0) << ", f(b) = " << solver.function(0.8) << std::endl; //виведення значення проміжку 0  і 0.8

    double root_bisect, root_newton; //змінні, у яких будуть збережені корені, знайдені методом дихотомії та методом Ньютона.

    if (solver.bisection(root_bisect) == 0)
        std::cout << "Метод дихотомії: x = " << root_bisect << std::endl;

    if (solver.newton(root_newton) == 0)
        std::cout << "Метод Ньютона: x = " << root_newton << std::endl;

    return 0;
}

