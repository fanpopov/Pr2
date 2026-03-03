#include <iostream>
using namespace std;

int computeGCD(int a, int b) {
    while (b != 0) {
        int remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

int findModularInverse(int number, int modulus, int printModulus) {
    cout << "------------------------" << endl;
    cout << "Rem\tX\tY\tQuotient" << endl;
    cout << "------------------------" << endl;

    int prevX = 1, currentX = 0;
    int prevY = 0, currentY = 1;
    int remainder = 0, quotient = 0;
    int a = number, b = modulus;

    while (b != 0) {
        remainder = a % b;
        quotient = a / b;

        int newX = prevX - quotient * currentX;
        int newY = prevY - quotient * currentY;

        cout << remainder << "\t" << newX << "\t" << newY << "\t" << quotient << endl;
        cout << "------------------------" << endl;

        a = b;
        b = remainder;
        prevX = currentX;
        currentX = newX;
        prevY = currentY;
        currentY = newY;
    }

    if (prevX < 0) {
        prevX += printModulus;
    }
    return prevX;
}

void checkCoprimality(int gcdResult) {
    if(gcdResult != 1) {
        cerr << "Ошибка: Число и модуль не взаимно просты, обратный элемент не существует." << endl;
        exit(1);
    }
}

int main() {
    int number = 0, modulus = 0;
    cout << "Введите число для нахождения обратного элемента: ";
    cin >> number;
    cout << "Введите модуль: ";
    cin >> modulus;

    checkCoprimality(computeGCD(number, modulus));
    int inverse = findModularInverse(number, modulus, modulus);

    cout << "Обратный элемент = " << inverse << endl;
    cout << number << "^(-1) mod " << modulus << " = " << inverse << endl;
    cout << number << "*" << inverse << " mod " << modulus << " = " << (number * inverse) % modulus << endl;

    return 0;
}
