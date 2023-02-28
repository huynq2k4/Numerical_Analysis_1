#include <iomanip>
#include "equation.h"
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

enum feature{
	DEFAULT,
	CALCULATE_EXPRESSION,
	SOLVE_EQUATION,
	SOLVE_SYSTEM_EQUATIONS,
	PLAY_GAMES
};

void solveUsingBisection(pair<string, long double> variable, vector<string> func) {
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

	cout << "The result is: " << fixed << setprecision(decimalPlace) << bisection(func, a, b, check, decimalPlace);
}

void solveUsingFixedPointIteration(pair<string, long double> variable, vector<string> func) {
	cout << "Enter the initial approximation: ";
	long double initVal; cin >> initVal;

	cout << "How many decimal places do you want to show? ";
	int decimalPlace; cin >> decimalPlace;

	cout << "Enter the maximum number of iterations: ";
	int maxIteration; cin >> maxIteration;

	bool check = true;//kiem tra xem co dung duoc phuong phap nay khong
	long double res = fixedPointIteration(func, initVal, check, decimalPlace, maxIteration);
	if (check) {
		cout << "The result is: " << fixed << setprecision(decimalPlace) << res;
	}
	else {
		cout << "The method failed after " << maxIteration << " iterations.";
	}

}

int main() {
	cout << "Welcome to NQHApp!!!\n";
	//sleep_for(seconds(1));
	cout << "My app has the following features:\n";
	//sleep_for(seconds(2));
	cout << "-----------------------------\n";
	//sleep_for(seconds(1));
	cout << "1. Calculate the value of expression or function.\n";
	//sleep_for(seconds(1));
	cout << "2. Solve the equation.\n";
	//sleep_for(seconds(1));
	cout << "3. Solve system of equations.\n";
	//sleep_for(seconds(1));
	cout << "4. Chill with games.\n";
	//sleep_for(seconds(1));
	cout << "-----------------------------\n";
	//sleep_for(seconds(1));
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
			pair<string, long double> var;

			var.first = "x";

			vector<string> func;

			cout << "f(x) = ";
			input(func);

			//solveUsingBisection(var, func);
			solveUsingFixedPointIteration(var, func);

			cin.ignore();

			cout << endl;
			break;
		}
		case SOLVE_SYSTEM_EQUATIONS:
			break;
		case PLAY_GAMES:
			break;
		default:
			cout << "You're an idiot!!!!!\n";
		}
		cout << "-----------------------------\n";


	}
	return 0;
	
}