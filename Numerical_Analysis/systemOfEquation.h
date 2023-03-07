#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

long double** getSystemOfEquations (int nRows, int nCols);

void GaussianElimination(long double** system, int n, int precision);
void Doolittle(long double** system, int n, int precision);
void Cholesky(long double** system, int n, int precision);
void Jacobi(long double** system, int n, long double* initVal, int precision);
void GaussSeidel(long double** system, int n, long double* initVal, int precision);