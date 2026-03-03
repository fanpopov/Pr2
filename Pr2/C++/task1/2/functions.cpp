#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cassert>
#include "header.h"

using namespace std;

bool isPrime(int number) {
    if (number <= 1 || number % 2 == 0 || number % 3 == 0) {
        return false;
    }
    int sqrtNum = static_cast<int>(sqrt(number)) + 1;
    int maxDivisor = (sqrtNum + 1) / 6;
    for(int i = 1; i < maxDivisor; i++) {
        int divisor1 = 6 * i - 1;
        int divisor2 = 6 * i + 1;
        if (divisor1 <= sqrtNum && number % divisor1 == 0) return false;
        if (divisor2 <= sqrtNum && number % divisor2 == 0) return false;
    }
    return true;
}

int simpleModularExponentiation(int base, int exponent, int modulus) {
    exponent = exponent % (modulus - 1);
    if(exponent == 0) return 1;
    int result = 1;
    for(int i = 0; i < exponent; i++) {
        result = (result * base) % modulus;
    }
    return result;
}

vector<bool> convertToBinary(int number) {
    vector<bool> binaryDigits;
    while (number > 0) {
        binaryDigits.push_back(number % 2);
        number /= 2;
    }
    return binaryDigits;
}

int binaryModularExponentiation(int base, int exponent, int modulus) {
    if (modulus == 1) return 0;
    base %= modulus;
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}

int fastModularExponentiation(int base, int exponent, int modulus) {
    if (exponent == 0) return 1 % modulus;
    if (modulus == 1) return 0;
    int bitsNeeded = static_cast<int>(ceil(log2(exponent))) + 1;
    vector<int> powerTable(bitsNeeded);
    powerTable[0] = base % modulus;
    for (int i = 1; i < bitsNeeded; ++i) {
        powerTable[i] = (powerTable[i-1] * powerTable[i-1]) % modulus;
    }
    vector<bool> binaryExponent = convertToBinary(exponent);
    int result = 1;
    for (size_t i = 0; i < binaryExponent.size(); ++i) {
        if (binaryExponent[i]) {
            result = (result * powerTable[i]) % modulus;
        }
    }
    return result;
}

int computeGCD(int a, int b) {
    while (b != 0) {
        int remainder = b;
        b = a % b;
        a = remainder;
    }
    return a;
}

template<typename T>
bool performFermatTest(T candidate, T& testLimit) {
    if(candidate <= 1 || (candidate % 2 == 0 && candidate != 2)) {
        return false;
    }
    const vector<int> testBases = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    testLimit = min(testLimit, static_cast<T>(testBases.size()));
    for(int i = 0; i < testLimit; i++) {
        int base = testBases[i];
        if(base >= candidate) continue;
        if(computeGCD(candidate, base) != 1) {
            return false;
        }
        if(simpleModularExponentiation(base, candidate-1, candidate) != 1) {
            return false;
        }
    }
    return true;
}

bool validateModulus(int modulus, int testCount) {
    if(!isPrime(modulus)) {
        cerr << "Ошибка: Модуль должен быть простым числом!" << endl;
        exit(1);
    }
    if(!performFermatTest(modulus, testCount)) {
        cerr << "Ошибка: Модуль не прошел тест Ферма!" << endl;
        exit(1);
    }
    return true;
}

void runAllTests() {
    assert(fastModularExponentiation(3, 13, 7) == 3);
    assert(fastModularExponentiation(5, 13, 7) == 5);
    assert(fastModularExponentiation(5, 0, 7) == 1);
    assert(fastModularExponentiation(3, 100, 7) == 4);
    assert(fastModularExponentiation(3, 1, 7) == 3);
}
