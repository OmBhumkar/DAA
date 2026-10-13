#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const long long INF = 1e9;

int main() {
    int V, E;

    cin >> V;
    cin >> E;

    vector<vector<long long>> dist(V, vector<long long>(V, INF));

    for (int i = 0; i < V; i++) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < E; i++) {
        int u, v;
        long long w;

        cin >> u >> v >> w;

        dist[u][v] = w;
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {

                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(
                        dist[i][j],
                        dist[i][k] + dist[k][j]
                    );
                }
            }
        }
    }

    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            cout << "ERROR: Negative Cycle Detected" << endl;
            return 0;
        }
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {

            if (dist[i][j] == INF)
                cout << "INF";
            else
                cout << dist[i][j];

            if (j != V - 1)
                cout << " ";
        }

        cout << endl;
    }

    return 0;
}