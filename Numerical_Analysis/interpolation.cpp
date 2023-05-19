#include "interpolation.h"


long double LagrangeInterpolation(vector<pair<long double, long double>> point, long double nextPointX)
{
	int n = point.size();
	long double res = 0;
	for (int i = 0; i < n; i++) {
		long double coefficient = point[i].second;
		for (int j = 0; j < n; j++) {
			if (j != i) {
				coefficient *= (nextPointX - point[j].first);
				coefficient /= (point[i].first - point[j].first);
			}
		}
		res += coefficient;
	}
	return res;
}

vector<vector<long double>> DividedDifferences(vector<pair<long double, long double>> point)
{
	int n = point.size();
	vector<vector<long double>> v(n);
	vector<long double> zeroDifference(n);
	for (int i = 0; i < n; i++) {
		zeroDifference[i] = point[i].second;
	}
	v[0] = zeroDifference;
	for (int i = 1; i < n; i++) {
		vector<long double> highDifference(n - i);
		for (int j = 0; j < n - i; j++) {
			highDifference[j] = (v[i - 1][j + 1] - v[i - 1][j]) / (point[j + i].first - point[j].first);
		}
		v[i] = highDifference;
	}
	return v;
}

long double NewtonForwardDifference(vector<vector<long double>> dividedDifference, vector<pair<long double, long double>> point, long double nextPointX)
{
	int n = dividedDifference.size();
	long double res = dividedDifference[0][0];
	for (int i = 1; i < n; i++) {
		long double coefficient = dividedDifference[i][0];
		for (int j = 0; j < i; j++) {
			coefficient *= (nextPointX - point[j].first);
		}
		res += coefficient;
	}
	return res;
}

long double NewtonBackwardDifference(vector<vector<long double>> dividedDifference, vector<pair<long double, long double>> point, long double nextPointX)
{
	int n = dividedDifference.size();
	long double res = dividedDifference[0][n - 1];
	for (int i = 1; i < n; i++) {
		long double coefficient = dividedDifference[i][n - i - 1];
		for (int j = n - i; j < n; j++) {
			coefficient *= (nextPointX - point[j].first);
		}
		res += coefficient;
	}
	return res;
}

vector<vector<long double>> NaturalCubicSpline(vector<pair<long double, long double>> point)
{
	int n = point.size();

	//Create solution array
	vector<vector<long double>> solution(n - 1);
	for (int i = 0; i < n - 1; i++) {
		vector<long double> tmp(4);
		tmp[0] = point[i].second;
		for (int j = 1; j < 4; j++) tmp[j] = 0;
		solution[i] = tmp;
	}

	vector<long double> h(n - 1), alpha(n - 1), l(n), muy(n - 1), z(n);

	//Step 1
	for (int i = 0; i < n - 1; i++) {
		h[i] = point[i + 1].first - point[i].first;
	}

	//Step 2
	alpha[0] = 0;
	for (int i = 1; i < n - 1; i++) {
		alpha[i] = 3 * (point[i + 1].second - point[i].second) / h[i] - 3 * (point[i].second - point[i - 1].second) / h[i - 1];
	}

	//Step 3
	l[0] = 1; muy[0] = 0; z[0] = 0;

	//Step 4
	for (int i = 1; i < n - 1; i++) {
		l[i] = 2 * (point[i + 1].first - point[i - 1].first) - h[i - 1] * muy[i - 1];
		muy[i] = h[i] / l[i];
		z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
	}

	//Step 5
	l[n - 1] = 1; z[n - 1] = 0;

	//Step 6
	for (int i = n - 2; i >= 0; i--) {
		long double c = 0;
		if (i < n - 2) c = solution[i + 1][2];
		solution[i][2] = z[i] - muy[i] * c;
		solution[i][1] = (point[i + 1].second - point[i].second) / h[i] - h[i] * (c + 2 * solution[i][2]) / 3;
		solution[i][3] = (c - solution[i][2]) / 3 / h[i];
	}

	//Step 7
	return solution;
}
