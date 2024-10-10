#include <iostream>

using namespace std;

void insertionSort(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		int cur = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > cur) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = cur;
	}
}

int main() {
	int arr[9] = { 4, 2, 3, 6, 8, 9, 1, 5, 7 };
	int arr_size = 9;
	insertionSort(arr, arr_size);
	for (int index = 0; index < arr_size; index++) {
		cout << arr[index] << " ";
	}
	return 0;
}