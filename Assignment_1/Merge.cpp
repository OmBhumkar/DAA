/*
 * Merge Sort
 * Time Complexity : O(n log n) — all cases
 * Space Complexity: O(n) — temporary array used during merging
 *
 * Strategy: Recursively divide the array in half until subarrays of
 * size 1 are reached (base case), then merge them back in sorted order.
 */

// Recursively sort arr[low..high]
void Merge(int a[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        Merge(a, low,     mid);   // sort left half
        Merge(a, mid + 1, high);  // sort right half

        // Merge the two sorted halves into a temporary array
        int* temp = new int[high - low + 1];

        int i = low;     // pointer for left  half
        int j = mid + 1; // pointer for right half
        int k = 0;       // pointer for temp array

        while (i <= mid && j <= high) {
            if (a[i] < a[j]) {
                temp[k] = a[i];
                i++;
            } else {
                temp[k] = a[j];
                j++;
            }
            k++;
        }

        // Copy any remaining elements from the left half
        while (i <= mid) {
            temp[k] = a[i];
            i++;
            k++;
        }

        // Copy any remaining elements from the right half
        while (j <= high) {
            temp[k] = a[j];
            j++;
            k++;
        }

        // Write the merged result back into the original array
        for (i = low, k = 0; i <= high; i++, k++) {
            a[i] = temp[k];
        }
        
        delete[] temp; // free allocated memory
    }
}
