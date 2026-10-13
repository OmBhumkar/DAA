#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// The Promising() function must be separate, checking columns and diagonals
bool Promising(int row, int col, const vector<int>& position) {
    // We only need to check the rows above the current 'row'
    for (int i = 0; i < row; i++) {
        // Check for same-column clash OR diagonal clash
        // Two queens are on the same diagonal if |row - i| == |col - position[i]|
        if (position[i] == col || abs(row - i) == abs(col - position[i])) {
            return false;
        }
    }
    return true;
}

// Backtracking function to place queens
void NQueens(int row, int N, vector<int>& position, int& solutionCount) {
    // Base case: If all N queens are placed successfully
    if (row == N) {
        solutionCount++;
        cout << "Solution " << solutionCount << ":  [ ";
        for (int i = 0; i < N; i++) {
            cout << position[i] << " ";
        }
        cout << "]\n";
        return;
    }

    // Try placing a queen in all columns for the current row
    for (int col = 0; col < N; col++) {
        if (Promising(row, col, position)) {
            position[row] = col; // Place the queen
            
            // Recursively place queens in the remaining rows
            NQueens(row + 1, N, position, solutionCount);
            
            // Backtracking happens implicitly here: 
            // the loop moves to the next column, overwriting position[row]
        }
    }
}

int main() {
    int N;
    cout << "Enter the value of N: ";
    cin >> N; // Accept N as user input at runtime

    if (N < 1) {
        cout << "N must be >= 1.\n";
        return 0;
    }

    // 1-D array: position[i] stores the column index of the queen placed in row i
    vector<int> position(N, 0);
    int solutionCount = 0;

    // Start placing queens from row 0
    NQueens(0, N, position, solutionCount);

    // Calculate total brute-force arrangements (N^N)
    // Using long long to prevent overflow for slightly larger N values
    long long bruteForceCount = pow(N, N);

    // Print the total number of solutions found
    cout << "Total solutions for N = " << N << " : " << solutionCount << "\n";
    cout << "Brute-force arrangements checked: " << bruteForceCount << "\n";

    return 0;
}