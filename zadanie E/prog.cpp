#include <iostream>
#include <vector>

using namespace std;

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

int mod_inverse(int a, int p) {
    a = (a % p + p*p) % p;
    for (int x = 0; x < p; x++) {
        if ((a * x ) % p == 1) {
            return x;
        }
    }
    return -1; 
}

bool GaussElimination(int col, vector<vector<int>>& L, vector<vector<int>>& U, vector<vector<int>>& P, int n, int p) {
    
        int inv = mod_inverse(U[col][col], p);
    for (int i = col + 1; i < n; i++) {
        if (inv == -1) return false;

        int x = (p*p + U[i][col] * inv) % p;
        L[i][col] = x;

        for (int j = col; j < n; j++) {
            U[i][j] = (U[i][j] % p - (x * U[col][j] + p*p) % p + p*p) % p;
        }
    }
    return true;
}

bool GaussIteration(vector<vector<int>>& L, vector<vector<int>>& U, vector<vector<int>>& P, int n, int i, int p) {
    if (!findNonZeroElementInRow(U, i, P, n)) {
        return false;
    }
    if (!GaussElimination(i, L, U, P, n, p)) {
        return false;
    }
    return true;
}


void copyMatrix(const vector<vector<int>>& A, vector<vector<int>>& A_copy, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A_copy[i][j] = A[i][j];
        }
    }
}

bool Gauss(vector<vector<int>>& A, vector<vector<int>>& L, vector<vector<int>>& U, vector<vector<int>>& P, int n, int p) {
    vector<vector<int>> L_copy(n, vector<int>(n, 0));
    vector<vector<int>> U_copy(n, vector<int>(n, 0)); 
    vector<vector<int>> P_copy(n, vector<int>(n, 0));

    copyMatrix(A, U_copy, n);
    createOnes(L_copy, n);
    createOnes(P_copy, n);

    for (int i = 0; i < n; i++) {
        //createOnes(L_copy, n);
        //createOnes(P_copy, n);
        if (!GaussIteration(L_copy, U_copy, P_copy, n, i, p)) {
            return false;
        }
        //L = multiplyMatrices(L_copy, L, p);
        //P = multiplyMatrices(P, P_copy, p);
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


int main() {
    int p, m;
    cin >> m >> p;

    while (m--) {
        int n;
        cin >> n;

        vector<vector<int>> A(n, vector<int>(n, 0));
        vector<vector<int>> A_copy(n, vector<int>(n, 0));
        vector<vector<int>> L(n, vector<int>(n, 0));
        vector<vector<int>> U(n, vector<int>(n, 0));
        vector<vector<int>> P(n, vector<int>(n, 0));

        createOnes(L, n);
        createOnes(P, n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> A[i][j];
            }
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                A[i][j] %= p;
            }
        }

        copyMatrix(A, A_copy, n);

        if (!Gauss(A_copy, L, U, P, n, p)) {
            cout << "NO" << endl;
        } else {
            try{ 
                vector<vector<int>> U_inv = inverseUpperTriangular(U, p);
                vector<vector<int>> L_inv = inverseLowerTriangular(L, p);
                vector<vector<int>> A_inv =  multiplyMatrices(P, U_inv, p);
                A_inv = multiplyMatrices(A_inv, L_inv, p);
             
                cout << "YES" << endl;
                printMatrix(A_inv, n);
            }
            catch(const runtime_error& e){
                cout << "NO" << endl;
            }
        }

    }
    return 0;
}
