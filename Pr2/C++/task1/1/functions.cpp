#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
#include "header.h"

using namespace std;

int fastExponentiationMod(int base, int exponent, int modulus) {
    int reducedExponent = exponent % (modulus - 1);
    int result = 1;
    for(int i = 1; i <= reducedExponent; i++) {
        result = (result * base) % modulus;
    }
    return result;
}

int gcd(int a, int b) {
    while(b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

template<typename T>
bool fermatsTest(T primeCandidate, T& testCount) {
    if(primeCandidate <= 1 || (primeCandidate % 2 == 0 && primeCandidate != 2)) {
        return false;
    }
    vector<int> testBases = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    if(testCount > static_cast<int>(testBases.size())) {
        testCount = testBases.size();
    }
    for(int i = 0; i < testCount; i++) {
        T currentBase = testBases[i];
        if(currentBase >= primeCandidate) continue;
        if(gcd(primeCandidate, currentBase) != 1) {
            return false;
        }
        if(fastExponentiationMod(currentBase, primeCandidate-1, primeCandidate) != 1) {
            return false;
        }
    }
    return true;
}

bool isPrime(int number) {
    if(number <= 1 || number % 2 == 0 || number % 3 == 0) {
        return false;
    }
    int sqrtNum = static_cast<int>(sqrt(number)) + 1;
    int maxDivisor = (sqrtNum + 1) / 6;
    for(int i = 1; i < maxDivisor; i++) {
        int divisor1 = 6 * i - 1;
        int divisor2 = 6 * i + 1;
        if(divisor1 <= sqrtNum && number % divisor1 == 0) return false;
        if(divisor2 <= sqrtNum && number % divisor2 == 0) return false;
    }
    return true;
}

void runTests() {
    assert(fastExponentiationMod(3, 100, 7) == 4);
    assert(gcd(1234, 54) == 2);
    assert(isPrime(23));
}

bool validateModulus(int modulus, int testCount) {
    if(!isPrime(modulus)) {
        cerr << "Модуль не является простым числом." << endl;
        return false;
    }
    if(!fermatsTest(modulus, testCount)) {
        cerr << "Модуль не удовлетворяет тесту Ферма." << endl;
        return false;
    }
    return true;
}
