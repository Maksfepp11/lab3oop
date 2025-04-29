#include "EquationSolver.h" 
#include <cmath> // Для математичних операцій (pow, tan, abs)
#include <iostream> // Для введення/виведення в консоль

EquationSolver::EquationSolver() {}
EquationSolver::~EquationSolver() {}

// Метод для встановлення інтервалу
void EquationSolver::setInterval(double vol_a, double vol_b) { //void - нічо неповертає
    a = vol_a;  // Присвоюємо значення a
    b = vol_b;  // Присвоюємо значення b
}

// Метод для встановлення точності
void EquationSolver::setTolerance(double vol_eps) {
    eps = vol_eps;  // Присвоюємо значення точності
}

// Функція для обчислення значення f(x)
double EquationSolver::function(double x) {
    double t = tan(x);
    return t - (pow(t, sqrt(3)) + 1) / (3 + 0.2 * pow(t, sqrt(5)));
}


// Похідна функції f'(x)
double EquationSolver::derivative(double x) {
    double t = tan(x);
    double sec2 = 1 / (cos(x) * cos(x)); // sec^2(x)
    
    double u = pow(t, sqrt(3)) + 1;
    double v = 3 + 0.2 * pow(t, sqrt(5));
    
    double u_prime = sqrt(3) * pow(t, sqrt(3) - 1) * sec2;
    double v_prime = 0.2 * sqrt(5) * pow(t, sqrt(5) - 1) * sec2;
    
    return sec2 - (u_prime * v - u * v_prime) / (v * v);
}


// Метод дихотомії для знаходження кореня
int EquationSolver::bisection(double &x) {
    double a_ = a;  // Копія початкового інтервалу
    double b_ = b;  // Копія кінцевого інтервалу
    double c;  // Перемінна для середини інтервалу

    // Перевірка, чи на проміжку є корінь
    if (function(a_) * function(b_) >= 0) {
        std::cout << "На цьому проміжку немає кореня." << std::endl;  // Якщо немає кореня
        return -1;  // Повертаємо помилку
    }

    // Основний цикл дихотомії
    while ((b_ - a_) > eps) {
        c = (a_ + b_) / 2;  // Обчислюємо середину інтервалу
        if (function(a_) * function(c) < 0)  // Якщо корінь знаходиться ліворуч
            b_ = c;  // Звужуємо інтервал з правого боку
        else  // Якщо корінь знаходиться праворуч
            a_ = c;  // Звужуємо інтервал з лівого боку
    }

    // Присвоюємо результат у змінну x
    x = (a_ + b_) / 2;
    return 0;  // Повертаємо успішний результат
}

// Метод Ньютона для знаходження кореня
int EquationSolver::newton(double &x) {
    double xn = (a + b) / 2;  // Початкова точка (середина інтервалу)
    int maxIter = 1000;  // Максимальна кількість ітерацій
    int iter = 0;  // Лічильник ітерацій

    // Перевірка, чи на проміжку є корінь
    if (function(a) * function(b) >= 0) {
        std::cerr << "На цьому проміжку немає кореня. Метод Ньютона не застосовується." << std::endl;
        return -1;  // Повертаємо помилку
    }

    // Основний цикл методу Ньютона
    while (std::abs(function(xn)) > eps && iter < maxIter) {
        double df = derivative(xn);  // Обчислюємо похідну в точці xn
        if (df == 0) {  // Якщо похідна дорівнює нулю
            std::cerr << "Помилка: похідна = 0. Метод Ньютона не застосовується." << std::endl;
            return -1;  // Повертаємо помилку
        }

        // Обчислюємо наступну точку за формулою Ньютона
        xn = xn - function(xn) / df;
        iter++;  // Збільшуємо лічильник ітерацій
    }

    // Перевищено максимальну кількість ітерацій
    if (iter == maxIter) {
        std::cerr << "Перевищено максимальну кількість ітерацій." << std::endl;
        return -1;  // Повертаємо помилку
    }

    // Присвоюємо результат у змінну x
    x = xn;
    return 0;  // Повертаємо успішний результат
}
