/*
 * Bubble Sort
 * Time Complexity : O(n^2) — all cases (no early-exit optimization)
 * Space Complexity: O(1) — in-place
 *
 * Strategy: Repeatedly compare adjacent elements and swap them
 * if they are in the wrong order. Each pass "bubbles" the largest
 * unsorted element to its correct position at the end.
 */
void Bubble(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // After i passes, the last i elements are already sorted
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                // Swap adjacent elements
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}
