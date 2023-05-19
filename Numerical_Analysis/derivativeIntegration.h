#pragma once
#include <iostream>
#include <vector>
#include "equation.h"

using namespace std;

long double ThreePointDerivative(long double x0, vector<long double> fx, long double h, bool isMidPoint);
long double FivePointDerivative(long double x0, vector<long double> fx, long double h, bool isMidPoint);
long double SecondDerivativeMidpoint(long double x0, vector<long double> fx, long double h);

long double SimpsonIntegration(vector<string> func, long double a, long double b, int partition);
long double TrapezoidIntegration(vector<string> func, long double a, long double b, int partition);
long double MidpointIntegration(vector<string> func, long double a, long double b, int partition);