#include <iostream>
#include <cstdlib> 
#include <vector>
#include <algorithm>
#include <chrono>
#include <time.h>
#include <random>

using namespace std;

const int MAX_N = 4000000; 
int arr[MAX_N];
const int SHORT_SIZE = 5000;

void insertsort(vector<int>& arr, int start, int n) {
    for (int i = start + 1; i <= n; i++) {
        int key = arr[i];  
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; 
    }
}

int partition(int arr[], int start, int end) {
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

void quicksort(int arr[], int start, int end) {
    if (start < end) {
        int pivot = partition(arr, start, end);
        quicksort(arr, start, pivot - 1);
        quicksort(arr, pivot + 1, end);
    }
}

int myFunction(int arr[], int size, int k) {
    int arr_short[SHORT_SIZE];
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(0, size - 1);

    for (int i = 0; i < SHORT_SIZE; i++) {
        arr_short[i] = arr[distrib(gen)];
    }

    quicksort(arr_short, 0, SHORT_SIZE - 1);
    int k_index = static_cast<int>((static_cast<double>(k) * SHORT_SIZE) / size);

    int L1 = arr_short[max(0, k_index - 200)];
    int L2 = arr_short[min(SHORT_SIZE - 1, k_index + 200)];

    int* arr_middle = new int[size];
    int middle_size = 0;
    int head = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] >= L1 && arr[i] <= L2) {
            arr_middle[middle_size++] = arr[i];
        } else if (arr[i] < L1) {
            head++;
        }
    }

    if (middle_size == 0) {
        delete[] arr_middle;
        return -1;
    }

    quicksort(arr_middle, 0, middle_size - 1);
    int result = arr_middle[k - head];

    //delete[] arr_middle;  
    return result;
}

int kthSmallest(int arr[], int size, int k) {
    return myFunction(arr, size, k - 1);
	//quicksort(arr, 0, size); return arr[k];
}

void fastInput(int arr[], int n) {
    char *buffer = new char[1 << 30];  
    fread(buffer, 1, 1 << 30, stdin);  

    int index = 0, value = 0;
    for (int i = 0; i < n; i++) {
        while (buffer[index] < '0' || buffer[index] > '9') index++;  
        while (buffer[index] >= '0' && buffer[index] <= '9')
            value = value * 10 + (buffer[index++] - '0');
        arr[i] = value;
        value = 0;
    }
    delete[] buffer;  
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

        int* arr = new int[n]; 

        cout << "Reading the input (size: " << n << ")....\n";
        auto start = chrono::high_resolution_clock::now();
		fastInput(arr, n);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "Reading time: " << duration.count() << " sec\n";

        start = chrono::high_resolution_clock::now();
        cout << "Element at index " << k << ": " << kthSmallest(arr, n, k) << "\n";
        end = chrono::high_resolution_clock::now();
        duration = end - start;
        cout << "Execution time: " << duration.count() << " sec\n";

        delete[] arr;  
    }

    return 0;
}