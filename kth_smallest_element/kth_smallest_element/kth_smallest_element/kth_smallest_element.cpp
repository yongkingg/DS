#include <iostream>

using namespace std;

int partition(int* arr, int low, int high) {
	int pivot = arr[high];
	int i = low - 1;
	for (int j = low; j < high; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return i + 1;
}

int kthSmallest(int* arr, int k, int first, int last) {
	int pivot = arr[k];
	int pivotIndex = partition(arr, 0, last);
	if (k < pivotIndex - first + 1) return kthSmallest(arr, k, first, pivotIndex - 1);
	else if (k = pivotIndex - first + 1) return pivot;
	else return kthSmallest(arr, k - (pivotIndex - first + 1), pivotIndex + 1, last);
}

int main() {
	int arr[10] = { 10, 24, 3, 49, 55, 22, 4, 19, 24, 98 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int result = kthSmallest(arr, 4, 0, n-1);
	cout << result;
	return 0;
}


