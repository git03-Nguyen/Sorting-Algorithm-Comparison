#pragma once
/*
	@file Sort.h
*/

// Functions of utilities
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
bool asc(int a, int b) {
    return a > b;
}
bool desc(int a, int b) {
    return a < b;
}
int maxArr(int arr[], const int n) {
    if (n <= 0) {
        throw "Error: cannot find max";
        return -1;
    }
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];
    return max;
}

// 1. Selection Sort
void selectionSort(int arr[], const int n, bool (*compare)(int,int) = asc) {
    for (int i = 0; i < n - 1; i++) {
        int x = i;
        for (int j = i + 1; j < n; j++)
            if (compare(arr[x],arr[j]))
                x = j;
		if (x != i)
            swap(arr[i], arr[x]);
    }
}

// 2. Bubble Sort
void bubbleSort(int arr[], const int n, bool (*compare)(int, int) = asc) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(arr[j], arr[j + 1])) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// 3. Insertion Sort
void insertionSort(int arr[], const int n, bool (*compare)(int, int) = asc) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && compare(arr[j], key)) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 4. Merge Sort
void merge(int arr[], const int left, const int mid, const int right, bool (*compare)(int, int) = asc) {
    const int nL = mid - left + 1;
    const int nR = right - mid;
    int* L = nullptr;
    int* R = nullptr;
    try {
        L = new int[nL];
        R = new int[nR];
    }
    catch (const std::bad_alloc& e) {
        delete[] L, R;
        throw e;
    }
    for (int i = 0; i < nL; i++)    L[i] = arr[left + i];
    for (int i = 0; i < nR; i++)    R[i] = arr[mid + 1 + i];

    int iL = 0;
    int iR = 0;
    int iArr = left;

    while (iL < nL && iR < nR) {
        if (compare(L[iL], R[iR])) {
            arr[iArr++] = R[iR++];
        }
        else {
            arr[iArr++] = L[iL++];
        }
    }
    
    while (iL < nL) {
        arr[iArr++] = L[iL++];
    }
    while (iR < nR) {
        arr[iArr++] = R[iR++];
    }

    delete[] L, R;
}

void mergeSort(int arr[], int const begin, int const end, bool (*compare)(int, int) = asc) {
    if (begin >= end) return;
    int mid = begin + (end - begin) / 2;
    mergeSort(arr, begin, mid, compare);
    mergeSort(arr, mid + 1, end, compare);
    merge(arr, begin, mid, end, compare);
}

void mergeSort(int arr[], const int n, bool (*compare)(int, int) = asc) {
    mergeSort(arr, 0, n - 1, compare);
}

// 5. Quick Sort - pivot at the last element
int partition(int arr[], const int low, const int high, bool (*compare)(int, int) = asc) {
    int random = low + rand() % (high - low);
    swap(arr[random], arr[high]);
    int pivot = arr[high]; // pivot
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (!compare(arr[j], pivot)) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], const int low, const int high, bool (*compare)(int, int) = asc) {
    if (low < high) {
        int pi = partition(arr, low, high, compare);
        quickSort(arr, low, pi - 1, compare);
        quickSort(arr, pi + 1, high, compare);
    }
}

void quickSort(int arr[], const int n, bool (*compare)(int, int) = asc) {
    quickSort(arr, 0, n - 1, compare);
}

// 6. Heap Sort
void heapify(int arr[], const int n, const int i, bool (*compare)(int, int) = asc) {
    int mark = (int)i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && compare(arr[left], arr[mark])) {
        mark = left;
    }
    if (right < n && compare(arr[right], arr[mark])) {
        mark = right;
    }

    if (mark != i) {
        swap(arr[i], arr[mark]);
        heapify(arr, n, mark, compare);
    }
}

void heapSort(int arr[], const int n, bool (*compare)(int, int) = asc) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, compare);
    }
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, compare);
    }
}

// 7. Radix Sort
void countSort(int arr[], const int n, const int exp, bool (*compare)(int, int) = asc) {
    int* output = nullptr;
    output = new int[n];
    int count[10] = { 0 };

    if (compare(1, 0))
        for (int i = 0; i < n; i++)
            count[arr[i] / exp % 10]++;
    else
        for (int i = 0; i < n; i++)
            count[9 - arr[i] / exp % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    if (compare(1, 0))
        for (int i = n - 1; i >= 0; i--)
            output[--count[arr[i] / exp % 10]] = arr[i];
    else 
        for (int i = n - 1; i >= 0; i--)
            output[--count[9 - arr[i] / exp % 10]] = arr[i];

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
   
    delete[] output;
    output = nullptr;
}

void radixSort(int arr[], const int n, bool (*compare)(int, int) = asc) {
    int max = maxArr(arr, n);
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, n, exp, compare); 
}

// 8. Shell Sort
void shellSort(int arr[], const int n, bool (*compare)(int, int) = asc) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = 0;
            for (j = i; j >= gap && compare(arr[j - gap], temp); j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

// 9. Binary Insertion Sort
int binSearch(int arr[], const int item, const int low, const int high, bool(*compare)(int, int)) {
    if (high <= low)
        return compare(item, arr[low]) ? low + 1 : low;

    int mid = low + (high - low) / 2;
    if (item == arr[mid])
        return mid + 1;

    if (compare(item, arr[mid]))
        return binSearch(arr, item, mid + 1, high, compare);

    return binSearch(arr, item, low, mid - 1, compare);
}

void binInsertionSort(int arr[], const int n, bool (*compare)(int, int) = asc) {
    for (int i = 1; i < n; i++) {
        int j = i - 1;
        int x = arr[i];
        int loc = binSearch(arr, x, 0, j, compare);
        while (j >= loc) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = x;
    }
}

// 10. Shaker Sort
void shakerSort(int arr[], const int n, bool (*compare)(int, int) = asc) {
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;
        for (int i = start; i < end; i++) {
            if (compare(arr[i], arr[i + 1])) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        end--;
        for (int i = end - 1; i >= start; i--) {
            if (compare(arr[i], arr[i + 1])) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        start++;
    }
}

// 11. Interchange Sort
void interchangeSort(int arr[], const int n, bool (*compare)(int, int) = asc) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (compare(arr[i], arr[j])) {
                swap(arr[i], arr[j]);   
            }
        }
    }
}

// ------------------------------------------------
// End of @file SortAlgorithms.h



