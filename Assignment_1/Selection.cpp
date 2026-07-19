/*
 * Selection Sort
 * Time Complexity : O(n^2) — all cases
 * Space Complexity: O(1) — in-place
 *
 * Strategy: Divide the array into a sorted and an unsorted region.
 * In each pass, find the minimum element in the unsorted region and
 * swap it with the first element of that region.
 */
void Selection(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;  // index of the minimum element in unsorted region

        // Find the minimum in the unsorted region a[i+1..n-1]
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }

        // Swap the found minimum with the first unsorted element
        int temp = a[i];
        a[i]     = a[min];
        a[min]   = temp;
    }
}
