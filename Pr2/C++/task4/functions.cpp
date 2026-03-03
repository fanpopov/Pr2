#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>
#include "functions.h"

using namespace std;

// Проверка числа на простоту
bool isPrime(int p) {
    if (p <= 1) return false;
    if (p <= 3) return true;
    if (p % 2 == 0 || p % 3 == 0) return false;
    int sqrtP = static_cast<int>(sqrt(p)) + 1;
    for (int i = 5; i <= sqrtP; i += 6) {
        if (p % i == 0 || p % (i + 2) == 0)
            return false;
    }
    return true;
}

// Наибольший общий делитель
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Возведение в степень по модулю (a^x mod p)
int aXmodP(int a, int x, int p) {
    int result = 1;
    a = a % p;
    while (x > 0) {
        if (x % 2 == 1)
            result = (result * a) % p;
        x = x >> 1;
        a = (a * a) % p;
    }
    return result;
}

// Разложение числа на простые множители
vector<int> prime_factors(int n) {
    vector<int> factors;
    if (n % 2 == 0) {
        factors.push_back(2);
        while (n % 2 == 0) n /= 2;
    }
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 2) factors.push_back(n);
    return factors;
}

// Проверка, является ли g примитивным корнем по модулю p
bool is_primitive_root(int g, int p) {
    if (g == 1) return false;
    if (gcd(g, p) != 1) return false;
    int phi = p - 1;
    vector<int> factors = prime_factors(phi);
    for (int q : factors) {
        if (aXmodP(g, phi / q, p) == 1)
            return false;
    }
    return true;
}
