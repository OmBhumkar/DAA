#include <iostream>
#include <vector>

using namespace std;

// The isSafe() function checks if the current color assignment is valid
bool isSafe(int vertex, int c, const vector<vector<int>>& graph, const vector<int>& color, int V) {
    for (int i = 0; i < V; i++) {
        // Two vertices connected by an edge MUST have different colors
        if (graph[vertex][i] == 1 && c == color[i]) {
            return false;
        }
    }
    return true;
}

// Backtracking function to assign colors vertex by vertex
bool graphColor(int vertex, int m, const vector<vector<int>>& graph, vector<int>& color, int V) {
    // Base case: If all vertices are assigned a color, return true
    if (vertex == V) {
        return true;
    }

    // Try all possible colorings using Backtracking from 1 to m
    for (int c = 1; c <= m; c++) {
        if (isSafe(vertex, c, graph, color, V)) {
            color[vertex] = c; // Assign the color

            // Recursive call to color the next vertex
            if (graphColor(vertex + 1, m, graph, color, V)) {
                return true; 
            }

            // Un-assign step (backtrack) if the choice does not lead to a solution
            color[vertex] = 0;
        }
    }

    // Return false if no color can be assigned to the current vertex
    return false;
}

int main() {
    int V, m;
    
    // Accept V, m, and the adjacency matrix as user input at runtime
    cout << "Enter number of vertices: ";
    cin >> V;
    
    cout << "Enter number of colors (m): ";
    cin >> m;
    
    vector<vector<int>> graph(V, vector<int>(V));
    cout << "Enter adjacency matrix (row by row):\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
        }
    }

    // Initialize all color assignments to 0 (unassigned)
    vector<int> color(V, 0);

    // The algorithm must assign colors starting from vertex 0
    if (graphColor(0, m, graph, color, V)) {
        // Print the color assignment as individual vertex->color lines
        cout << "\nGraph Coloring Solution:\n";
        for (int i = 0; i < V; i++) {
            cout << "color[" << i << "] = " << color[i] << "\n";
        }
        
        // Print each solution as a 1-D array
        cout << "\nSolution array: [ ";
        for (int i = 0; i < V; i++) {
            cout << color[i] << " ";
        }
        cout << "]\n";
    } else {
        // Report that no solution exists with m colors if applicable
        cout << "\nNo solution exists with " << m << " colors for this graph.\n";
    }

    return 0;
}