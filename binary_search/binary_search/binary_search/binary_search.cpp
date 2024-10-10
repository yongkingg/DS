#include <iostream>

using namespace std;

// Non Recursive Binary Search 
int non_recursive_binary_search(int* arr, int n, int x) {
	int low = 0;
	int high = n - 1;
	while (low <= high) {
		int mid = (low + high) / 2; // in cpp, remove decimal part(소수점 이하)
		if (arr[mid] < x) low = mid + 1;
		else if (arr[mid] > x) high = mid - 1;
		else return mid;
	}
}

// Recursive Binary Search 
int recursive_binary_search(int* arr,int x, int low, int high) {
	if (low > high) return 0;
	int mid = (low + high) / 2;
	if (arr[mid] < x) return recursive_binary_search(arr, x, mid + 1, high);
	else if (arr[mid] > x) return recursive_binary_search(arr, x, low, mid - 1);
	else return mid;
}

int main() {
	// we have to sort arr before binary search
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int size = 10;
	//int result_index = non_recursive_binary_search(arr, size, 8);
	//int result_index = recursive_binary_search(arr, 8, 0, 9);
	//cout << result_index;
	return 0;
}