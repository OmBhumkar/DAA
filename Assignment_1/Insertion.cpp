/*
 * Insertion Sort
 * Time Complexity : O(n^2) worst/average, O(n) best (already sorted)
 * Space Complexity: O(1) — in-place
 *
 * Strategy: Build the sorted array one element at a time. For each
 * element, shift all larger elements in the sorted region one position
 * to the right, then insert the element in its correct position.
 */
void Insertion(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];  // element to be inserted into the sorted region
        int j   = i - 1;

        // Shift elements greater than key one position to the right
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;  // insert key at its correct position
    }
}
