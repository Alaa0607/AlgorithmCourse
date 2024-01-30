#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// Function prototypes

void selectionSort(int arr[], int n, int); // Additional int parameter

void bubbleSort(int arr[], int n, int); // Additional int parameter

void merge(int arr[], int l, int m, int r);

void mergesort(int arr[], int l, int r);

void quicksort(int arr[], int low, int high);

// Function to generate a random integer array of size n
int* generateRandomArray(int n) {
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Generate numbers between 0 and 99
    }
    return arr;
}

// Function to print an integer array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Merge sort function
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Quick sort function
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Bubble sort function
void bubbleSort(int arr[], int n , int) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// Selection sort function
void selectionSort(int arr[], int n , int) {
    int i, j, minIndex, temp;
    for (i = 0; i < n-1; i++) {
        minIndex = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// Function to measure the time taken by a sorting algorithm
double timeFunction(int arr[], int n, void (*sortFunction)(int[], int, int)) {
    clock_t startTime = clock();
    sortFunction(arr, 0, n - 1); // Remove the extra integer parameter
    clock_t endTime = clock();
    double timeTaken = double(endTime - startTime) / CLOCKS_PER_SEC;
    return timeTaken;
}
/*int main() {
    srand(time(0)); // Seed the random number generator

    // Generate random arrays of different sizes
    int n1 = 10;
    int* arr1 = generateRandomArray(n1);
    int n2 = 100;
    int* arr2 = generateRandomArray(n2);
    int n3 = 1000;
    int* arr3 = generateRandomArray(n3);

        // Measure the execution time of merge sort for different input sizes
    double totalTime1 = 0;
    for (int i = 0; i < 10; i++) {
        auto start = chrono::high_resolution_clock::now();
        mergesort(arr1, 0, n1-1);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        totalTime1 += duration;
    }
    double avgTime1 = totalTime1 / 10;
    cout << "Merge sort execution time for size " << n1 << ": " << avgTime1 << " ns" << endl;

    // Measure the execution time of quick sort for different input sizes
    double totalTime2 = 0;
    for (int i = 0; i < 10; i++) {
        auto start = chrono::high_resolution_clock::now();
        quicksort(arr2, 0, n2-1);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        totalTime2 += duration;
    }
    double avgTime2 = totalTime2 / 10;
    cout << "Quick sort execution time for size " << n2 << ": " << avgTime2 << " ns" << endl;

    // Measure the execution time of selection sort for different input sizes
    double totalTime3 = 0;
    for (int i = 0; i < 10; i++) {
        auto start = chrono::high_resolution_clock::now();
        selectionSort(arr1, n1);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        totalTime3 += duration;
    }
    double avgTime3 = totalTime3 / 10;
    cout << "Selection sort execution time for size " << n1 << ": " << avgTime3 << " ns" << endl;

    // Measure the execution time of bubble sort for different input sizes
    double totalTime4 = 0;
    for (int i = 0; i < 10; i++) {
        auto start = chrono::high_resolution_clock::now();
        bubbleSort(arr1, n1);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        totalTime4 += duration;
    }
    double avgTime4 = totalTime4 / 10;
    cout << "Bubble sort execution time for size " << n1 << ": " << avgTime4 << " ns" << endl;

    // Measure the execution time of merge sort for different input sizes
    double totalTime5 = 0;
    for (int i = 0; i < 10; i++) {
        auto start = chrono::high_resolution_clock::now();
        mergesort(arr3, 0, n3-1);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        totalTime5 += duration;
    }
    double avgTime5 = totalTime5 / 10;
    cout << "Merge sort execution time for size " << n3 << ": " << avgTime5 << " ns" << endl;

    // Measure the execution time of quick sort for different input sizes
    double totalTime6 = 0;
    for (int i = 0; i < 10; i++) {
        auto start = chrono::high_resolution_clock::now();
        quicksort(arr3, 0, n3-1);
        auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        totalTime6 += duration;
    }
    double avgTime6 = totalTime6 / 10;
    cout << "Quick sort execution time for size " << n3 << ": " << avgTime6 << " ns" << endl;

    // Measure the execution time of bubble sort for different input sizes
    double totalTime7 = 0;
    for (int i = 0; i < 10; i++) {
        auto start = chrono::high_resolution_clock::now();
        bubbleSort(arr3, n3);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        totalTime7 += duration;
    }
    double avgTime7 = totalTime7 / 10;
    cout << "Bubble sort execution time for size " << n3 << ": " << avgTime7 << " ns" << endl;

    // Free memory allocated by the arrays
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    return 0;
    }*/
int main() {

    int n = 10000;

    int* arr = generateRandomArray(n);


    //cout << "Insertion sort time: " << timeFunction(arr, n, insertionSort) << " seconds" << endl;

    cout << "Selection sort time: " << timeFunction(arr, n, selectionSort) << " seconds" << endl;

    cout << "Bubble sort time: " << timeFunction(arr, n, bubbleSort) << " seconds" << endl;

    cout << "Merge sort time: " << timeFunction(arr, n, mergesort) << " seconds" << endl;

    cout << "Quick sort time: " << timeFunction(arr, n, quicksort) << " seconds" << endl;


    return 0;

}