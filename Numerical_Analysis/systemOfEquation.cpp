#include "systemOfEquation.h"


void exchangeRows(long double** a, int nCols, int i, int j);
void showResult(long double** a, int nRows, int precision);

void input1(vector<string>& function) {
    string s; cin >> s;
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

long double** getSystemOfEquations(int nRows, int nCols) {
    long double** sys = new long double* [nRows];
    for (int i = 0; i < nRows; i++) {
        sys[i] = new long double [nCols];
        for (int j = 0; j < nCols; j++) {
            vector<string> v;
            input1(v);
            bool check = true;
            sys[i][j] =  calculateExpression(v, check, 0.0);
        }
    }
    return sys;
}

long double* GaussianElimination(long double** system, int n)
{
    for (int i = 0; i < n - 1; i++) {//Step 1
        /*long double pivotValue = 0;
        for (int j = i; j < n; j++) {
            long double pivotValue_tmp = abs(system[j][i]);
            for (int k = i; k < n; k++) {
                if (abs(system[j][k]) > pivotValue_tmp) pivotValue_tmp = abs(system[j][k]);
            }
            if (pivotValue_tmp == 0) {
                cout << "No unique solution exists." << endl;
                return nullptr;
            }
            else {
                pivotValue_tmp = abs(system[j][i]) / pivotValue_tmp;
                if (pivotValue_tmp > pivotValue) {
                    pivotValue = pivotValue_tmp;
                    pivotRow = j;
                }
            }
        }*/

        //Partial pivoting
        int pivotRow = i;
        for (int j = i; j < n; j++) {
            if (abs(system[j][i]) > abs(system[pivotRow][i])) pivotRow = j;
        }
        if (system[pivotRow][i] == 0.0) {
            cout << "No unique solution exists." << endl;
            return nullptr;
        }//Step 2
        else {
            exchangeRows(system, n + 1, i, pivotRow);
        }//Step 3
        for (int j = i + 1; j < n; j++) {//Step 4
            long double f = system[j][i] / system[i][i];//Step 5
            for (int k = i + 1; k < n + 1; k++) {
                system[j][k] -= system[i][k] * f;//Step 6
            }
            //system[j][i] = 0;
        }   
    }
    if (system[n - 1][n - 1] == 0.0) {
        cout << "No unique solution exists." << endl;
        return nullptr;
    }//Step 7

    //Backward substitution
    system[n - 1][n] /= system[n - 1][n - 1];//Step 8
    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            system[i][n] -= (system[i][j] * system[j][n]);
        }
        system[i][n] /= system[i][i];
    }//Step 9

    //Step 10
    long double* solution = new long double[n];
    for (int i = 0; i < n; i++) {
        solution[i] = system[i][n];
    }
    return solution;

    //showResult(system, n, precision);
}

long double* Doolittle(long double** system, int n)
{
    //Create lower triangular matrix 
    long double** l = new long double* [n];
    for (int i = 0; i < n; i++) {
        l[i] = new long double[n];
        for (int j = 0; j < n; j++) {
            if (j == i) l[i][j] = 1;
            else l[i][j] = 0;
        }
    }

    //Create upper triangular matrix
    long double** u = new long double* [n];
    for (int i = 0; i < n; i++) {
        u[i] = new long double[n];
        for (int j = 0; j < n; j++) {
            u[i][j] = 0;
        }
    }

    //Create solution array
    long double* solution = new long double [n];
    for (int i = 0; i < n; i++) {
        solution[i] = system[i][n];
    }

    //LU factorization
    u[0][0] = system[0][0];
    if (u[0][0] == 0) {
        cout << "No unique solution exists." << endl;
        return nullptr;
    }
    for (int i = 1; i < n; i++) {
        u[0][i] = system[0][i];
        l[i][0] = system[i][0] / u[0][0];
    }
    for (int i = 1; i < n - 1; i++) {
        u[i][i] = system[i][i];
        for (int j = 0; j < i; j++) {
            u[i][i] -= (l[i][j] * u[j][i]);
        }
        if (u[i][i] == 0) {
            cout << "No unique solution exists." << endl;
            return nullptr;
        }
        for (int j = i + 1; j < n; j++) {
            u[i][j] = system[i][j];
            l[j][i] = system[j][i];
            for (int k = 0; k < i; k++) {
                u[i][j] -= (l[i][k] * u[k][j]);
                l[j][i] -= (l[j][k] * u[k][i]);
            }
            u[i][j] /= l[i][i];
            l[j][i] /= u[i][i];
        }
    }
    u[n - 1][n - 1] = system[n - 1][n - 1];
    for (int i = 0; i < n - 1; i++) {
        u[n - 1][n - 1] -= (l[n - 1][i] * u[i][n - 1]);
    }
    if (u[n - 1][n - 1] == 0) {
        cout << "No unique solution exists." << endl;
        return nullptr;
    }

    //Forward substitution L(Ux) = b
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            solution[i] -= (solution[j] * l[i][j]);
        }
        solution[i] /= l[i][i];
    }

    //Backward substitution Ux = y
    solution[n - 1] /= u[n - 1][n - 1];
    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            solution[i] -= (solution[j] * u[i][j]);
        }
        solution[i] /= u[i][i];
    }

    //Delete pointer
    for (int i = 0; i < n; i++) {
        delete[] l[i];
        delete[] u[i];
    }
    delete[] l;
    delete[] u;
    return solution;
}

long double* Cholesky(long double** system, int n)
{
    //Check if the coefficient matrix is symmetric
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (system[i][j] != system[j][i]) {
                cout << "Cannot use Cholesky's method since the coefficient matrix is not symmetric.\n";
                return nullptr;
            }
        }
    }

    //Create lower triangular matrix;
    long double** l = new long double* [n];
    for (int i = 0; i < n; i++) {
        l[i] = new long double[n];
        for (int j = 0; j < n; j++) {
            l[i][j] = 0;
        }
    }

    //Create solution array
    long double* solution = new long double[n];
    for (int i = 0; i < n; i++) {
        solution[i] = system[i][n];
    }

    //Calculate value for lower triangular matrix
    if (system[0][0] <= 0) {
        cout << "Cannot use Cholesky's method since the coefficient matrix is not positive definite.\n";
        return nullptr;
    }
    else {
        l[0][0] = sqrt(system[0][0]);
    }
    for (int i = 1; i < n; i++) {
        l[i][0] = system[i][0] / l[0][0];
    }
    for (int i = 1; i < n - 1; i++) {
        l[i][i] = system[i][i];
        for (int j = 0; j < i; j++) {
            l[i][i] -= (l[i][j] * l[i][j]);
        }
        if (l[i][i] < 0) {
            cout << "Cannot use Cholesky's method since the coefficient matrix is not positive definite.\n";
            return nullptr;
        }
        else {
            l[i][i] = sqrt(l[i][i]);
        }
        for (int j = i + 1; j < n; j++) {
            l[j][i] = system[j][i];
            for (int k = 0; k < i; k++) {
                l[j][i] -= (l[j][k] * l[i][k]);
            }
            l[j][i] /= l[i][i];
        }
    }
    l[n - 1][n - 1] = system[n - 1][n - 1];
    for (int j = 0; j < n - 1; j++) {
        l[n - 1][n - 1] -= (l[n - 1][j] * l[n - 1][j]);
    }
    if (l[n - 1][n - 1] < 0) {
        cout << "Cannot use Cholesky's method since the coefficient matrix is not positive definite.\n";
        return nullptr;
    }
    else {
        l[n - 1][n - 1] = sqrt(l[n - 1][n - 1]);
    }

    //Forward substitution L(Lt.x) = b
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            solution[i] -= (solution[j] * l[i][j]);
        }
        solution[i] /= l[i][i];
    }

    //Backward substitution Lt.x = y
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            solution[i] -= (solution[j] * l[j][i]);
        }
        solution[i] /= l[i][i];
    }

    //Delete pointer
    for (int i = 0; i < n; i++) {
        delete[] l[i];
    }
    delete[] l;
    return solution;
}

long double* Jacobi(long double** system, int n, long double* initVal, int precision)
{
    //Initialize solution array
    long double* solution = new long double[n];
    for (int i = 0; i < n; i++) {
        solution[i] = 0;
    }

    for (int i = 1; i <= MAX_ITERATION; i++) {
        for (int j = 0; j < n; j++) {
            solution[j] = system[j][n];
            for (int k = 0; k < n; k++) {
                if (k != j) {
                    solution[j] -= (system[j][k] * initVal[k]);
                }
            }
            solution[j] /= system[j][j];
        }
        long double norm = 0;
        for (int j = 0; j < n; j++) {
            norm += ((solution[j] - initVal[j]) * (solution[j] - initVal[j]));
        }
        norm = sqrt(norm);

        //Set stop condition
        if (norm < pow(10, -precision)) {
            return solution;
        }
        else {
            for (int j = 0; j < n; j++) {
                initVal[j] = solution[j];
            }
        }
    }

    cout << "The method failed after " << MAX_ITERATION << " iterations." << endl;
    return nullptr;
}

long double* GaussSeidel(long double** system, int n, long double* initVal, int precision)
{
    //Initialize solution array
    long double* solution = new long double[n];
    for (int i = 0; i < n; i++) {
        solution[i] = 0;
    }

    for (int i = 1; i <= MAX_ITERATION; i++) {
        for (int j = 0; j < n; j++) {
            solution[j] = system[j][n];
            for (int k = 0; k < j; k++) {
                solution[j] -= (system[j][k] * solution[k]);
            }
            for (int k = j + 1; k < n; k++) {
                solution[j] -= (system[j][k] * initVal[k]);
            }
            solution[j] /= system[j][j];
        }
        long double norm = 0;
        for (int j = 0; j < n; j++) {
            norm += ((solution[j] - initVal[j]) * (solution[j] - initVal[j]));
        }
        norm = sqrt(norm);

        //Set stop condition
        if (norm < pow(10, -precision)) {
            return solution;
        }
        else {
            for (int j = 0; j < n; j++) {
                initVal[j] = solution[j];
                cout << solution[j] << " ";
            }
            cout << endl;
        }
    }

    cout << "The method failed after " << MAX_ITERATION << " iterations." << endl;
    return nullptr;
}


void exchangeRows(long double** a, int nCols, int i, int j) {
    for (int k = 0; k < nCols; k++) {
        long double tmp = a[i][k];
        a[i][k] = a[j][k];
        a[j][k] = tmp;
    }
}

void showResult(long double** a, int nRows, int precision) {
    cout << "The solution is:\n";
    for (int i = 0; i < nRows; i++) {
        cout << fixed << setprecision(precision) << a[i][nRows] << endl;
    }
}