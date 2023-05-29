#include "ode.h"
#include <iomanip>


vector<long double> FY_x(vector<vector<string>> sysfunc, vector<long double> Y, long double x);
vector<long double> operator+(vector<long double> a, vector<long double> b);
vector<long double> operator*(vector<long double> a, long double x);

void input2(vector<string>& function) {
	//cin.ignore();
	string s; getline(cin, s);
	s.erase(remove(s.begin(), s.end(), ' '), s.end());
	int i = 0;
	while (i < s.length()) {
		string tmp = "";

		//nhap so thuc
		if (s[i] <= '9' && s[i] >= '0') {
			while ((s[i] <= '9' && s[i] >= '0') || s[i] == '.') {
				tmp += s[i];
				++i;
			}
		}

		else if (s[i] == '-') {
			tmp = "-";
			//xu li trong truong hop dau tru mang y nghia dau am (vd: -9)
			if (i == 0 || s[i - 1] == '(' || s[i - 1] == '^') {
				tmp += 'n';
			}
			++i;
		}

		//nhap cac cum chu de xu li phep tinh kho va xu li bien
		else if (s[i] >= 'a' && s[i] <= 'z') {
			while (s[i] <= 'z' && s[i] >= 'a') {
				tmp += s[i];
				++i;
			}
		}
		else if (s[i] >= 'A' && s[i] <= 'Z') {
			while (s[i] <= 'Z' && s[i] >= 'A') {
				tmp += s[i];
				++i;
			}
		}

		else {
			//xu li cac dau don gian (+,-,*,/,^)
			tmp += s[i];
			++i;
		}
		function.push_back(tmp);
	}
	function.push_back("=");
	for (int i = 0; i < function.size() - 1; i++) {
		if (function[i] == "y" && function[i + 1][0] >= '0' && function[i + 1][0] <= '9') {
			function[i] += function[i + 1];
			function.erase(function.begin() + i + 1);
		}
	}
}

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

vector<vector<long double>>	EulerODE(vector<vector<string>> sysFunc, long double initX, vector<long double> initY, long double h, int step)
{
	int n = sysFunc.size();
	vector<vector<long double>> res(step);
	for (int i = 1; i <= step; i++) {
		vector<long double> tmp = initY + FY_x(sysFunc, initY, initX + h * (i - 1)) * h;
		res[i - 1] = tmp;
		initY = tmp;
	}
	return res;

}

vector<vector<long double>> SecondRungeKuttaODE(vector<vector<string>> sysFunc, long double initX, vector<long double> initY, long double h, long double alpha, int step)
{
	int n = sysFunc.size();
	vector<vector<long double>> res(step);
	for (int i = 1; i <= step; i++) {

		vector<long double> K1 = FY_x(sysFunc, initY, initX + h * (i - 1)) * h;
		vector<long double> K2 = FY_x(sysFunc, initY + K1 * alpha, initX + h * (i - 1) + alpha * h) * h;

		long double w = 0.5 / alpha;
		vector<long double> tmp = initY + K1 * (1 - w) + K2 * w;
		res[i - 1] = tmp;
		initY = tmp;
	}
	return res;
}

vector<vector<long double>>	FourthRungeKuttaODE(vector<vector<string>> sysFunc, long double initX, vector<long double> initY, long double h, int step) 
{
	int n = sysFunc.size();
	vector<vector<long double>> res(step);
	for (int i = 1; i <= step; i++) {

		vector<long double> K1 = FY_x(sysFunc, initY, initX + h * (i - 1)) * h;
		vector<long double> K2 = FY_x(sysFunc, initY + K1 * 0.5, initX + h * (i - 0.5)) * h;
		vector<long double> K3 = FY_x(sysFunc, initY + K2 * 0.5, initX + h * (i - 0.5)) * h;
		vector<long double> K4 = FY_x(sysFunc, initY + K3, initX + h * i) * h;

		vector<long double> tmp = initY + (K1 + K2 * 2 + K3 * 2 + K4) * (1.0 / 6);
		res[i - 1] = tmp;
		initY = tmp;
	}
	return res;
}

vector<long double> FY_x(vector<vector<string>> sysFunc, vector<long double> Y, long double x)
{
	int n = sysFunc.size();
	bool check = true;
	vector<long double> res(n);
	pair<string, long double>* p = new pair<string, long double>[n + 1];
	
	for (int i = 0; i < n; i++) {
		p[i] = make_pair("y" + to_string(i + 1), Y[i]);
	}
	p[n] = make_pair("x", x);
	for (int i = 0; i < n; i++) {
		res[i] = calculateExpression(sysFunc[i], check, p);
	}
	delete[] p;
	return res;
	
}

vector<long double> operator+(vector<long double> a, vector<long double> b)
{
	int n = a.size();
	vector<long double> res(n);
	for (int i = 0; i < n; i++) {
		res[i] = a[i] + b[i];
	}
	return res;
}

vector<long double> operator*(vector<long double> a, long double x)
{
	vector<long double> tmp = a;
	for (int i = 0; i < tmp.size(); i++) {
		tmp[i] *= x;
	}
	return tmp;
}
