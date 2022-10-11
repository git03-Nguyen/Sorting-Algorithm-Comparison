#pragma once
/*
	@file Header.h
*/
#include<iostream>
#include<iomanip>
#include<ctime>
#include"SortAlgorithms.h"
using namespace std;

const int MIN = 0;
const int MAX = 30000;

// Funtions working with array
void clearArr(int*& arr) {
	delete[] arr;
	arr = nullptr;
}
int* copyArr(int* originalArr, int* &arr, const int n) {
	clearArr(arr);
	arr = new int[n];
	for (int i = 0; i < n; i++)
		arr[i] = originalArr[i];
	return arr;
}
void printArr(int arr[], const int n) {
	if (n == 0) {
		cout << "Empty!" << endl;
	}
	else {
		const int SPAN = 7;
		const int COL = 10;
		for (int i = 0; i < n; i++) {
			if (i != 0 && i % COL == 0) cout << endl;
			cout << setw(SPAN) << left << arr[i];
		}
		cout << endl;
	}
}
void shuffleArr(int arr[], const int n) {
	if (n <= 2) return;
	int level = n <= 20 ? 2 : n / 10;
	for (int i = 0; i < level; i++) {
		int idx1 = rand() % (n + 1);
		int idx2 = 0;
		do idx2 = rand() % (n + 1); while (idx1 == idx2);
		swap(arr[idx1], arr[idx2]);
	}
}

int* getRandomArr(const int n, const int MIN_VAL = MIN, const int MAX_VAL = MAX) {
	int* arr = nullptr;
	arr = new int[n];
	for (int i = 0; i < n; i++)
		arr[i] = MIN_VAL + rand() % (MAX_VAL - MIN_VAL + 1);
	return arr;
}
int* getSortedArray(const int n, bool(*compare)(int, int) = asc, const int MIN_VAL = MIN, const int MAX_VAL = MAX) {
	int* arr = getRandomArr(n, MIN_VAL, MAX_VAL);
	quickSort(arr, n, compare);
	return arr;
}
int* getNearlySorted(const int n, bool(*compare)(int, int) = asc, const int MIN_VAL = MIN, const int MAX_VAL = MAX) {
	int* arr = getSortedArray(n, compare, MIN_VAL, MAX_VAL);
	shuffleArr(arr, n);
	return arr;
}

// Measure run-time of each sorting algorithm
double calSortTime(int arr[], const int n,
					void (*sort)(int[], int, bool (*)(int, int)),
					bool (*compare)(int, int) = asc) {
	int* tmpArr = nullptr;
	copyArr(arr, tmpArr, n);

	clock_t start = clock();
	sort(tmpArr, n, compare);
	clock_t end = clock();

	// printArr(tmpArr, n);
	clearArr(tmpArr);
	return (double)(end - start) / CLOCKS_PER_SEC;
}

// Output runtime of 11 sorting algorithms
void testSorting(int arr[], const int n, bool(*order)(int, int)) {
	cout << "-------------------------------" << endl;
	cout << "1. Selection Sort: " << calSortTime(arr, n, selectionSort, order) << " second(s)" << endl;
	cout << "----------" << endl;
	cout << "2. Bubble Sort: " << calSortTime(arr, n, bubbleSort, order) << " second(s)" << endl;
	cout << "----------" << endl;
	cout << "3. Insertion Sort: " << calSortTime(arr, n, insertionSort, order) << " second(s)" << endl;
	cout << "----------" << endl;
	cout << "4. Merge Sort: " << calSortTime(arr, n, mergeSort, order) << " second(s)" << endl;
	cout << "----------" << endl;
	cout << "5. Quick Sort: " << calSortTime(arr, n, quickSort, order) << " second(s)" << endl;
	cout << "----------" << endl;
	cout << "6. Heap Sort: " << calSortTime(arr, n, heapSort, order) << " second(s)" << endl;
	cout << "----------" << endl;
	cout << "7. Radix Sort: " << calSortTime(arr, n, radixSort, order) << " second(s)" << endl;
	cout << "----------" << endl;
	cout << "8. Shell Sort: " << calSortTime(arr, n, shellSort, order) << " second(s)" << endl;
	cout << "----------" << endl;
	cout << "9. Binary Insertion Sort: " << calSortTime(arr, n, binInsertionSort, order) << " second(s)" << endl;
	cout << "----------" << endl;
	cout << "10. Shaker Sort: " << calSortTime(arr, n, shakerSort, order) << " second(s)" << endl;
	cout << "----------" << endl;
	cout << "11. Interchange Sort: " << calSortTime(arr, n, interchangeSort, order) << " second(s)" << endl;
}

// Input size and order to sort
void inputSizeAndOrder(int& n, bool(*&order)(int, int)) {
	// Input N - size of array
	cout << "Input size of array: ";
	cin >> n;
	if (n <= 0)
		throw "Array size must be positive!";

	// Input order to sort
	int choice = 0;
	cout << "Choose order (0 is descending, 1 is ascending): ";
	cin >> choice;
	if (choice != 1 && choice != 0)
		throw "Invalid order!";
	order = choice ? asc : desc;
}

// Test with diffent types of array
void testRandomArray(const int numberOfTest) {
	int n = 0;
	bool(*order)(int, int) = nullptr;
	
	inputSizeAndOrder(n, order);
	cout << "TEST RANDOM ARRAY" << endl;

	for (int i = 0; i < numberOfTest; i++) {
		int* arr = getRandomArr(n);
		//printArr(arr, n);

		testSorting(arr, n, order);

		cout << "-------------------------------" << endl;
		cout << "------ End of test " << i + 1 << " ------------" << endl << endl;
		//system("PAUSE");
		cout << endl;

		clearArr(arr);
	}
}

void testSortedArray(const int numberOfTest) {
	int n = 0;
	bool(*order)(int, int) = nullptr;

	inputSizeAndOrder(n, order);
	cout << "TEST SORTED ARRAY" << endl;

	for (int i = 0; i < numberOfTest; i++) {
		int* arr = getSortedArray(n, order);
		// printArr(arr, n);

		testSorting(arr, n, order);

		cout << "-------------------------------" << endl;
		cout << "------ End of test " << i + 1 << " ------------" << endl << endl;
		cout << endl;

		clearArr(arr);
	}
}

void testNearlySorted(const int numberOfTest) {
	int n = 0;
	bool(*order)(int, int) = nullptr;
	
	inputSizeAndOrder(n, order);
	cout << "TEST NEARLY SORTED ARRAY" << endl;
	for (int i = 0; i < numberOfTest; i++) {
		int* arr = getNearlySorted(n, order);
		// printArr(arr, n);

		testSorting(arr, n, order);

		cout << "-------------------------------" << endl;
		cout << "------ End of test " << i + 1 << " ------------" << endl << endl;
		cout << endl;

		clearArr(arr);
	}
}

void testReversedArray(const int numberOfTest) {
	int n = 0;
	bool(*order)(int, int) = nullptr;

	inputSizeAndOrder(n, order);
	cout << "TEST REVERSED ARRAY" << endl;

	for (int i = 0; i < numberOfTest; i++) {
		int* arr = getSortedArray(n, order == asc ? desc : asc);
		// printArr(arr, n);

		testSorting(arr, n, order);

		cout << "-------------------------------" << endl;
		cout << "------ End of test " << i + 1 << " ------------" << endl << endl;
		cout << endl;

		clearArr(arr);
	}
}

// Menu functions
void menuTest() {
	cout << "SORTING ALGORITHMS RUN-TIME COMPARISON AND ANALYSIS" << endl;
	cout << "1. Test with random array" << endl;
	cout << "2. Test with sorted array" << endl;
	cout << "3. Test with nearly sorted array" << endl;
	cout << "4. Test with reversed array" << endl;
	cout << "Your option (0 to exit): ";
	int choice = 0;
	cin >> choice;
	if (choice == 0) {
		cout << "Exiting..." << endl;
		return;
	}
	if (choice < 0 || choice > 4)
		throw "Invalid options!";;

	system("CLS");
	int numberOfTest = 0;
	cout << "Number of test cases (range 1..20): ";
	cin >> numberOfTest;
	if (numberOfTest < 1 || numberOfTest>20)
		throw "Invalid number of test cases";

	switch (choice) {
	case 1:
		testRandomArray(numberOfTest);
		break;
	case 2:
		testSortedArray(numberOfTest);
		break;
	case 3:
		testNearlySorted(numberOfTest);
		break;
	case 4: 
		testReversedArray(numberOfTest);
		break;
	}
}

// -------------------------------------------------
// End of @file Header.h





