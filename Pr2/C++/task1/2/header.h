#pragma once
#include <vector>

using namespace std;

bool isPrime(int number);
int simpleModularExponentiation(int base, int exponent, int modulus);
vector<bool> convertToBinary(int number);
int binaryModularExponentiation(int base, int exponent, int modulus);
int fastModularExponentiation(int base, int exponent, int modulus);
int computeGCD(int a, int b);
template<typename T> bool performFermatTest(T candidate, T& testLimit);
bool validateModulus(int modulus, int testCount);
void runAllTests();
