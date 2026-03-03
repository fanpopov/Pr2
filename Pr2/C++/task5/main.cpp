#include <iostream>
#include <vector>

using namespace std;

// Функция для вычисления цепной дроби
vector<int> continued_fraction(int a, int b) {
    vector<int> coefficients;
    while (b != 0) {
        int q = a / b;
        coefficients.push_back(q);
        int r = a % b;
        a = b;
        b = r;
    }
    return coefficients;
}

// Функция вычисления НОД (алгоритм Евклида)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Функция для вывода компактного решения
void print_compact_solution(int x0, int a_coef, int y0, int b_coef) {
    cout << "\nКомпактная форма общего решения:\n";
    cout << "a = " << x0 << " + " << b_coef << " * k\n";
    cout << "b = " << y0 << " - " << a_coef << " * k\n";
    cout << "где k - любое целое число\n";
}

// Функция решения диофантова уравнения ax + by = c
void solve_diophantine(int a, int b, int c) {
    cout << "Решаем уравнение: " << a << "a + " << b << "b = " << c << endl;

    // Проверяем, существует ли решение
    int d = gcd(a, b);
    if (c % d != 0) {
        cout << "Нет решения, так как " << c << " не делится на НОД("
             << a << ", " << b << ") = " << d << endl;
        return;
    }

    // Масштабируем коэффициенты, если НОД не равен 1
    if (d != 1) {
        a /= d;
        b /= d;
        c /= d;
        cout << "Упрощаем уравнение: " << a << "a + " << b << "b = " << c << endl;
    }

    // Вычисляем цепную дробь
    vector<int> cf = continued_fraction(a, b);

    // Находим решение с помощью подходящих дробей
    int x_prev = 1, x = 0;
    int y_prev = 0, y = 1;

    for (int q : cf) {
        int x_temp = x;
        x = x_prev - q * x;
        x_prev = x_temp;

        int y_temp = y;
        y = y_prev - q * y;
        y_prev = y_temp;
    }

    // Частное решение
    int x0 = x_prev * c;
    int y0 = y_prev * c;

    cout << "\nОдно из частных решений:\n";
    cout << "a = " << x0 << ", b = " << y0 << endl;

    // Общее решение
    cout << "\nОбщее решение:\n";
    cout << "a = " << x0 << " + " << b << " * k\n";
    cout << "b = " << y0 << " - " << a << " * k\n";
    cout << "где k - любое целое число\n";

    // Компактное решение
    print_compact_solution(x0, a, y0, b);

    // Проверка решения
    cout << "\nПроверка решения: ";
    cout << a << "*" << x0 << " + " << b << "*" << y0 << " = "
         << (a*x0 + b*y0) << endl;
}

int main() {
    // Решаем уравнение 143a + 169b = 5
    solve_diophantine(143, 169, 5);
    return 0;
}
