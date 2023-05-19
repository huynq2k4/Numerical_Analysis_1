#pragma once
#include "systemOfEquation.h"
#include "equation.h"
#include "derivativeIntegration.h"
#include <vector>

using namespace std;

long double* DiscreteLeastSquare(vector<pair<long double, long double>> point, int degree);
long double* FunctionLeastSquare(vector<string> func, int degree, long double a, long double b);