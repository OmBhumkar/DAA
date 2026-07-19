/*
 * Heap Sort
 * Time Complexity : O(n log n) — all cases
 * Space Complexity: O(1) — in-place, no extra array needed
 *
 * Strategy: Build a max-heap from the array, then repeatedly extract
 * the maximum element (root) and place it at the end of the array.
 */

// Heapify the subtree rooted at index i in an array of logical size n
// Ensures the max-heap property: parent >= both children
void heapify(int a[], int n, int i) {
    int largest = i;        // assume root is largest
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;

    // Check if left child exists and is greater than current largest
    if (left < n && a[left] > a[largest]) {
        largest = left;
    }

    // Check if right child exists and is greater than current largest
    if (right < n && a[right] > a[largest]) {
        largest = right;
    }

    // If the largest is not the root, swap and continue heapifying downward
    if (largest != i) {
        int temp   = a[i];
        a[i]       = a[largest];
        a[largest] = temp;

        heapify(a, n, largest);
    }
}

// Main heap sort function
void Heap(int a[], int n) {
    // Phase 1: Build max-heap (bottom-up, start from last non-leaf)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i);
    }

    // Phase 2: Extract elements one by one from the heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root (maximum) to the end
        int temp = a[0];
        a[0]     = a[i];
        a[i]     = temp;

        // Heapify the reduced heap (exclude the sorted tail)
        heapify(a, i, 0);
    }
}
