
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// ---------- Binary Search ----------
// Returns index of key if found, else -1. Increments 'comparisons' once per element compared.
long long binarySearch(const vector<long long> &a, long long key, long long &comparisons) {
    long long low = 0, high = (long long)a.size() - 1;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        comparisons++;
        if (a[mid] == key) {
            return mid;
        } else if (a[mid] < key) {
            low = mid + 1;   // discard left half
        } else {
            high = mid - 1;  // discard right half
        }
    }
    return -1;
}

// ---------- Linear Search ----------
long long linearSearch(const vector<long long> &a, long long key, long long &comparisons) {
    for (long long i = 0; i < (long long)a.size(); i++) {
        comparisons++;
        if (a[i] == key) return i;
    }
    return -1;
}

// Generates a sorted array: 2, 4, 6, ..., 2n
vector<long long> generateSortedArray(long long n) {
    vector<long long> a(n);
    for (long long i = 0; i < n; i++) a[i] = 2 * (i + 1);
    return a;
}

void runSortedArrayAnalysis() {
    long long n;
    cout << "\nEnter input size n: ";
    cin >> n;
    if (n <= 0) {
        cout << "n must be positive.\n";
        return;
    }

    vector<long long> arr = generateSortedArray(n);
    long long key = arr[n - 1]; // worst case: last element = 2n

    const int RUNS = 3;
    long long totalBinComp = 0, totalLinComp = 0;
    double totalBinTime = 0.0, totalLinTime = 0.0;

    for (int r = 0; r < RUNS; r++) {
        long long binComparisons = 0, linComparisons = 0;

        auto t1 = high_resolution_clock::now();
        long long binIndex = binarySearch(arr, key, binComparisons);
        auto t2 = high_resolution_clock::now();
        double binTime = duration<double, micro>(t2 - t1).count();

        auto t3 = high_resolution_clock::now();
        long long linIndex = linearSearch(arr, key, linComparisons);
        auto t4 = high_resolution_clock::now();
        double linTime = duration<double, micro>(t4 - t3).count();

        totalBinComp += binComparisons;
        totalLinComp += linComparisons;
        totalBinTime += binTime;
        totalLinTime += linTime;

        (void)binIndex; (void)linIndex; // indices not needed for output
    }

    cout << fixed << setprecision(3);
    cout << "\n--- Results for n = " << n << " (averaged over " << RUNS << " runs) ---\n";
    cout << "Key searched (last element, worst case) : " << key << "\n\n";

    cout << "Binary Search : comparisons = " << (totalBinComp / RUNS)
         << " | avg time = " << (totalBinTime / RUNS) << " microseconds\n";
    cout << "Linear Search : comparisons = " << (totalLinComp / RUNS)
         << " | avg time = " << (totalLinTime / RUNS) << " microseconds\n";
}

void runUnsortedArrayDemo() {
    // Deliberately unsorted array containing the same values used in the report's Table C
    vector<long long> arr = {50, 200, 6208, 30, 999, 4, 777, 1500, 12, 6666};

    cout << "\n--- Unsorted array demonstration ---\n";
    cout << "Array: ";
    for (auto v : arr) cout << v << " ";
    cout << "\n\n";

    vector<long long> testKeys = {126, 1268, 6208, 30};

    for (long long key : testKeys) {
        long long comparisons = 0;
        long long result = binarySearch(arr, key, comparisons);

        bool actuallyPresent = find(arr.begin(), arr.end(), key) != arr.end();

        cout << "Key = " << key
             << " | Binary Search result = " << result
             << " | Actually present? " << (actuallyPresent ? "Y" : "N")
             << " | Correct? " << (((result != -1) == actuallyPresent) ? "Y" : "N")
             << "\n";
    }

    cout << "\nNote: Binary Search can incorrectly report a present key as absent (-1)\n"
         << "when the array is not sorted, because discarding a half at each step\n"
         << "relies entirely on the ordering property.\n";
}

int main() {
    int choice;
    cout << "=================================================\n";
    cout << " Binary Search vs Linear Search - Efficiency Study\n";
    cout << "=================================================\n";
    cout << "1. Analyze sorted array (comparisons + timing)\n";
    cout << "2. Demonstrate behaviour on unsorted array\n";
    cout << "3. Both\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1 || choice == 3) runSortedArrayAnalysis();
    if (choice == 2 || choice == 3) runUnsortedArrayDemo();

    return 0;
}
