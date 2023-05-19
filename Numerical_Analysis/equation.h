#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <string>

using namespace std;

const long double E = 2.7182818284;
const long double PI = atan(1) * 4;
const long double ZERO_LIMIT = 0;
const long double EPSILON = 1.0E-5;
const int MAX_ITERATION = 1000;

int signum(long double x);

void input(vector<string>& function);

long double calculateExpression(vector<string> function, bool& check, long double variable);
long double calculateExpression(vector<string> function, bool& check, pair<string, long double> variable[100]);

//long double derivative(vector<string> function, bool& check, long double variable);

long double bisection(vector<string> function, long double low_num, long double high_num, bool& check, int precision);
long double fixedPointIteration(vector<string> &function, long double initVal, bool& check, int precision);
long double NewtonMethod(vector<string>& function, long double initVal, bool& check, int precision);
long double secant(vector<string>& function, long double initVal1, long double initVal2, bool& check, int precision);
long double falsePosition(vector<string>& function, long double initVal1, long double initVal2, bool& check, int precision);
