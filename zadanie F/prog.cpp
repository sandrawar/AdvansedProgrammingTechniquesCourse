#include <iostream>
#include <vector>

using namespace std;

int mod_inverse(int a, int p) {
    a = (a % p + p*p) % p;
    for (int x = 0; x < p; x++) {
        if ((a * x ) % p == 1) {
            return x;
        }
    }
    return -1; 
}

void swapColumns(int x, int y, vector<vector<int>>& A, int n) {
    for (int i = 0; i < n; i++) {
        swap(A[i][x], A[i][y]);
    }
}

void swapRows(int x, int y, vector<vector<int>>& A, int n){
    vector<int> temp= A[x];
    A[x] = A[y];
    A[y] = temp;
}

bool DynamicInverse(vector<vector<int>>& A, vector<vector<int>>& A1, int r, int c, int n, int p) {
    swapRows(r, n - 1, A, n);
    swapColumns(c, n - 1, A, n);
    swapRows(c, n - 1, A1, n);
    swapColumns(r, n - 1, A1, n);
    
    n--;
    if (A1[n][n] == 0) {
        return false;
    }
    
    int inv = mod_inverse(A1[n][n], p);
    if (inv == -1) {
        return false;
    }
    
    vector<vector<int>> B1(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            B1[i][j] = (A1[i][j] - (A1[i][n] * A1[n][j] % p) * inv % p + p) % p;
        }
    }
    
    A1 = B1;
    return true;
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
    int p, z;
    cin >> z >> p;

    while (z--) {
        int n;
        int r;
        int c;
        cin >> n >> r >> c;

        vector<vector<int>> A(n, vector<int>(n, 0));
        vector<vector<int>> A1(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> A[i][j];
            }
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cin >> A1[i][j];
            }
        }


        if (!DynamicInverse(A, A1, r, c, n, p)) {
            cout << "NO" << endl;
        } else {
            try{ 
                cout << "YES" << endl;
                printMatrix(A1, n-1);
            }
            catch(const runtime_error& e){
                cout << "NO" << endl;
            }
        }

    }
    return 0;
}
