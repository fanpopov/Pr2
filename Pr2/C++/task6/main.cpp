#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "functions.h"

using namespace std;

int main() {
    srand(time(NULL));

    // Генерация общих параметров
    int p, g;
    do {
        p = rand() % 9000 + 1000;
    } while (!isPrime(p));
    do {
        g = rand() % (p - 1) + 1;
    } while (!is_primitive_root(g, p));

    // Секретные ключи участников
    int a = rand() % (p - 2) + 1; // Алиса
    int b = rand() % (p - 2) + 1; // Боб
    int e = rand() % (p - 2) + 1; // Ева

    // Вычисление открытых ключей
    int A = aXmodP(g, a, p); // A = g^a mod p
    int B = aXmodP(g, b, p); // B = g^b mod p
    int Ae = aXmodP(g, e, p); // A' = g^e mod p (подмена от Евы)
    int Be = aXmodP(g, e, p); // B' = g^e mod p

    // Ева перехватывает A и B, подменяет их на Ae и Be
    // Алиса получает Be вместо B, Боб получает Ae вместо A

    // Вычисление общих ключей
    int K_Alice = aXmodP(Be, a, p); // Алиса думает, что это ключ с Бобом, но это ключ с Евой
    int K_Bob   = aXmodP(Ae, b, p); // Боб думает, что это ключ с Алисой, но это ключ с Евой
    int K_Eve_with_Alice = aXmodP(Be, e, p); // Ева вычисляет ключ с Алисой
    int K_Eve_with_Bob   = aXmodP(Ae, e, p); // Ева вычисляет ключ с Бобом

    // Запись результатов в файл
    ofstream outFile("mitm_output.txt");
    outFile << "Атака Man-in-the-Middle на протокол Диффи-Хеллмана\n";
    outFile << "Параметры: p = " << p << ", g = " << g << "\n\n";
    outFile << "Секретный ключ Алисы: a = " << a << "\n";
    outFile << "Секретный ключ Боба  : b = " << b << "\n";
    outFile << "Секретный ключ Евы   : e = " << e << "\n\n";
    outFile << "Открытый ключ Алисы (A) = " << A << "\n";
    outFile << "Открытый ключ Боба  (B) = " << B << "\n";
    outFile << "Подменённый ключ от Евы (A') = " << Ae << "\n";
    outFile << "Подменённый ключ от Евы (B') = " << Be << "\n\n";
    outFile << "Ключ, вычисленный Алисой (K_Alice) = " << K_Alice << "\n";
    outFile << "Ключ, вычисленный Бобом   (K_Bob)   = " << K_Bob << "\n";
    outFile << "Ключ Евы с Алисой = " << K_Eve_with_Alice << "\n";
    outFile << "Ключ Евы с Бобом   = " << K_Eve_with_Bob << "\n\n";
    if (K_Alice == K_Eve_with_Alice && K_Bob == K_Eve_with_Bob) {
        outFile << "Атака успешна: Ева имеет общие ключи с Алисой и Бобом.\n";
    } else {
        outFile << "Ошибка атаки.\n";
    }
    outFile.close();

    cout << "Результаты атаки записаны в mitm_output.txt\n";
    return 0;
}
