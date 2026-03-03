#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "functions.h"

using namespace std;

int main() {
    srand(time(NULL));

    // Генерация параметров для Диффи-Хеллмана
    int p, g, a, b, A, B, K1, K2;

    // Генерация большого простого числа p
    do {
        p = rand() % 9000 + 1000;
    } while (!isPrime(p));

    // Генерация примитивного корня g по модулю p
    do {
        g = rand() % (p - 1) + 1;
    } while (!is_primitive_root(g, p));

    // Секретные ключи Алисы и Боба
    a = rand() % (p - 2) + 1; // 1 < a < p-1
    b = rand() % (p - 2) + 1; // 1 < b < p-1

    // Вычисление открытых ключей
    A = aXmodP(g, a, p);
    B = aXmodP(g, b, p);

    // Вычисление общего секретного ключа
    K1 = aXmodP(B, a, p);
    K2 = aXmodP(A, b, p);

    // Проверка, что ключи совпали
    if (K1 != K2) {
        cerr << "Ошибка: ключи не совпали!" << endl;
        return 1;
    }

    // Запись результатов в файл
    ofstream outFile("output.txt");
    outFile << "Параметры Диффи-Хеллмана:" << endl;
    outFile << "p = " << p << endl;
    outFile << "g = " << g << endl << endl;
    outFile << "Секретный ключ Алисы (a) = " << a << endl;
    outFile << "Открытый ключ Алисы (A) = " << A << endl << endl;
    outFile << "Секретный ключ Боба (b) = " << b << endl;
    outFile << "Открытый ключ Боба (B) = " << B << endl << endl;
    outFile << "Общий секретный ключ (K) = " << K1 << endl;
    outFile.close();

    cout << "Результаты записаны в output.txt" << endl;
    return 0;
}
