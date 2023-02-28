#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <string>

using namespace std;

void input(vector<string>& function);
long double calculateExpression(vector<string> function, bool& check, long double variable);
long double calculateExpression(vector<string> function, bool& check, pair<string, long double> variable[100]);
long double bisection(vector<string> function, long double low_num, long double high_num, bool& check, int precision);
long double fixedPointIteration(vector<string> &function, long double initVal, bool& check, int precision, int maxIteration);
int signum(long double x);