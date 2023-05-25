#pragma once
#include <iostream>
#include <vector>

using namespace std;

long double LagrangeInterpolation(vector<pair<long double, long double>> point, long double nextPointX);

vector<vector<long double>> DividedDifferences(vector<pair<long double, long double>> point);
long double NewtonForwardDifference(vector<vector<long double>> dividedDifference, vector<pair<long double, long double>> point, long double nextPointX);
long double NewtonBackwardDifference(vector<vector<long double>> dividedDifference, vector<pair<long double, long double>> point, long double nextPointX);

vector<vector<long double>> NaturalCubicSpline(vector<pair<long double, long double>> point);
vector<vector<long double>> ClampedCubicSpline(vector<pair<long double, long double>> point, long double FPO, long double FPN);