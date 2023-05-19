#include "approximation.h"

long double binPow(long double a, int b) {
	long double res = 1.0;
	while (b > 0) {
		if (b & 1) {
			res *= a;
		}
		a *= a;
		b >>= 1;
	}
	return res;
}


long double* DiscreteLeastSquare(vector<pair<long double, long double>> point, int degree)
{
	int m = point.size(), n = degree + 1;
	long double* coefficient = new long double[n];
	long double** normalEquations = new long double* [n];
	for (int i = 0; i < n; i++) {
		normalEquations[i] = new long double[n + 1];
	}

	normalEquations[0][0] = m; normalEquations[0][n] = 0;
	for (int i = 0; i < m; i++) {
		normalEquations[0][n] += point[i].second;
	}
	for (int i = 1; i < n; i++) {
		long double x = 0, yx = 0;
		for (int j = 0; j < m; j++) {
			if (i == 1) {
				x += point[j].first;
				yx += point[j].second * point[j].first;
			}
			else {
				long double tmp = binPow(point[j].first, i);
				x += tmp;
				yx += point[j].second * tmp;
			}
		}
		for (int j = 0; j <= i; j++) {
			normalEquations[j][i - j] = x;
		}
		normalEquations[i][n] = yx;
	}
	for (int i = 1; i < n; i++) {
		long double x = 0;
		for (int j = 0; j < m; j++) {
			x += binPow(point[j].first, n - 1 + i);
		}
		for (int j = i; j <= n - 1; j++) {
			normalEquations[j][n - 1 + i - j] = x;
		}
	}

	coefficient = Doolittle(normalEquations, n);

	return coefficient;
}

long double* FunctionLeastSquare(vector<string> func, int degree, long double a, long double b)
{
	int n = degree + 1;
	long double* coefficient = new long double[n];
	long double** normalEquations = new long double* [n];
	for (int i = 0; i < n; i++) {
		normalEquations[i] = new long double[n + 1];
	}

	normalEquations[0][0] = b - a;
	long double a_power = a * a, b_power = b * b;
	for (int i = 1; i < n; i++) {
		long double x = (b_power - a_power) / (i + 1);
		for (int j = 0; j <= i; j++) {
			normalEquations[j][i - j] = x;
		}
		a_power *= a;
		b_power *= b;
	}

	for (int i = 1; i < n; i++) {
		long double x = (b_power - a_power) / (n + i);
		for (int j = i; j <= n - 1; j++) {
			normalEquations[j][n - 1 + i - j] = x;
		}
		a_power *= a;
		b_power *= b;
	}

	vector<string> func1 = func;
	bool check = true;
	normalEquations[0][n] = SimpsonIntegration(func1, a, b, 100);

	func1.insert(func1.begin(), "(");
	func1.insert(func1.end() - 1, ")");
	func1.insert(func1.end() - 1, "*");
	func1.insert(func1.end() - 1, "x");
	func1.insert(func1.end() - 1, "^");
	func1.insert(func1.end() - 1, "1");

	for (int i = 1; i < n; i++) {
		normalEquations[i][n] = SimpsonIntegration(func1, a, b, 100);
		func1[func1.size() - 2] = to_string(i + 1);
	}

	coefficient = Doolittle(normalEquations, n);

	return coefficient;
}
