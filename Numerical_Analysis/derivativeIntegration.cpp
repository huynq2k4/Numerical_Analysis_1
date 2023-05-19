#include "derivativeIntegration.h"

long double ThreePointDerivative(long double x0, vector<long double> fx, long double h, bool isMidPoint)
{
	if (fx.size() != 3) return 0;
	long double res = 0;
	if (isMidPoint) {
		res = fx[2] - fx[0];
	}
	else {
		if (h != 0) {
			res = -3 * fx[0] + 4 * fx[1] - fx[2];
		}
	}
	return res / 2 / h;
}

long double FivePointDerivative(long double x0, vector<long double> fx, long double h, bool isMidPoint)
{
	if (fx.size() != 5) return 0;
	long double res = 0;
	if (isMidPoint) {
		res = fx[0] - 8 * fx[1] + 8 * fx[3] - fx[4];
	}
	else {
		if (h != 0) {
			res = -25 * fx[0] + 48 * fx[1] - 36 * fx[2] + 16 * fx[3] - 3 * fx[4];
		}
	}
	return res / 12 / h;
}

long double SecondDerivativeMidpoint(long double x0, vector<long double> fx, long double h)
{
	if (fx.size() != 3) return 0;
	return (fx[0] - 2 * fx[1] + fx[2]) / h / h;
}

long double SimpsonIntegration(vector<string> func, long double a, long double b, int partition)
{
	if(partition % 2 != 0) return 0;
	long double h = (b - a) / partition;
	bool check = true;
	long double xi0 = calculateExpression(func, check, a) + calculateExpression(func, check, b);
	long double xi1 = 0, xi2 = 0;
	for (int i = 1; i <= partition - 1; i++) {
		long double tmp = a + i * h;
		if (i % 2 == 0) xi2 += calculateExpression(func, check, tmp);
		else xi1 += calculateExpression(func, check, tmp);
	}
	xi0 = h / 3 * (xi0 + 2 * xi2 + 4 * xi1);
	return xi0;
}

long double TrapezoidIntegration(vector<string> func, long double a, long double b, int partition)
{
	long double h = (b - a) / partition;
	bool check = true;

	long double res = calculateExpression(func, check, a) + calculateExpression(func, check, b);
	long double xi = 0;

	for (int i = 1; i <= partition - 1; i++) {
		long double tmp = a + i * h;
		xi += calculateExpression(func, check, tmp);
	}

	res = h / 2 * (res + xi * 2);
	return res;
}

long double MidpointIntegration(vector<string> func, long double a, long double b, int partition)
{
	if (partition % 2 != 0) return 0;
	long double h = (b - a) / (partition + 2);
	bool check = true;
	long double res = 0;
	for (int i = 0; i <= partition; i += 2) {
		long double tmp = a + (i + 1) * h;
		res += calculateExpression(func, check, tmp);
	}
	res *= 2 * h;

	return res;
}
