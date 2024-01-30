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

int main() {

    int n = 10000;

    int* arr = generateRandomArray(n);

    cout << "Selection sort time: " << timeFunction(arr, n, selectionSort) << " seconds" << endl;

    cout << "Bubble sort time: " << timeFunction(arr, n, bubbleSort) << " seconds" << endl;

    cout << "Merge sort time: " << timeFunction(arr, n, mergesort) << " seconds" << endl;

    cout << "Quick sort time: " << timeFunction(arr, n, quicksort) << " seconds" << endl;

    return 0;

}