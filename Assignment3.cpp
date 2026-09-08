#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

int selectPivot(int arr[], int low, int high, int strategy) {
    if (strategy == 1) return low;
    if (strategy == 2) return high;
    if (strategy == 3) return low + (high - low) / 2;
    return low + rand() % (high - low + 1);
}

int partitionArray(int arr[], int low, int high, int strategy, long long &comparisons) {
    int pivotIndex = selectPivot(arr, low, high, strategy);
    swap(arr[pivotIndex], arr[high]);
    int pivot = arr[high], i = low - 1;

    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high, int strategy, long long &comparisons) {
    if (low < high) {
        int pivotPosition = partitionArray(arr, low, high, strategy, comparisons);
        quickSort(arr, low, pivotPosition - 1, strategy, comparisons);
        quickSort(arr, pivotPosition + 1, high, strategy, comparisons);
    }
}

void generateSortedArray(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = i + 1;
}

void generateReverseSortedArray(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = n - i;
}

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = rand() % 100000 + 1;
}

void copyArray(int source[], int destination[], int n) {
    for (int i = 0; i < n; i++) destination[i] = source[i];
}

struct Result {
    long long comparisons;
    double averageTime;
};

Result measurePerformance(int original[], int n, int strategy) {
    double totalTime = 0.0;
    long long comparisons = 0;

    for (int run = 1; run <= 3; run++) {
        int *arr = new int[n];
        copyArray(original, arr, n);
        long long currentComparisons = 0;

        auto t1 = high_resolution_clock::now();
        quickSort(arr, 0, n - 1, strategy, currentComparisons);
        auto t2 = high_resolution_clock::now();

        totalTime += duration<double, micro>(t2 - t1).count();
        comparisons = currentComparisons;
        delete[] arr;
    }
    return {comparisons, totalTime / 3.0};
}

void printSectionHeader(const string &title, const string &subtitle) {
    cout << "\n\n============================================================\n";
    cout << "                    " << title << "\n";
    cout << "             " << subtitle << "\n";
    cout << "============================================================\n";
    cout << left << setw(22) << "Pivot Strategy" << setw(20) << "Comparisons" << setw(20) << "Average Time (us)\n";
    cout << "------------------------------------------------------------\n";
}

void printRow(const string &strategy, long long comparisons, double avgTime) {
    cout << left << setw(22) << strategy << setw(20) << comparisons << setw(20) << fixed << setprecision(3) << avgTime << "\n";
}

int main() {
    const int n = 1200;
    srand(time(0));

    cout << "\n============================================================\n";
    cout << "       QUICK SORT - DIVIDE AND CONQUER\n";
    cout << "       PIVOT SELECTION PERFORMANCE ANALYSIS\n";
    cout << "============================================================\n\n";
    cout << "Input Size       : " << n << "\nNumber of Runs   : 3\nTime Unit        : Microseconds (us)\n";

    int *sortedArray = new int[n];
    int *reverseArray = new int[n];
    int *randomArray = new int[n];

    generateSortedArray(sortedArray, n);
    generateReverseSortedArray(reverseArray, n);
    generateRandomArray(randomArray, n);

    Result sortedFirst = measurePerformance(sortedArray, n, 1);
    Result sortedMiddle = measurePerformance(sortedArray, n, 3);
    printSectionHeader("SORTED ARRAY", "Pivot: First + Middle");
    printRow("First Element", sortedFirst.comparisons, sortedFirst.averageTime);
    printRow("Middle Element", sortedMiddle.comparisons, sortedMiddle.averageTime);

    Result reverseLast = measurePerformance(reverseArray, n, 2);
    printSectionHeader("REVERSE-SORTED ARRAY", "   Pivot: Last");
    printRow("Last Element", reverseLast.comparisons, reverseLast.averageTime);

    Result randomPivot = measurePerformance(randomArray, n, 4);
    printSectionHeader("UNSORTED / RANDOM ARRAY", "  Pivot: Random");
    printRow("Random Element", randomPivot.comparisons, randomPivot.averageTime);

    cout << "\n\n============================================================\n";
    cout << "                     FINAL SUMMARY\n";
    cout << "============================================================\n";
    cout << "\nInput Size : 1200\n\nPivot Strategies Used:\n";
    cout << "Sorted Array        -> First Element\nSorted Array        -> Middle Element\n";
    cout << "Reverse-Sorted      -> Last Element\nUnsorted / Random   -> Random Element\n";
    cout << "\n\nTime Calculation:\nDelta t = t2 - t1\n";
    cout << "t1 = Time immediately before Quick Sort\nt2 = Time immediately after Quick Sort\n";
    cout << "\n============================================================\n";
    cout << "                  EXPERIMENT COMPLETED\n";
    cout << "============================================================\n";

    delete[] sortedArray;
    delete[] reverseArray;
    delete[] randomArray;
    return 0;
}