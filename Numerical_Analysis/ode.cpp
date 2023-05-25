#include "ode.h"
#include <iomanip>

vector<long double> EulerODE(vector<string> func, long double initX, long double initY, long double h, int n)
{
	vector<long double> res(n);
	for (int i = 1; i <= n; i++) {
		pair<string, long double> p[2] = { {"x", initX + h * (i - 1)}, {"y", initY}};
		bool check = true;
		long double tmp = initY + h * calculateExpression(func, check, p);
		res[i - 1] = tmp;
		initY = tmp;
	}
	return res;
}

vector<long double> MidpointODE(vector<string> func, long double initX, long double initY, long double h, int n)
{
	vector<long double> res(n);
	for (int i = 1; i <= n; i++) {
		pair<string, long double> p[2] = { {"x", initX + h * (i - 1)}, {"y", initY} };
		bool check = true;
		long double tmp1 = initY + h / 2 * calculateExpression(func, check, p);
		p[0].second += h / 2;
		p[1].second = tmp1;
		long double tmp2 = initY + h * calculateExpression(func, check, p);
		res[i - 1] = tmp2;
		initY = tmp2;
	}
	return res;
}

vector<long double> HeunODE(vector<string> func, long double initX, long double initY, long double h, int n)
{
	vector<long double> res(n);
	for (int i = 1; i <= n; i++) {
		pair<string, long double> p[2] = { {"x", initX + h * (i - 1)}, {"y", initY} };
		bool check = true;
		long double f_xy = calculateExpression(func, check, p);
		long double tmp1 = initY + h * f_xy;
		p[0].second += h;
		p[1].second = tmp1;
		long double tmp2 = initY + h / 2 * (f_xy + calculateExpression(func, check, p));
		res[i - 1] = tmp2;
		initY = tmp2;
	}
	return res;
}

vector<long double> SecondRungeKuttaODE(vector<string> func, long double initX, long double initY, long double h, long double alpha, int n)
{
	vector<long double> res(n);
	for (int i = 1; i <= n; i++) {
		pair<string, long double> p[2] = { {"x", initX + h * (i - 1)}, {"y", initY} };
		bool check = true;
		long double K1 = h * calculateExpression(func, check, p);
		p[0].second += alpha * h;
		p[1].second += alpha * K1;
		long double K2 = h * calculateExpression(func, check, p);

		long double w = 1.0 / 2 / alpha;
		long double tmp = initY + (1 - w) * K1 + w * K2;
		res[i - 1] = tmp;
		initY = tmp;
	}
	return res;
}

vector<long double> FourthRungeKuttaODE(vector<string> func, long double initX, long double initY, long double h, int n)
{
	vector<long double> res(n);
	for (int i = 1; i <= n; i++) {
		pair<string, long double> p[2] = { {"x", initX + h * (i - 1)}, {"y", initY} };
		bool check = true;
		long double K1 = calculateExpression(func, check, p);

		p[0].second += h / 2.0;
		p[1].second += h * K1 / 2.0;
		long double K2 = calculateExpression(func, check, p);

		p[1].second = initY + h * K2 / 2.0;
		long double K3 = calculateExpression(func, check, p);

		p[0].second += h / 2.0;
		p[1].second = initY + h * K3;
		long double K4 = calculateExpression(func, check, p);

		long double tmp = initY + h / 6 * (K1 + 2 * K2 + 2 * K3 + K4);
		res[i - 1] = tmp;
		initY = tmp;
	}
	return res;
}
