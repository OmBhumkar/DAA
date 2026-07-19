/*
 * Sort.cpp — Driver / Timing Harness
 *
 * Measures and prints the wall-clock time (in seconds) taken by each of the
 * six sorting algorithms across six different input sizes.
 *
 * Input sizes  : 1, 10, 100, 1000, 10000, 100000
 * Each algorithm receives the SAME random array (cloned before each run)
 * so the comparison is fair.
 *
 * Algorithms timed:
 *   Bubble    — O(n^2)
 *   Selection — O(n^2)
 *   Insertion — O(n^2)
 *   Merge     — O(n log n)
 *   Quick     — O(n log n) average
 *   Heap      — O(n log n)
 */
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <iomanip>

// Function declarations
void Bubble(int a[], int n);
void Selection(int a[], int n);
void Insertion(int a[], int n);
void Merge(int a[], int low, int high);
void Quick(int a[], int low, int high);
void Heap(int a[], int n);

// Utility to copy array
void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

int main() {
    int sizes[] = {1, 10, 100, 1000, 10000, 100000};
    int num_sizes = 6;

    // Table header — tab-separated for easy copy-paste
    std::cout << "Size\t\tBubble(s)\tSelection(s)\tInsertion(s)\tMerge(s)\tQuick(s)\tHeap(s)\n";
    std::cout << "--------------------------------------------------------------------------------------------------------------------------\n";

    srand(time(NULL));

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        
        // Generate a random array of size n
        int* a = new int[n];
        for (int j = 0; j < n; j++) {
            a[j] = rand() % 100000;
        }

        int* c = new int[n];   // working copy — always cloned from the same original array
        clock_t start, end;

        // --- Bubble Sort ---
        copyArray(a, c, n);
        start = clock();
        Bubble(c, n);
        end = clock();
        double bubble = (double)(end - start) / CLOCKS_PER_SEC;

        // --- Selection Sort ---
        copyArray(a, c, n);
        start = clock();
        Selection(c, n);
        end = clock();
        double selection = (double)(end - start) / CLOCKS_PER_SEC;

        // --- Insertion Sort ---
        copyArray(a, c, n);
        start = clock();
        Insertion(c, n);
        end = clock();
        double insertion = (double)(end - start) / CLOCKS_PER_SEC;

        // --- Merge Sort ---
        copyArray(a, c, n);
        start = clock();
        Merge(c, 0, n - 1);
        end = clock();
        double merge = (double)(end - start) / CLOCKS_PER_SEC;

        // --- Quick Sort ---
        copyArray(a, c, n);
        start = clock();
        Quick(c, 0, n - 1);
        end = clock();
        double quick = (double)(end - start) / CLOCKS_PER_SEC;

        // --- Heap Sort ---
        copyArray(a, c, n);
        start = clock();
        Heap(c, n);
        end = clock();
        double heap = (double)(end - start) / CLOCKS_PER_SEC;

        // Print one row
        std::cout << std::left << std::setw(10) << n << "\t"
                  << std::fixed << std::setprecision(9) 
                  << bubble << "\t"
                  << selection << "\t"
                  << insertion << "\t"
                  << merge << "\t"
                  << quick << "\t"
                  << heap << "\n";

        delete[] a;
        delete[] c;
    }

    return 0;
}
