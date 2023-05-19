#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

long double** getSystemOfEquations (int nRows, int nCols);

long double* GaussianElimination(long double** system, int n);
long double* Doolittle(long double** system, int n);
long double* Cholesky(long double** system, int n);
long double* Jacobi(long double** system, int n, long double* initVal, int precision);
long double* GaussSeidel(long double** system, int n, long double* initVal, int precision);