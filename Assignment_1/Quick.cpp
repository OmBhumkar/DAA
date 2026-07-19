/*
 * Quick Sort
 * Time Complexity : O(n log n) average, O(n^2) worst case
 * Space Complexity: O(log n) — recursive call stack
 *
 * Strategy: Pick a pivot, partition array so elements less than pivot
 * go left and greater go right, then recursively sort both halves.
 */

// Partitions arr[low..high] around a pivot (last element)
// Returns the final index of the pivot after partitioning
int partition(int a[], int low, int high) {
    int pivot = a[high];   // choose last element as pivot
    int i = low - 1;       // i tracks the boundary of the "less-than" region

    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) {
            i++;
            // swap a[i] and a[j]
            int temp = a[i];
            a[i]    = a[j];
            a[j]    = temp;
        }
    }

    // Place pivot in its correct sorted position
    int temp   = a[i + 1];
    a[i + 1]   = a[high];
    a[high]    = temp;

    return i + 1;  // pivot's final index
}

// Recursively sort the sub-array arr[low..high]
void Quick(int a[], int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);  // partition index

        Quick(a, low,    pi - 1);  // sort left of pivot
        Quick(a, pi + 1, high);    // sort right of pivot
    }
}
