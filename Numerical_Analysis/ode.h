#pragma once
#include "equation.h"


vector<long double> EulerODE(vector<string> func, long double initX, long double initY, long double h, int n);
vector<long double> MidpointODE(vector<string> func, long double initX, long double initY, long double h, int n);
vector<long double> HeunODE(vector<string> func, long double initX, long double initY, long double h, int n);
vector<long double> SecondRungeKuttaODE(vector<string> func, long double initX, long double initY, long double h, long double alpha, int n);
vector<long double> FourthRungeKuttaODE(vector<string> func, long double initX, long double initY, long double h, int n);

