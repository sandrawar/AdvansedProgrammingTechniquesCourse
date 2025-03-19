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
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % p;
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
        A[b][i] = (A[b][i] + (A[a][i] * x) % p + p) % p;
    }
}

int mod_inverse(int a, int p) {
    a = a % p;
    for (int x = 1; x < p; x++) {
        if ((a * x) % p == 1) {
            return x;
        }
    }
    return -1; 
}

bool GaussElimination(int col, vector<vector<int>>& A, vector<vector<int>>& L, vector<vector<int>>& U, vector<vector<int>>& P, int n, int p) {
    for (int i = col + 1; i < n; i++) {
        int inv = mod_inverse(U[col][col], p);
        if (inv == -1) return false;

        int x = (p + U[i][col] * inv) % p;
        L[i][col] = x;

        for (int j = col; j < n; j++) {
            U[i][j] = (U[i][j] - x * U[col][j] % p + p) % p;
        }
    }
    return true;
}

bool GaussIteration(vector<vector<int>>& A, vector<vector<int>>& L, vector<vector<int>>& U, vector<vector<int>>& P, int n, int i, int p) {
    if (!findNonZeroElementInRow(A, i, P, n)) {
        return false;
    }
    if (!GaussElimination(i, A, L, U, P, n, p)) {
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
        if (!GaussIteration(U_copy, L_copy, U_copy, P_copy, n, i, p)) {
            return false;
        }
        L = multiplyMatrices(L_copy, L, p);
        P = multiplyMatrices(P_copy, P, p);
    }

    U = U_copy;
    return true;
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

        copyMatrix(A, A_copy, n);

        if (!Gauss(A_copy, L, U, P, n, p)) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }
    return 0;
}
