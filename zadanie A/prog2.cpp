#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

int partition(vector<int>& arr, int start, int end) {
    int pivot = arr[end];
    int i = start - 1;
    for (int j = start; j < end; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[end]);
    return i + 1;
}

void quicksort(vector<int>& arr, int start, int end) {
    if (start < end) {
        int pivot = partition(arr, start, end);
        quicksort(arr, start, pivot - 1);
        quicksort(arr, pivot + 1, end);
    }
}

int kthSmallest(vector<int>& arr, int k) {
    quicksort(arr, 0, arr.size()); return arr[k];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int z, n, k;
    cin >> z;

    for (int j = 0; j < z; j++) {
        cout << "Data set: " << j + 1 << "\n";
        cin >> n >> k;

        vector<int> arr(n);
        cout << "Reading the input (size: " << n << ")....\n";

        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "Reading time: " << duration.count() << " sec\n";

        start = chrono::high_resolution_clock::now();
        cout << "Element at index " << k << ": " << kthSmallest(arr, k) << "\n";
        end = chrono::high_resolution_clock::now();
        duration = end - start;
        cout << "Execution time: " << duration.count() << " sec\n";
    }

    return 0;
}
