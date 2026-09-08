#include <iostream>
#include <cmath>

using namespace std;

int binarySearch(const int arr[], int low, int high, int key) {
    if (low > high) return -1;
    int mid = low + (high - low) / 2;
    if (arr[mid] == key) return mid;
    if (arr[mid] > key) return binarySearch(arr, low, mid - 1, key);
    return binarySearch(arr, mid + 1, high, key);
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[500], R[500];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

long long sumFactorials(int n) {
    if (n <= 1) return 1;
    return sumFactorials(n - 1) + factorial(n);
}

long long fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

long long sumFibonacci(int n) {
    if (n <= 1) return fib(1);
    return sumFibonacci(n - 1) + fib(n);
}

void evaluateMasterTheorem(double a, double b, double k, bool isPolyLog = false) {
    if (b <= 1) {
        cout << "   [Math Error] b = " << b << " leads to division by zero in log_b(a) (log(1) = 0).\n";
        cout << "   If we approximate b -> 1.0001 (infinitesimal division), log_b(a) -> infinity.\n";
        return;
    }

    double log_b_a = log(a) / log(b);
    cout << "   Hypothetical Parameters: a = " << a << ", b = " << b << ", f(n) = O(n^" << k << ")\n";
    cout << "   Critical Exponent Term: n^(log_b a) = n^" << log_b_a << "\n";

    const double EPS = 1e-6;
    if (k < log_b_a - EPS) {
        cout << "   Result: Case 1 applies [f(n) is smaller than n^(log_b a)] -> T(n) = Theta(n^" << log_b_a << ")\n";
    } else if (fabs(k - log_b_a) < EPS) {
        if (k == 0) cout << "   Result: Case 2 applies [f(n) matches n^(log_b a)] -> T(n) = Theta(log n)\n";
        else cout << "   Result: Case 2 applies [f(n) matches n^(log_b a)] -> T(n) = Theta(n^" << k << " * log n)\n";
    } else {
        cout << "   Result: Case 3 applies [f(n) is larger than n^(log_b a)] -> T(n) = Theta(n^" << k << ")\n";
    }
}

void analyzeAlgorithm(int choice) {
    switch (choice) {
        case 1: { // Binary Search
            cout << "\n--- Algorithm: Binary Search ---\n";
            cout << "Standard Status: Master Theorem is strictly APPLICABLE.\n";
            cout << "Recurrence: T(n) = 1*T(n/2) + O(1)\n";
            evaluateMasterTheorem(1, 2, 0);
            break;
        }
        case 2: { // Merge Sort
            cout << "\n--- Algorithm: Merge Sort ---\n";
            cout << "Standard Status: Master Theorem is strictly APPLICABLE.\n";
            cout << "Recurrence: T(n) = 2*T(n/2) + O(n^1)\n";
            evaluateMasterTheorem(2, 2, 1);
            break;
        }
        case 3: { // Sum of Factorials
            cout << "\n--- Algorithm: Sum of First N Factorials ---\n";
            cout << "Standard Status: Master Theorem CANNOT BE APPLIED.\n";
            cout << "Reason: Recurrence is T(n) = T(n-1) + O(n). Problem shrinks by subtraction, not division.\n";
            cout << "Correct Solution (Iteration/Substitution): T(n) = Theta(n^2)\n";

            int force;
            cout << "\nDo you want to see what happens if we force Master Theorem? (1: Yes, 0: No): ";
            cin >> force;
            if (force == 1) {
                cout << "\n[FORCED ATTEMPT 1: T(n) = 1*T(n/1) + O(n^1) where a=1, b=1, k=1]\n";
                evaluateMasterTheorem(1, 1, 1);

                cout << "\n[FORCED ATTEMPT 2: Treat as an asymptotic boundary with dummy b=2 -> T(n) = 1*T(n/2) + O(n^1)]\n";
                evaluateMasterTheorem(1, 2, 1);
                cout << "   Note: Forced Case 3 gives Theta(n), which fails because true cost is Theta(n^2).\n";
            }
            break;
        }
        case 4: { // Sum of Fibonacci Numbers
            cout << "\n--- Algorithm: Sum of First N Fibonacci Numbers ---\n";
            cout << "Standard Status: Master Theorem CANNOT BE APPLIED.\n";
            cout << "Reason: Recurrence is T(n) = T(n-1) + T(n-2) + O(1) or T(n) = T(n-1) + O(phi^n).\n";
            cout << "Correct Solution (Recursion Tree/Summation): T(n) = Theta(phi^n) ~ Theta(1.618^n)\n";

            int force;
            cout << "\nDo you want to see what happens if we force Master Theorem? (1: Yes, 0: No): ";
            cin >> force;
            if (force == 1) {
                cout << "\n[FORCED ATTEMPT 1: Symmetric Branching Approximation T(n) = 2*T(n/2) + O(1)]\n";
                evaluateMasterTheorem(2, 2, 0);
                cout << "   Note: Forced Case 1 yields Theta(n), which drastically underestimates the exponential Theta(1.618^n).\n";

                cout << "\n[FORCED ATTEMPT 2: Treating as T(n) = 1*T(n/1) + O(phi^n)]\n";
                cout << "   f(n) = O(phi^n) is strictly exponential, violating the polynomial requirement f(n) = Theta(n^k) of standard Master Theorem.\n";
            }
            break;
        }
        case 5:
            cout << "\nExiting Master Theorem Explorer.\n";
            break;
        default:
            cout << "\nInvalid selection. Please choose between 1 and 5.\n";
            break;
    }
}

int main() {
    int arrBS[500], arrMS[500];
    int nBS, key, nMS, nFact, nFib;

    // Execution Run
    cout << "==========================================\n";
    cout << "1. RUNNING RECURSIVE ALGORITHMS\n";
    cout << "==========================================\n";

    cout << "Enter size of sorted array for Binary Search: ";
    cin >> nBS;
    cout << "Enter " << nBS << " sorted integers: ";
    for (int i = 0; i < nBS; i++) cin >> arrBS[i];
    cout << "Enter key to search: ";
    cin >> key;
    int bsIdx = binarySearch(arrBS, 0, nBS - 1, key);
    if (bsIdx != -1) cout << "-> Key found at index: " << bsIdx << "\n";
    else cout << "-> Key not found.\n";

    cout << "\nEnter size of array for Merge Sort: ";
    cin >> nMS;
    cout << "Enter " << nMS << " integers: ";
    for (int i = 0; i < nMS; i++) cin >> arrMS[i];
    mergeSort(arrMS, 0, nMS - 1);
    cout << "-> Sorted Array: ";
    for (int i = 0; i < nMS; i++) cout << arrMS[i] << " ";
    cout << "\n";

    cout << "\nEnter N for Factorial Sum: ";
    cin >> nFact;
    cout << "-> Sum of first " << nFact << " factorials: " << sumFactorials(nFact) << "\n";

    cout << "\nEnter N for Fibonacci Sum: ";
    cin >> nFib;
    cout << "-> Sum of first " << nFib << " Fibonacci numbers: " << sumFibonacci(nFib) << "\n";

    int choice;
    do {
        cout << "\n==========================================\n";
        cout << "2. MASTER THEOREM EXPLORER\n";
        cout << "==========================================\n";
        cout << "1. Binary Search Analysis\n";
        cout << "2. Merge Sort Analysis\n";
        cout << "3. Sum of Factorials Analysis\n";
        cout << "4. Sum of Fibonacci Analysis\n";
        cout << "5. Exit Explorer\n";
        cout << "Choose algorithm (1-5): ";
        cin >> choice;

        analyzeAlgorithm(choice);
    } while (choice != 5);

    return 0;
}