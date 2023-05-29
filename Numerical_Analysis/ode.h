#pragma once
#include "equation.h"
#include "systemOfEquation.h"

void input2(vector<string>& function);

//Solve ODE
vector<long double> EulerODE(vector<string> func, long double initX, long double initY, long double h, int n);
vector<long double> MidpointODE(vector<string> func, long double initX, long double initY, long double h, int n);
vector<long double> HeunODE(vector<string> func, long double initX, long double initY, long double h, int n);
vector<long double> SecondRungeKuttaODE(vector<string> func, long double initX, long double initY, long double h, long double alpha, int n);
vector<long double> FourthRungeKuttaODE(vector<string> func, long double initX, long double initY, long double h, int n);


//Solve system of ODEs
vector<vector<long double>> EulerODE(vector<vector<string>> sysFunc, long double initX, vector<long double> initY, long double h, int step);
vector<vector<long double>> SecondRungeKuttaODE(vector<vector<string>> sysFunc, long double initX, vector<long double> initY, long double h, long double alpha, int step);
vector<vector<long double>>	FourthRungeKuttaODE(vector<vector<string>> sysFunc, long double initX, vector<long double> initY, long double h, int step);