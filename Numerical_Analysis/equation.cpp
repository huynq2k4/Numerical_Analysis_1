#include "equation.h"

void calculateBasicFunc(stack<string>& operat, stack<long double>& num, bool& check);
void calculatePower(stack<string>& operat, stack<long double>& num, bool& check);
void calculateNegative(stack<string>& operat, stack<long double>& num, bool& check);
void calculateMultiplicationAndDivision(stack<string>& operat, stack<long double>& num, bool& check);
void calculateAdditionAndSubtraction(stack<string>& operat, stack<long double>& num, bool& check);

int signum(long double x) {
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

void input(vector<string>& function) {
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
}

long double calculateExpression(vector<string> function, bool& check, pair<string, long double> variable[100]) {

	//khoi tao hai ngan xep luu phep tinh va so
	stack<string> operat;
	stack<long double> num;

	unsigned int i = 0;
	while (i < function.size() && check == true) {

		//neu la so thi dua so vao num
		if (function[i][0] >= '0' && function[i][0] <= '9') {
			num.push(stold(function[i]));
		}
		else if (function[i] == "E" || function[i] == "e") {
			num.push(E);
		}
		else if (function[i] == "PI" || function[i] == "pi") {
			num.push(PI);
		}

		else {

			bool isBasicFunc = false;

			string basic_func[17] = { "-n", "sqrt", "cbrt", "ln", "sin", "cos", "tan", "cot", "arcsin", "arccos", "arctan", "arccot", "sinh", "cosh", "tanh", "coth", "abs" };

			for (int j = 0; j < 17; j++) {
				if (function[i] == basic_func[j]) {
					operat.push(function[i]);
					isBasicFunc = true;
					break;
				}
			}

			bool isVariable = false;
			for (int j = 0; j < 100; j++) {
				if (function[i] == variable[j].first) {
					num.push(variable[j].second);
					isVariable = true;
					break;
				}
			}

			if (!isBasicFunc && !isVariable) {

				if (function[i] == "^") {
					if (!operat.empty()) {
						calculateBasicFunc(operat, num, check);
					}
					operat.push(function[i]);
				}

				else if (function[i] == "*" || function[i] == "/") {
					if (!operat.empty()) {
						calculateBasicFunc(operat, num, check);
						calculateNegative(operat, num, check);
						calculatePower(operat, num, check);
						calculateMultiplicationAndDivision(operat, num, check);
					}
					operat.push(function[i]);
				}

				else if (function[i] == "+" || function[i] == "-") {
					if (!operat.empty()) {
						calculateBasicFunc(operat, num, check);
						calculateNegative(operat, num, check);
						calculatePower(operat, num, check);
						calculateMultiplicationAndDivision(operat, num, check);
						calculateAdditionAndSubtraction(operat, num, check);
					}
					operat.push(function[i]);
				}

				else if (function[i] == "(") {
					operat.push(function[i]);
				}

				else if (function[i] == "=" || function[i] == ")") {
					calculateBasicFunc(operat, num, check);
					calculateNegative(operat, num, check);
					calculatePower(operat, num, check);
					calculateMultiplicationAndDivision(operat, num, check);
					calculateAdditionAndSubtraction(operat, num, check);
					if (check == true) {
						if (function[i] == ")") {
							if (operat.empty() || operat.top() != "(") {
								cerr << "Syntax Error: Lack of parenthesis.";
								check = false;
							}
							else operat.pop();
						}
						else {
							if (operat.empty()) return num.top();
							else {
								cerr << "Syntax Error: Lack of parenthesis.";
								check = false;
							}
						}
					}
				}

				else {
					cerr << "Syntax Error: Cannot understand the expression.";
					check = false;
				}
			}
		}
		++i;
	}
	if (!num.empty()) {
		return num.top();
	}
	return 0;
}

long double calculateExpression(vector<string> function, bool& check, long double variable) {

	//khoi tao hai ngan xep luu phep tinh va so
	stack<string> operat;
	stack<long double> num;

	unsigned int i = 0;
	while (i < function.size() && check == true) {

		//neu la so thi dua so vao num
		if (function[i][0] >= '0' && function[i][0] <= '9') {
			num.push(stold(function[i]));
		}
		else if (function[i] == "E" || function[i] == "e") {
			num.push(E);
		}
		else if (function[i] == "PI" || function[i] == "pi") {
			num.push(PI);
		}
		else if (function[i] == "x") {
			num.push(variable);
		}

		else {

			bool isBasicFunc = false;

			string basic_func[17] = { "-n", "sqrt", "cbrt", "ln", "sin", "cos", "tan", "cot", "arcsin", "arccos", "arctan", "arccot", "sinh", "cosh", "tanh", "coth", "abs" };

			for (int j = 0; j < 17; j++) {
				if (function[i] == basic_func[j]) {
					operat.push(function[i]);
					isBasicFunc = true;
					break;
				}
			}


			if (!isBasicFunc) {

				if (function[i] == "^") {
					if (!operat.empty()) {
						calculateBasicFunc(operat, num, check);
					}
					operat.push(function[i]);
				}

				else if (function[i] == "*" || function[i] == "/") {
					if (!operat.empty()) {
						calculateBasicFunc(operat, num, check);
						calculateNegative(operat, num, check);
						calculatePower(operat, num, check);
						calculateMultiplicationAndDivision(operat, num, check);
					}
					operat.push(function[i]);
				}

				else if (function[i] == "+" || function[i] == "-") {
					if (!operat.empty()) {
						calculateBasicFunc(operat, num, check);
						calculateNegative(operat, num, check);
						calculatePower(operat, num, check);
						calculateMultiplicationAndDivision(operat, num, check);
						calculateAdditionAndSubtraction(operat, num, check);
					}
					operat.push(function[i]);
				}

				else if (function[i] == "(") {
					operat.push(function[i]);
				}

				else if (function[i] == "=" || function[i] == ")") {
					calculateBasicFunc(operat, num, check);
					calculateNegative(operat, num, check);
					calculatePower(operat, num, check);
					calculateMultiplicationAndDivision(operat, num, check);
					calculateAdditionAndSubtraction(operat, num, check);
					if (check == true) {
						if (function[i] == ")") {
							if (operat.empty() || operat.top() != "(") {
								cerr << "Syntax Error: Lack of parenthesis.";
								check = false;
							}
							else operat.pop();
						}
						else {
							if (operat.empty()) return num.top();
							else {
								cerr << "Syntax Error: Lack of parenthesis.";
								check = false;
							}
						}
					}
				}

				else {
					cerr << "Syntax Error: Cannot understand the expression.";
					check = false;
				}
			}
		}
		++i;
	}
	if (!num.empty()) {
		return num.top();
	}
	return -1;
}

void calculateBasicFunc(stack<string>& operat, stack<long double>& num, bool& check) {
	if (!num.empty()) {
		if (!operat.empty()) {
			string s = operat.top();//lay ten ham can tinh

			long double tmp = 0;//luu ket qua de dua vao stack num

			if (s == "sqrt") {
				if (num.top() < 0) {
					cerr << "Math Error: Expression below sqrt is smaller than 0.";
					check = false;
				}
				else {
					tmp = sqrt(num.top());
					num.pop();
					num.push(tmp);
					operat.pop();
				}
			}
			else if (s == "cbrt") {
				tmp = cbrt(num.top());
				num.pop();
				num.push(tmp);
				operat.pop();
			}
			else if (s == "ln") {
				if (num.top() < ZERO_LIMIT) {
					cerr << "Math Error: Expression inside ln is not greater than 0.";
					check = false;
				}
				else {
					tmp = log(num.top());
					num.pop();
					num.push(tmp);
					operat.pop();
				}
			}
			else if (s == "sin") {
				tmp = sin(num.top());
				num.pop();
				num.push(tmp);
				operat.pop();
			}
			else if (s == "cos") {
				tmp = cos(num.top());
				num.pop();
				num.push(tmp);
				operat.pop();
			}
			else if (s == "tan") {
				if (abs(cos(num.top())) < ZERO_LIMIT) {
					cerr << "Math Error: Expression inside tan is invalid.";
					check = false;
				}
				else {
					tmp = tan(num.top());
					num.pop();
					num.push(tmp);
					operat.pop();
				}
			}
			else if (s == "cot") {
				if (abs(sin(num.top())) < ZERO_LIMIT) {
					cerr << "Math Error: Expression inside cot is invalid.";
					check = false;
				}
				else {
					tmp = cos(num.top()) / sin(num.top());
					num.pop();
					num.push(tmp);
					operat.pop();
				}
			}
			else if (s == "arcsin") {
				if (abs(num.top()) > 1) {
					cerr << "Math Error: Expression inside arcsin is invalid (the absolute value is greater than 1).";
					check = false;
				}
				else {
					tmp = asin(num.top());
					num.pop();
					num.push(tmp);
					operat.pop();
				}
			}
			else if (s == "arccos") {
				if (abs(num.top()) > 1) {
					cerr << "Math Error: Expression inside arccos is invalid (the absolute value is greater than 1).";
					check = false;
				}
				else {
					tmp = acos(num.top());
					num.pop();
					num.push(tmp);
					operat.pop();
				}
			}
			else if (s == "arctan") {
				tmp = atan(num.top());
				num.pop();
				num.push(tmp);
				operat.pop();
			}
			else if (s == "arccot") {
				tmp = PI / 2 - atan(num.top());
				num.pop();
				num.push(tmp);
				operat.pop();
			}
			else if (s == "sinh") {
				tmp = sinh(num.top());
				num.pop();
				num.push(tmp);
				operat.pop();
			}
			else if (s == "cosh") {
				tmp = cosh(num.top());
				num.pop();
				num.push(tmp);
				operat.pop();
			}
			else if (s == "tanh") {
				tmp = tanh(num.top());
				num.pop();
				num.push(tmp);
				operat.pop();
			}
			else if (s == "coth") {
				if (abs(sinh(num.top())) < ZERO_LIMIT) {
					cerr << "Math Error: Expression inside coth is invalid.";
					check = false;
				}
				else {
					tmp = cosh(num.top()) / sinh(num.top());
					num.pop();
					num.push(tmp);
					operat.pop();
				}
			}
			else if (s == "abs") {
				tmp = abs(num.top());
				num.pop();
				num.push(tmp);
				operat.pop();
			}
		}
	}
	else {
		cerr << "Syntax Error: Cannot understand the expression.";
		check = false;
	}
}

void calculateNegative(stack<string>& operat, stack<long double>& num, bool& check) {
	if (!operat.empty() && check == true) {
		if (operat.top() == "-n") {
			if (!num.empty()) {
				long double n = num.top();
				num.pop();
				operat.pop();
				num.push(-n);
			}
			else {
				cerr << "Syntax Error: Cannot understand the expression.";
				check = false;
			}
		}
	}
}

//Cac ham duoi day neu con du 2 so thi moi thuc hien, con ko thi in ra loi.
//Ngoai ra ktra check de chi in ra dung 1 loi tren man hinh.

void calculatePower(stack<string>& operat, stack<long double>& num, bool& check) {
	while (!operat.empty() && operat.top() == "^" && check == true) {
		if (num.size() >= 2) {
			long double power = num.top();
			num.pop();
			long double base = num.top();
			num.pop();
			operat.pop();
			num.push(pow(base, power));
		}
		else {
			cerr << "Syntax Error: Cannot understand the expression.";
			check = false;
		}
	}
}

void calculateMultiplicationAndDivision(stack<string>& operat, stack<long double>& num, bool& check) {
	while (!operat.empty() && (operat.top() == "*" || operat.top() == "/") && check == true) {
		if (operat.top() == "*") {
			if (num.size() >= 2) {
				long double x1 = num.top();
				num.pop();
				long double x2 = num.top();
				num.pop();
				operat.pop();
				num.push(x1 * x2);
			}

		}
		else if (operat.top() == "/") {
			if (num.size() >= 2) {
				long double x2 = num.top();
				num.pop();
				if (abs(x2) < ZERO_LIMIT) {
					cerr << "Math Error: Divide by 0.";
					check = false;
				}
				else {
					long double x1 = num.top();
					num.pop();
					operat.pop();
					num.push(x1 / x2);
				}
			}
			else {
				cerr << "Syntax Error: Cannot understand the expression.";
				check = false;
			}
		}
	}
}

void calculateAdditionAndSubtraction(stack<string>& operat, stack<long double>& num, bool& check) {
	while (!operat.empty() && (operat.top() == "+" || operat.top() == "-") && check == true) {
		if (operat.top() == "+") {
			if (num.size() >= 2) {
				long double x1 = num.top();
				num.pop();
				long double x2 = num.top();
				num.pop();
				operat.pop();
				num.push(x1 + x2);
			}
			else {
				cerr << "Syntax Error: Cannot understand the expression.";
				check = false;
			}
		}
		else if (operat.top() == "-") {
			if (num.size() >= 2) {
				long double x2 = num.top();
				num.pop();
				long double x1 = num.top();
				num.pop();
				operat.pop();
				num.push(x1 - x2);
			}
			else {
				cerr << "Syntax Error: Cannot understand the expression.";
				check = false;
			}
		}
	}
}

long double bisection(vector<string> function, long double low_num, long double high_num, bool& check, int precision)
{
	long double mid_num = low_num;

	for (int i = 1; i <= MAX_ITERATION; i++)
	{
		// Find middle point
		mid_num = low_num + (high_num - low_num) / 2.0;

		// Check if middle point is root
		if (calculateExpression(function, check, mid_num) == 0.0 || (high_num - low_num) / 2 < pow(10, -precision)) {
			cout << "Number of iterations: " << i << "." << endl;
			return mid_num;
		}

		// Decide the side to repeat the steps
		else if (signum(calculateExpression(function, check, low_num)) * signum(calculateExpression(function, check, mid_num)) < 0)
			high_num = mid_num;
		else
			low_num = mid_num;
	}
	check = false;//neu khong ra ket qua nhu y muon thi tra ve false
	return mid_num;
}

long double fixedPointIteration(vector<string> &function, long double initVal, bool& check, int precision) {

	//Bien doi ve dung dang can xu li x = f(x)
	function.insert(function.end() - 1, "+");
	function.insert(function.end() - 1, "x");

	long double res = initVal;
	for (int i = 1; i <= MAX_ITERATION; i++) {
		res = calculateExpression(function, check, res);
		if (abs(res - initVal) < pow(10, -precision))
		{
			cout << "Number of iterations: " << i << "." << endl;
			return res;
		}
		initVal = res;
	}

	check = false;//neu khong ra ket qua nhu y muon thi tra ve false
	return 0;
}

long double NewtonMethod(vector<string>& function, long double initVal, bool& check, int precision) {

	long double res = initVal;

	for (int i = 1; i <= MAX_ITERATION; i++) {
		res = initVal - calculateExpression(function, check, res) / derivative(function, check, res);
		if (abs(res - initVal) < pow(10, -precision)) {
			cout << "Number of iterations: " << i << "." << endl;
			return res;
		}
		initVal = res;
	}

	check = false;//neu khong ra ket qua nhu y muon thi tra ve false
	return 0;
}

long double derivative(vector<string> function, bool& check, long double variable) {
	long double res = (calculateExpression(function, check, variable + 1.0e-7) - calculateExpression(function, check, variable - 1.0e-7)) / 2 / 1.0e-7;
	if (check == true) return res;
	return -1;
}

long double secant(vector<string>& function, long double initVal1, long double initVal2, bool& check, int precision) {

	long double res = 0;
	
	for (int i = 2; i <= MAX_ITERATION; i++) {
		res = initVal2 - calculateExpression(function, check, initVal2) * (initVal2 - initVal1) / (calculateExpression(function, check, initVal2) - calculateExpression(function, check, initVal1));
		if (abs(res - initVal2) < pow(10, -precision)) {
			cout << "Number of iterations: " << i << "." << endl;
			return res;
		}
		initVal1 = initVal2;
		initVal2 = res;
	}

	check = false;//neu khong ra ket qua nhu y muon thi tra ve false
	return 0;
}


long double falsePosition(vector<string>& function, long double initVal1, long double initVal2, bool& check, int precision) {

	long double res = 0;

	for (int i = 2; i <= MAX_ITERATION; i++) {

		res = initVal2 - calculateExpression(function, check, initVal2) * (initVal2 - initVal1) / (calculateExpression(function, check, initVal2) - calculateExpression(function, check, initVal1));

		if (abs(res - initVal2) < pow(10, -precision)) {
			cout << "Number of iterations: " << i << "." << endl;
			return res;
		}

		//lua chon diem de tinh gia tri tiep theo
		if (signum(calculateExpression(function, check, res)) * signum(calculateExpression(function, check, initVal2)) < 0) initVal1 = initVal2;
		initVal2 = res;

	}

	check = false;//neu khong ra ket qua nhu y muon thi tra ve false
	return 0;

}