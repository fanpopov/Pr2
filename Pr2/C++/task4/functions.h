#pragma once
#include <vector>
#include <string>
#include <fstream>

using namespace std;

bool isPrime(int p);
int gcd(int a, int b);
int aXmodP(int a, int x, int p);
vector<int> prime_factors(int n);
bool is_primitive_root(int g, int p);
