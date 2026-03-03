#pragma once

int fastExponentiationMod(int base, int exponent, int modulus);
int gcd(int a, int b);
template<typename T> bool fermatsTest(T primeCandidate, T& testCount);
bool isPrime(int number);
void runTests();
bool validateModulus(int modulus, int testCount);
