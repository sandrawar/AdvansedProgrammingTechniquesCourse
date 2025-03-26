#include <iostream>
#include <vector>
#include <random>

using namespace std;

const int p = 8191; 

int mod_inverse(int a, int p) {
    int t = 0, new_t = 1;
    int r = p, new_r = a;

    while (new_r != 0) {
        int quotient = ((r / new_r) + p*p)%p;

        t = (p*p + t - quotient * new_t) % p;
        swap(t, new_t);

        r = (p*p + r - quotient * new_r) % p;
        swap(r, new_r);
    }

    if (r > 1) {
        return -1;
    }

    if (t < 0) {
        t = (t + p*p)%p;  
    }

    return t;
}



void copyMatrix(const vector<vector<int>>& A, vector<vector<int>>& A_copy, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A_copy[i][j] = A[i][j];
        }
    }
}


vector<vector<int>> multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, int p) {
    int n = A.size();
    int m = B[0].size();
    int l = A[0].size();
    vector<vector<int>> C(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < l; k++) {
                C[i][j] = (C[i][j] + (A[i][k] * B[k][j]) % p) % p;
            }
        }
    }
    return C;
}

void swapColumns(int x, int y, vector<vector<int>>& A, int n) {
    for (int i = 0; i < n; i++) {
        swap(A[i][x], A[i][y]);
    }
}

void createOnes(vector<vector<int>>& A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = (i == j) ? 1 : 0;
        }
    }
}

bool findNonZeroElementInRow(vector<vector<int>>& A, int row, vector<vector<int>>& P, int n) {
    if (A[row][row] != 0) {
        return true;
    }
    for (int i = row + 1; i < n; i++) {
        if (A[row][i] != 0) {
            swapColumns(row, i, A, n);
            swapColumns(row, i, P, n);
            return true;
        }
    }
    return false;
}

void addRow(int a, int b, int x, vector<vector<int>>& A, int n, int p) {
    for (int i = 0; i < n; i++) {
        A[b][i] = (A[b][i] + (A[a][i] * x + p*p) % p + p*p) % p;
    }
}


bool GaussElimination(int col, vector<vector<int>>& L, vector<vector<int>>& U, vector<vector<int>>& P, int n, int p) {
    if (U[col][col] == 0) {
        return false; 
    }

    int inv = mod_inverse(U[col][col], p);  
    if (inv == -1) {
        cout << "No modular inverse for pivot " << U[col][col] << " at column " << col << endl;
        return false;  
    }

    for (int i = col + 1; i < n; i++) {
        int x = (p*p + U[i][col] * inv) % p;
        L[i][col] = x;

        for (int j = col; j < n; j++) {
            U[i][j] = (U[i][j] - x * U[col][j] + p*p) % p;
        }
    }

    return true;
}

bool GaussIteration(vector<vector<int>>& L, vector<vector<int>>& U, vector<vector<int>>& P, int n, int i, int p) {
    if (!findNonZeroElementInRow(U, i, P, n)) {
        //cout << "No non-zero element found in row " << i << endl;
        return false;
    }

    if (!GaussElimination(i, L, U, P, n, p)) {
        return false;
    }

    return true;
}

bool Gauss(vector<vector<int>>& A, vector<vector<int>>& L, vector<vector<int>>& U, vector<vector<int>>& P, int n, int p) {
    vector<vector<int>> L_copy(n, vector<int>(n, 0));
    vector<vector<int>> U_copy(n, vector<int>(n, 0));
    vector<vector<int>> P_copy(n, vector<int>(n, 0));

    copyMatrix(A, U_copy, n);
    createOnes(L_copy, n);
    createOnes(P_copy, n);

    for (int i = 0; i < n; i++) {
        if (!GaussIteration(L_copy, U_copy, P_copy, n, i, p)) {
            return false;
        }
    }

    copyMatrix(U_copy, U, n);
    copyMatrix(L_copy, L, n);
    copyMatrix(P_copy, P, n);
    return true;
}

vector<vector<int>> inverseLowerTriangular(const vector<vector<int>>& L, int p) {
    int n = L.size();
    vector<vector<int>> L_inv(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        L_inv[i][i] = 1;
    }

    for (int j = 0; j < n; j++) { 
        for (int i = j + 1; i < n; i++) { 
            int sum = 0;
            for (int k = j; k < i; k++) {
                sum = (sum + L[i][k] * L_inv[k][j] + p*p) % p;
            }
            L_inv[i][j] = ((p - sum) % p * mod_inverse(L[i][i], p)) % p;

        }
    }

    return L_inv;
}


vector<vector<int>> inverseUpperTriangular(const vector<vector<int>>& U, int p) {
    int n = U.size();
    vector<vector<int>> U_inv(n, vector<int>(n, 0));

    for (int i = n - 1; i >= 0; i--) {
        U_inv[i][i] = mod_inverse(U[i][i], p);
        if (U_inv[i][i] == -1) {
            throw runtime_error("Brak odwrotności macierzy.");
        }
        for (int j = i + 1; j < n; j++) {
            int sum = 0;
            for (int k = i + 1; k <= j; k++) {
                sum = (sum + U[i][k] * U_inv[k][j] + p*p) % p;
            }
            U_inv[i][j] = (((p - sum + p*p) %p)* mod_inverse(U[i][i], p) + p*p) % p;
        }
    }
    return U_inv;
}

void printMatrix(vector<vector<int>> A, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

void generateTutteMatrix(vector<vector<int>>& A, int n) {
    random_device rd;  
    mt19937 gen(rd());  
    uniform_int_distribution<int> dist(0, p - 2);  

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {  
        if(A[i][j] == 1){
            int randValue = (dist(gen) + 1) %p;  
            A[i][j] = randValue;
            A[j][i] = p - randValue;  
        }
        }
    }
}

bool compareMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    int m = A[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] != B[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> A(n, vector<int>(n, 0));
    vector<vector<int>> L(n, vector<int>(n, 0));
    vector<vector<int>> U(n, vector<int>(n, 0));
    vector<vector<int>> P(n, vector<int>(n, 0));
    vector<vector<int>> A_copy(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        P[i][i] = 1;
        L[i][i] = 1;
    }

    while (m--) {
        int i, j;
        cin >> i >> j;
        A[i][j] = 1;
        A[j][i] = 1;  
    }

    generateTutteMatrix(A, n);
    
    copyMatrix(A, A_copy, n);
    if (!Gauss(A_copy, L, U, P, n, p)) {
            /*cout << "A:" << endl;
            printMatrix(A, n);
            cout << "U: " << endl;
                printMatrix(U, n);
                
                cout << "L: " << endl;
                printMatrix(L, n);
                
                cout << "P: " << endl;
                printMatrix(P, n);
            cout << "NO" << endl;*/
        } else {
            /*cout << "U: " << endl;
                printMatrix(U, n);
                
                cout << "L: " << endl;
                printMatrix(L, n);
                
                cout << "P: " << endl;
                printMatrix(P, n);*/
            try{ 
                vector<vector<int>> U_inv = inverseUpperTriangular(U, p);
                vector<vector<int>> L_inv = inverseLowerTriangular(L, p);
                vector<vector<int>> A_inv =  multiplyMatrices(P, U_inv, p);
                A_inv = multiplyMatrices(A_inv, L_inv, p);          
                cout << "YES" << endl;
            }
            catch(const runtime_error& e){
                cout << "NO" << endl;
            }
        }


    return 0;
}