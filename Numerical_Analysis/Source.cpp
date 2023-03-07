#include <iomanip>
#include "equation.h"
#include "systemOfEquation.h"
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

enum feature{
	DEFAULT_FEATURE,
	CALCULATE_EXPRESSION,
	SOLVE_EQUATION,
	SOLVE_SYSTEM_EQUATIONS,
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



void intro() {
	cout << "Welcome to NQHApp!!!\n";
	cout << "My app has the following features:\n";
	cout << "-----------------------------\n";
	cout << "1. Calculate the value of expression or function.\n";
	cout << "2. Solve the equation.\n";
	cout << "3. Solve system of equations.\n";
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

			cout << "How many decimal places do you want to show? ";
			int decimalPlace; cin >> decimalPlace;

			cout << "Choose the method (1. Gaussian elimination, 2. Doolittle, 3. Cholesky, 4. Jacobi, 5. Gauss-Seidel): ";
			int option;

			do {
				cin >> option;
				switch (option) {
				case GAUSS_ELIMINATION:
					GaussianElimination(a, n, decimalPlace);
					break;
				case DOOLITTLE:
					Doolittle(a, n, decimalPlace);
					break;
				case CHOLESKY:
					Cholesky(a, n, decimalPlace);
					break;
				case JACOBI:
				{
					long double* initVal = new long double[n];
					cout << "Enter the initial approximation: ";
					for (int i = 0; i < n; i++) cin >> initVal[i];
					Jacobi(a, n, initVal, decimalPlace);
					delete[] initVal;
					break;
				}
				case GAUSS_SEIDEL:
				{
					long double* initVal = new long double[n];
					cout << "Enter the initial approximation: ";
					for (int i = 0; i < n; i++) cin >> initVal[i];
					GaussSeidel(a, n, initVal, decimalPlace);
					delete[] initVal;
					break;
				}
				default:
					cout << "Invalid number. Please enter a number from 1 to 5 corresponding to the method above: ";
				}
			} while (option > 5 || option < 1);
			
			//Delete pointer
			for (int i = 0; i < n; i++) {
				delete[] a[i];
			}
			delete[] a;

			cin.ignore();
			break;
		}
		default:
			cout << "Invalid number. Please enter a number from 1 to 3.\n";
		}
		cout << "-----------------------------\n";


	}
	return 0;
	
}