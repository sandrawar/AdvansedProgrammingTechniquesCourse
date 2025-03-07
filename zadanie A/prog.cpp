#include <iostream>
#include <cstdlib> 
#include <vector>
#include <algorithm>
#include <chrono>
#include <time.h>
#include <random>

using namespace std;

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

int partition(std::vector<int>& arr, int start, int end) {
    int pivot = arr[end]; 
    int i = start - 1; 

    for (int j = start; j < end; j++) {
        if (arr[j] < pivot) { 
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[end]); 
    return i + 1;
}

void quicksort(std::vector<int>& arr, int start, int end) {
    if (start < end) {
        int pivot = partition(arr, start, end);

        quicksort(arr, start, pivot - 1);
        quicksort(arr, pivot + 1, end);
    }
}

int findMedian(vector<int>& arr, int start, int size) {
    sort(arr.begin() + start, arr.begin() + start + size);
    return arr[start + size / 2];
}

int medianOfMedians(vector<int>& arr, int left, int right, int k) {
    int n = right - left + 1;
    
    if (n <= 5) {
        sort(arr.begin() + left, arr.begin() + right + 1);
        return arr[left + k];
    }

    vector<int> medians;
    for (int i = 0; i < n / 5; i++) {
        int median = findMedian(arr, left + i * 5, 5);
        medians.push_back(median);
    }
    if (n % 5 > 0) { 
        int median = findMedian(arr, left + (n / 5) * 5, n % 5);
        medians.push_back(median);
    }

    int pivot = medianOfMedians(medians, 0, medians.size() - 1, medians.size() / 2);

    vector<int> leftPart, rightPart;
    int pivotCount = 0;
    for (int i = left; i <= right; i++) {
        if (arr[i] < pivot) leftPart.push_back(arr[i]);
        else if (arr[i] > pivot) rightPart.push_back(arr[i]);
        else pivotCount++;
    }

    if (k < leftPart.size()) return medianOfMedians(leftPart, 0, leftPart.size() - 1, k);
    else if (k < leftPart.size() + pivotCount) return pivot;
    else return medianOfMedians(rightPart, 0, rightPart.size() - 1, k - leftPart.size() - pivotCount);
}

int myFunction(std::vector<int>& arr, int start, int size, int k){
	 
	vector<int> arr_short;
	arr_short.clear();
	std::srand(std::time(0));

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distrib(0, arr.size() - 1);



	int short_size = 5000; 
	for(int i = 0; i < short_size; i++){
		int x = distrib(gen);
		arr_short.push_back(arr[x]);
	}

	quicksort(arr_short, 0, arr_short.size()-1);
	int k_index = static_cast<int>((static_cast<double>(k) * short_size) / arr.size());

    int L1 = arr_short[max(0, k_index - 200)];
    int L2 = arr_short[min(short_size - 1, k_index + 200)];


	vector<int> arr_middle;
	int head = 0;
	for(int i = 0; i < arr.size(); i++){
		if(arr[i] >= L1 && arr[i] <= L2){
			arr_middle.push_back(arr[i]);
		}
		else if(arr[i] < L1){
			head++;
		}
	}
	if (arr_middle.empty()) {
    	return -1; 
	}

	quicksort(arr_middle, 0, arr_middle.size() - 1);
	return arr_middle[k - head];
}


int kthSmallest(vector<int>& arr, int k) {
	
	//quicksort(arr, 0, arr.size()-1); return arr[k-1];
	//insertsort(arr, 0, arr.size()-1); return arr[k-1];		
	//return medianOfMedians(arr, 0, arr.size() - 1, k);
	return myFunction(arr, 0, arr.size()-1, k-1);

}


int main() {
	int z, n, k, x;
	vector<int> arr;
	cin >> z;
	int j = 0;
	while(j < z)
	{
		j++;
		cout << "Data set:"<< j << "\n";
		cin >> n >> k;
		cout << "Reading the input (size:" << n <<")....\n";
		arr.clear();
		auto start = std::chrono::high_resolution_clock::now();
		for(int i=0; i< n; i++)
		{	
			cin >> x;
			arr.push_back(x);
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;
		cout << "Reading time:" << duration.count() << endl; 
		
		start = std::chrono::high_resolution_clock::now();
		cout << "Element at index "<<k <<": ";
		cout << kthSmallest(arr, k) << endl;
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		cout << "Execution time:" << duration.count() << endl; 
		
	}
    return 0;
}
