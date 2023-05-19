#include <iomanip>
#include "equation.h"
#include "systemOfEquation.h"
#include "interpolation.h"
#include "approximation.h"
#include "derivativeIntegration.h"
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

//const long double ALPHA = 1.0 / 3.0;

enum feature{
	DEFAULT_FEATURE,
	CALCULATE_EXPRESSION,
	SOLVE_EQUATION,
	SOLVE_SYSTEM_EQUATIONS,
	INTERPOLATION,
	APPROXIMATION,
	DERIVATIVE,
	INTEGRATION,
	PLAY_GAMES
};

enum equation {
	DEFAULT_EQUATION,
	BISECTION,
	FIXED_POINT,
	NEWTON,
	SECANT,
	FALSE_POSITION
};

enum system_of_equations {
	DEFAULT_SYSTEM_EQUATIONS,
	GAUSS_ELIMINATION,
	DOOLITTLE,
	CHOLESKY,
	JACOBI,
	GAUSS_SEIDEL
};

enum interpolation {

};

enum approximation {

};

enum derivative {

};

enum integration {
	SIMPSON,
	TRAPEZOID,
	MIDPOINT
};



void intro() {
	cout << "Welcome to NQHApp!!!\n";
	cout << "My app has the following features:\n";
	cout << "-----------------------------\n";
	cout << "1. Calculate the value of expression or function.\n";
	cout << "2. Solve the equation.\n";
	cout << "3. Solve system of equations.\n";
	cout << "4. Polynomial interpolation through a set of points.\n";
	cout << "5. Polynomial approximation for a set of points or a function.\n";
	cout << "6. Calculate the derivative of a function at a given point.\n";
	cout << "7. Calculate the integration of a function over an interval.\n";
	cout << "-----------------------------\n";
}

void solveUsingBisection(vector<string> func) {
	cout << "Enter the interval (a, b):\n";
	long double a, b;
	bool check = true;//ktra xem trong phep tinh co loi hay khong, neu ko thi true, neu co thi false
	do {
		cout << "a = ";
		cin >> a;
		cout << "b = ";
		cin >> b;
		if (signum(calculateExpression(func, check, a)) * signum(calculateExpression(func, check, b)) >= 0) {
			cout << "You have not assumed right a and b. Require f(a) * f(b) < 0.\n";
		}
	} while (signum(calculateExpression(func, check, a)) * signum(calculateExpression(func, check, b)) >= 0);

	cout << "How many decimal places do you want to show? ";
	int decimalPlace; cin >> decimalPlace;

	long double res = bisection(func, a, b, check, decimalPlace);
	if (check) {
		cout << "The result is: " << fixed << setprecision(decimalPlace) << res;
	}
	else {
		cout << "The method failed after " << MAX_ITERATION << " iterations.";
	}
}

void solveUsingFixedPointIteration(vector<string> func) {
	cout << "Enter the initial approximation: ";
	long double initVal; cin >> initVal;

	cout << "How many decimal places do you want to show? ";
	int decimalPlace; cin >> decimalPlace;

	bool check = true;//kiem tra xem co dung duoc phuong phap nay khong
	long double res = fixedPointIteration(func, initVal, check, decimalPlace);
	if (check) {
		cout << "The result is: " << fixed << setprecision(decimalPlace) << res;
	}
	else {
		cout << "The method failed after " << MAX_ITERATION << " iterations.";
	}

}

void solveUsingNewtonMethod(vector<string> func) {

	cout << "Enter the initial approximation: ";
	long double initVal; cin >> initVal;

	cout << "How many decimal places do you want to show? ";
	int decimalPlace; cin >> decimalPlace;

	bool check = true;//kiem tra xem co dung duoc phuong phap nay khong
	long double res = NewtonMethod(func, initVal, check, decimalPlace);
	if (check) {
		cout << "The result is: " << fixed << setprecision(decimalPlace) << res;
	}
	else {
		cout << "The method failed after " << MAX_ITERATION << " iterations.";
	}
}

void solveUsingSecantMethod(vector<string> func) {

	cout << "Enter two initial approximation p0 and p1:\n";
	cout << "p0 = ";
	long double initVal1; cin >> initVal1;
	cout << "p1 = ";
	long double initVal2; cin >> initVal2;

	cout << "How many decimal places do you want to show? ";
	int decimalPlace; cin >> decimalPlace;

	bool check = true;//kiem tra xem co dung duoc phuong phap nay khong
	long double res = secant(func, initVal1, initVal2, check, decimalPlace);
	if (check) {
		cout << "The result is: " << fixed << setprecision(decimalPlace) << res;
	}
	else {
		cout << "The method failed after " << MAX_ITERATION << " iterations.";
	}

}

void solveUsingFalsePosition(vector<string> func) {

	cout << "Enter two initial approximation:\n";
	long double a, b;
	bool check = true;//ktra xem trong phep tinh co loi hay khong, neu ko thi true, neu co thi false
	do {
		cout << "p0 = ";
		cin >> a;
		cout << "p1 = ";
		cin >> b;
		if (signum(calculateExpression(func, check, a)) * signum(calculateExpression(func, check, b)) >= 0) {
			cout << "You have not assumed right p0 and p1. Require f(p0) * f(p1) < 0.\n";
		}
	} while (signum(calculateExpression(func, check, a)) * signum(calculateExpression(func, check, b)) >= 0);

	cout << "How many decimal places do you want to show? ";
	int decimalPlace; cin >> decimalPlace;

	long double res = falsePosition(func, a, b, check, decimalPlace);
	if (check) {
		cout << "The result is: " << fixed << setprecision(decimalPlace) << res;
	}
	else {
		cout << "The method failed after " << MAX_ITERATION << " iterations.";
	}
}



int main() {
	intro();
	while (1) {
		cout << "Please enter the number corresponding to the feature you want to try: ";
		int feat; cin >> feat;
		cin.ignore();
		switch (feat) {
		case CALCULATE_EXPRESSION: 
		{
			pair<string, long double> var[100];

			cout << "Input list of variables, separated by a space: ";

			string s; getline(cin, s);//nhap bien khong biet truoc so lieu

			//Tach cac bien dua vao mang de xu li ve sau
			s += ' ';
			size_t pos = 0, n = 0;
			string token;
			while ((pos = s.find(' ')) != string::npos) {
				token = s.substr(0, pos);
				var[n].first = token;
				s.erase(0, pos + 1);
				++n;
			}

			//Nhap gia tri cho cac bien
			for (int i = 0; i < n; i++) {
				cout << var[i].first << " = ";
				cin >> var[i].second;
			}
			cin.ignore();

			vector<string> v;

			cout << "Input the function or expression: \n";
			input(v);

			bool check = true;//ktra xem trong phep tinh co loi hay khong, neu ko thi true, neu co thi false
			long double res = calculateExpression(v, check, var);

			if (check) {
				cout << "How many decimal places do you want to show? (Input 0 if you want to show by default.)\n";
				int decimalPlace; cin >> decimalPlace;
				if (decimalPlace == 0) {
					cout << "The result is: " << res;
				}
				else {
					cout << "The result is: " << fixed << setprecision(decimalPlace) << res;
				}
				cin.ignore();
			}
			cout << endl;
			break;
		}
		case SOLVE_EQUATION:
		{
			cout << "Solve the equation f(x) = 0.\n";
			cout << "f(x) = ";

			vector<string> func;			
			input(func);

			cout << "Choose the method (1: Bisection, 2: Fixed-point Iteration, 3: Newton, 4: Secant, 5: False Position): ";
			int option;

			do {
				cin >> option;
				switch (option) {
				case BISECTION:
					solveUsingBisection(func);
					break;
				case FIXED_POINT:
					solveUsingFixedPointIteration(func);
					break;
				case NEWTON:
					solveUsingNewtonMethod(func);
					break;
				case SECANT:
					solveUsingSecantMethod(func);
					break;
				case FALSE_POSITION:
					solveUsingFalsePosition(func);
					break;
				default:
					cout << "Invalid number. Please enter a number from 1 to 5 corresponding to the method above: ";
				}
			} while (option > 5 || option < 1);

			cin.ignore();

			cout << endl;
			break;
		}
		case SOLVE_SYSTEM_EQUATIONS:
		{
			cout << "Enter the number of equations: ";
			int n; cin >> n;

			cout << "Enter the coefficients: \n";
			long double** a = getSystemOfEquations(n, n + 1);

			long double* solution = nullptr;

			cout << "How many decimal places do you want to show? ";
			int decimalPlace; cin >> decimalPlace;

			cout << "Choose the method (1. Gaussian elimination, 2. Doolittle, 3. Cholesky, 4. Jacobi, 5. Gauss-Seidel): ";
			int option;

			do {
				cin >> option;
				switch (option) {
				case GAUSS_ELIMINATION:
					solution = GaussianElimination(a, n);
					break;
				case DOOLITTLE:
					solution = Doolittle(a, n);
					break;
				case CHOLESKY:
					solution = Cholesky(a, n);
					break;
				case JACOBI:
				{
					cout << "Enter the initial approximation: ";
					long double* initVal = new long double[n];
					for (int i = 0; i < n; i++) cin >> initVal[i];
					solution = Jacobi(a, n, initVal, decimalPlace);
					delete[] initVal;
					break;
				}
				case GAUSS_SEIDEL:
				{
					cout << "Enter the initial approximation: ";
					long double* initVal = new long double[n];
					for (int i = 0; i < n; i++) cin >> initVal[i];
					solution = GaussSeidel(a, n, initVal, decimalPlace);
					delete[] initVal;
					break;
				}
				default:
					cout << "Invalid number. Please enter a number from 1 to 5 corresponding to the method above: ";
				}
			} while (option > 5 || option < 1);
			
			if (solution != nullptr) {
				cout << "The solution is:\n";
				for (int i = 0; i < n; i++) {
					cout << fixed << setprecision(decimalPlace) << solution[i] << endl;
				}
			}

			//Delete pointer
			for (int i = 0; i < n; i++) {
				delete[] a[i];
			}
			delete[] a;
			delete[] solution;

			cin.ignore();
			break;
		}
		case INTERPOLATION:
		{
			cout << "Enter the number of points: ";
			int n; cin >> n;
			while (n <= 1) {
				cout << "Not enough point! Please enter the number of points greater than 1: ";
				cin >> n;
			}
			cout << "Enter list of points (x-coordinate has to be different): " << endl;
			vector<pair<long double, long double>> v(n);
			for (int i = 0; i < n; i++) {
				double x, y; cin >> x >> y;
				v[i] = make_pair(x, y);
			}
			
			vector<vector<long double>> d = DividedDifferences(v);
			cout << "Enter the point (x-coordinate): ";
			double nextPoint; cin >> nextPoint;
			cout << "The value for Lagrange is: " << LagrangeInterpolation(v, nextPoint) << endl;
			cout << "The value for backward is: " << NewtonBackwardDifference(d, v, nextPoint) << endl;
			cout << "The value for forward is: " << NewtonForwardDifference(d, v, nextPoint) << endl;

			vector<vector<long double>> cubicSpline = NaturalCubicSpline(v);
			for (int i = 0; i < cubicSpline.size(); i++) {
				for (int j = 0; j < 4; j++) {
					cout << cubicSpline[i][j] << " ";
				}
				cout << endl;
			}
			break;
		}
		case APPROXIMATION:
		{
			cout << "Choose type of data to approximate (1. Discrete set of points, 2. Function): ";
			int option; cin >> option;
			while (option != 1 && option != 2) {
				cout << "Invalid number! Please choose again: ";
				cin >> option;
			}

			long double* coefficient = nullptr;
			int degree;

			if (option == 1) {
				cout << "Enter the number of points: ";
				int n; cin >> n;
				while (n <= 1) {
					cout << "Not enough point! Please enter the number of points greater than 1: ";
					cin >> n;
				}
				cout << "Enter list of points (x-coordinate has to be different): " << endl;
				vector<pair<long double, long double>> v(n);
				for (int i = 0; i < n; i++) {
					double x, y; cin >> x >> y;
					v[i] = make_pair(x, y);
				}


				cout << "Polynomial approximation with degree = ";
				cin >> degree;
				coefficient = DiscreteLeastSquare(v, degree);


				
			}
			else if (option == 2) {
				cout << "f(x) = ";
				cin.ignore();
				vector<string> func;
				input(func);

				cout << "Enter the interval [a, b]: \n";
				long double a, b;
				cout << "a = "; cin >> a;
				cout << "b = "; cin >> b;

				cout << "Polynomial approximation with degree = ";
				cin >> degree;
				coefficient = FunctionLeastSquare(func, degree, a, b);


			}
			cout << "Least squares polynomial is: ";
			bool hasPlus = false;
			if (coefficient[0] != 0.0) {
				cout << coefficient[0];
				hasPlus = true;
			}
			if (coefficient[1] != 0.0) {
				if (coefficient[1] > 0) {
					if (hasPlus) cout << "+";
					else hasPlus = true;
				}
				cout << coefficient[1] << "x";
			}
			for (int i = 2; i <= degree; i++) {
				if (coefficient[i] != 0.0) {
					if (coefficient[i] > 0) {
						if (hasPlus) cout << "+";
						else hasPlus = true;
					}
					cout << coefficient[i] << "x^" << i;
				}
			}
			cout << endl;
			delete[] coefficient;
			break;
		}
		case DERIVATIVE:
		{
			cout << "Choose type of derivative (1. f'(x), 2. f''(x)): ";
			int type; cin >> type;
			while (type != 1 && type != 2) {
				cout << "Invalid number! Please choose again: ";
				cin >> type;
			}

			cout << "f(x) = ";
			cin.ignore();
			vector<string> func;
			input(func);

			if (type == 1) {
				cout << "Choose the number of points (3 or 5): ";
				int point; cin >> point;
				while (point != 3 && point != 5) {
					cout << "Invalid number! Please choose again: ";
					cin >> point;
				}
				cout << "Choose the method (1. Midpoint, 2. Endpoint): ";
				int option; cin >> option;
				while (option != 1 && option != 2) {
					cout << "Invalid number! Please choose again: ";
					cin >> option;
				}
				long double x0, h; vector<long double> fx(point);
				cout << "x0 = "; cin >> x0;
				cout << "h = "; cin >> h;
				long double res;
				if (point == 3) {


					if (option == 1) {
						for (int i = 0; i < 3; i++) {
							bool check = true;
							pair<string, long double> p[1] = { {"x", x0 + (i - 1) * h} };
							long double tmp = calculateExpression(func, check, p);
							fx[i] = tmp;
						}
						res = ThreePointDerivative(x0, fx, h, true);
					}
					else if (option == 2) {
						for (int i = 0; i < 3; i++) {
							bool check = true;
							pair<string, long double> p[1] = { {"x", x0 + i * h} };
							long double tmp = calculateExpression(func, check, p);
							fx[i] = tmp;
						}
						res = ThreePointDerivative(x0, fx, h, false);
					}

				}
				if (point == 5) {

					if (option == 1) {
						for (int i = 0; i < 5; i++) {
							bool check = true;
							pair<string, long double> p[1] = { {"x", x0 + (i - 2) * h} };
							long double tmp = calculateExpression(func, check, p);
							fx[i] = tmp;
						}
						res = FivePointDerivative(x0, fx, h, true);
					}
					else if (option == 2) {
						for (int i = 0; i < 5; i++) {
							bool check = true;
							pair<string, long double> p[1] = { {"x", x0 + i * h} };
							long double tmp = calculateExpression(func, check, p);
							fx[i] = tmp;
						}
						res = FivePointDerivative(x0, fx, h, false);
					}
				}
				cout << "f'(x0) = " << res;
			}
			else if (type == 2) {
				long double x0, h; vector<long double> fx(3);
				cout << "x0 = "; cin >> x0;
				cout << "h = "; cin >> h;
				for (int i = 0; i < 3; i++) {
					bool check = true;
					pair<string, long double> p[1] = { {"x", x0 + (i - 1) * h} };
					long double tmp = calculateExpression(func, check, p);
					fx[i] = tmp;
				}
				long double res = SecondDerivativeMidpoint(x0, fx, h);
				cout << "f''(x) = " << res;
			}
			cout << endl;
			break;
		}
		case INTEGRATION:
		{
			long double res = 0;

			cout << "Choose the method (1. Simpson's rule, 2. Trapezodial rule, 3. Midpoint rule): ";
			int option; cin >> option;
			while (option < 0 || option > 3) {
				cout << "Invalid number! Please choose again: ";
				cin >> option;
			}

			cout << "f(x) = ";
			cin.ignore();
			vector<string> func;
			input(func);

			cout << "Enter the interval [a, b]:\n";
			long double a, b;
			cout << "a = "; cin >> a;
			cout << "b = "; cin >> b;

			cout << "Enter the number of intervals divided (even for Simpson and Midpoint rule): ";
			switch (option) {
			case SIMPSON:
			{
				int n; cin >> n;
				while (n % 2 != 0) {
					cout << "Invalid number! The number of intervals divided has to be even. Please enter again: ";
					cin >> n;
				}
				res = SimpsonIntegration(func, a, b, n);
				break;
			}
			case TRAPEZOID:
			{
				int n; cin >> n;
				res = TrapezoidIntegration(func, a, b, n);
				break;
			}
			case MIDPOINT:
			{
				int n; cin >> n;
				while (n % 2 != 0) {
					cout << "Invalid number! The number of intervals divided has to be even. Please enter again: ";
					cin >> n;
				}
				res = MidpointIntegration(func, a, b, n);
				break;
			}
			}
			cout << "The result is: " << res << endl;
			break;
		}
		default:
			cout << "Invalid number. Please enter a number from 1 to 3.\n";
		}
		cout << "-----------------------------\n";


	}
	return 0;
	
}