#include <iostream>
#include <cstdlib> 
#include <vector>
#include <algorithm>
#include <chrono>
#include <time.h>
#include <random>

using namespace std;

const int pList[2] = {1117, 1367};

bool verifyMultiplication1(const vector<vector<int>>& A, const vector<vector<int>>& B, const vector<vector<int>>& C, int n, int p) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int sum = 0;
            for (int k = 0; k < n; ++k) {
                sum = (sum + 1LL * A[i][k] * B[k][j]) % p;
            }
            if (sum != C[i][j] % p) return false;
        }
    }
    return true;
}

bool compareMatrixes(const vector<vector<int>>& A, const vector<vector<int>>& B, int n, int k, int p){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < k; j++){
            if(A[i][j] % p != B[i][j] % p){
                return false;
            }
        }
    }
    return true;
}

vector<vector<int>> multiplyMatrixVectorMod(const vector<vector<int>>& A, const vector<vector<int>>& v, int n, int p) {
    vector<vector<int>> res(n, vector<int>(1, 0));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            res[i][0] = (res[i][0] + 1LL * A[i][j] * v[j][0]) % p;
        }
        res[i][0] = (res[i][0] ) % p; 
    }
    
    return res;
}

bool verifyMultiplication2(const vector<vector<int>>& A, const vector<vector<int>>& B, const vector<vector<int>>& C, int n) {
    int k = 1; 
    random_device rd;
    mt19937 gen(rd());

    for (int test = 0; test < k; test++) {
        vector<vector<int>> vect(n, vector<int>(1));  
        int p = pList[k];     
        uniform_int_distribution<int> dist(0, p - 1);
        
        for(int i = 0; i < n; i++) {
            vect[i][0] = dist(gen);
        } 

        vector<vector<int>> C0 = multiplyMatrixVectorMod(B, vect, n, p);
        vector<vector<int>> C1 = multiplyMatrixVectorMod(A, C0, n, p);
        vector<vector<int>> C2 = multiplyMatrixVectorMod(C, vect, n, p);

        if (!compareMatrixes(C1, C2, n, 1, p)) {
            return false; 
        }
    }
    return true; 
}

int main() {
    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;
        cout << "Reading the input (size:" << n <<")....\n";

		auto start = std::chrono::high_resolution_clock::now();
        vector<vector<int>> A(n, vector<int>(n));
        vector<vector<int>> B(n, vector<int>(n));
        vector<vector<int>> C(n, vector<int>(n));

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> A[i][j];
        
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> B[i][j];
        
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> C[i][j];
                
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;
		cout << "Reading time:" << duration.count() << endl;
        
		start = std::chrono::high_resolution_clock::now();

        if (verifyMultiplication1(A, B, C, n, pList[0])) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
        
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		cout << "Execution time 1 (matrices multiplication): " << duration.count() << endl;
        start = std::chrono::high_resolution_clock::now();

        if (verifyMultiplication2(A, B, C, n)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
        
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		cout << "Execution time 2 (with vector): " << duration.count() << endl;
    }

    return 0;
}
