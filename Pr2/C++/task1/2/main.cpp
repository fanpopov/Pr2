#include <iostream>
#include "header.h"

using namespace std;

int main() {
    runAllTests();
    int base1, exponent1;
    cout << "Введите основание и показатель степени через пробел: ";
    cin >> base1 >> exponent1;
    int base2, exponent2;
    cout << "Введите второе основание и показатель степени через пробел: ";
    cin >> base2 >> exponent2;
    int modulus, testCount;
    cout << "Введите модуль (простое число): ";
    cin >> modulus;
    cout << "Введите количество проверок для теста Ферма: ";
    cin >> testCount;
    validateModulus(modulus, testCount);
    int result1 = fastModularExponentiation(base1, exponent1, modulus);
    int result2 = fastModularExponentiation(base2, exponent2, modulus);
    if(result1 == result2) {
        cout << base1 << "^" << exponent1 << " mod " << modulus << " = "
             << base2 << "^" << exponent2 << " mod " << modulus << endl;
    } else {
        cout << base1 << "^" << exponent1 << " mod " << modulus << " != "
             << base2 << "^" << exponent2 << " mod " << modulus << endl;
    }
}
