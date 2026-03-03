#include <iostream>
#include "header.h"

using namespace std;

int main() {
    runTests();
    int base1, exponent1;
    cout << "Введите первое число и его степень через пробел: ";
    cin >> base1 >> exponent1;
    int base2, exponent2;
    cout << "Введите второе число и его степень через пробел: ";
    cin >> base2 >> exponent2;
    int modulus, testCount;
    cout << "Введите модуль: ";
    cin >> modulus;
    cout << "Введите количество проверок для теоремы Ферма: ";
    cin >> testCount;
    if(!isPrime(modulus)) {
        cout << endl << "Модуль не является простым числом, попробуйте другой. Модуль обязательно должен быть > 0!" << endl;
        return 0;
    }
    if(!fermatsTest(modulus, testCount)) {
        cout << endl << "Модуль не удовлетворяет условию Ферма, попробуйте другой." << endl;
        return 0;
    }
    int result1 = fastExponentiationMod(base1, exponent1, modulus);
    int result2 = fastExponentiationMod(base2, exponent2, modulus);
    if(result1 == result2) {
        cout << base1 << "^" << exponent1 << " mod " << modulus << " = "
             << base2 << "^" << exponent2 << " mod " << modulus << endl;
    } else {
        cout << base1 << "^" << exponent1 << " mod " << modulus << " != "
             << base2 << "^" << exponent2 << " mod " << modulus << endl;
    }
}
