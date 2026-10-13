#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>
#include <climits>

using namespace std;
using namespace chrono;

struct Edge {
    int u, v, weight;
};

// UNION-FIND / DISJOINT SET (for Kruskal)
class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return;

        if (rank[a] < rank[b])
            swap(a, b);

        parent[b] = a;

        if (rank[a] == rank[b])
            rank[a]++;
    }
};

// KRUSKAL'S ALGORITHM
void kruskal(int V, vector<Edge> edges) {
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    DSU dsu(V);
    vector<Edge> mst;
    int totalCost = 0;

    auto start = high_resolution_clock::now();

    for (const Edge &e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            mst.push_back(e);
            totalCost += e.weight;
            dsu.unite(e.u, e.v);

            if ((int)mst.size() == V - 1)
                break;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);

    cout << "\nKRUSKAL'S ALGORITHM\n";

    if ((int)mst.size() != V - 1) {
        cout << "Note: Graph is disconnected. Spanning tree covers only a component.\n";
    }

    cout << "MST Edges:\n";
    for (const Edge &e : mst) {
        cout << "  " << e.u << " - " << e.v << " : weight = " << e.weight << "\n";
    }
    cout << "Total MST Cost = " << totalCost << "\n";
    cout << "Execution Time = " << duration.count() << " ns\n";
}

// PRIM'S ALGORITHM
void prim(int V, const vector<vector<pair<int, int>>> &graph, int startVertex = 0) {
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[startVertex] = 0;
    pq.push({0, startVertex});

    auto start = high_resolution_clock::now();

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        for (auto [v, weight] : graph[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);

    int totalCost = 0;
    cout << "\nPRIM'S ALGORITHM\n";
    cout << "MST Edges (rooted at " << startVertex << "):\n";

    for (int v = 0; v < V; v++) {
        if (v == startVertex) continue;
        if (parent[v] != -1) {
            cout << "  " << parent[v] << " - " << v << " : weight = " << key[v] << "\n";
            totalCost += key[v];
        } else {
            cout << "  Vertex " << v << " is unreachable.\n";
        }
    }
    cout << "Total MST Cost = " << totalCost << "\n";
    cout << "Execution Time = " << duration.count() << " ns\n";
}

// DIJKSTRA'S ALGORITHM
void dijkstra(int V, const vector<vector<pair<int, int>>> &graph, int source) {
    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    auto start = high_resolution_clock::now();

    while (!pq.empty()) {
        int u = pq.top().second;
        int currentDist = pq.top().first;
        pq.pop();

        if (currentDist != dist[u]) continue;

        for (auto [v, weight] : graph[u]) {
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);

    cout << "\nDIJKSTRA'S ALGORITHM\n";
    cout << "Source Vertex = " << source << "\n\n";
    cout << "Shortest Paths from Source:\n";

    for (int i = 0; i < V; i++) {
        cout << "  Target " << i << " : Distance = ";
        if (dist[i] == INT_MAX) {
            cout << "INF (Unreachable)\n";
            continue;
        }

        cout << dist[i] << ", Path = ";

        vector<int> path;
        for (int curr = i; curr != -1; curr = parent[curr]) {
            path.push_back(curr);
        }
        reverse(path.begin(), path.end());

        for (size_t j = 0; j < path.size(); j++) {
            cout << path[j] << (j + 1 < path.size() ? " -> " : "");
        }
        cout << "\n";
    }

    cout << "Execution Time = " << duration.count() << " ns\n";
}

// MAIN FUNCTION
int main() {
    int V, E;

    cout << "Enter number of vertices (V): ";
    if (!(cin >> V) || V <= 0) {
        cout << "Invalid vertex count.\n";
        return 1;
    }

    cout << "Enter number of edges (E): ";
    if (!(cin >> E) || E < 0) {
        cout << "Invalid edge count.\n";
        return 1;
    }

    vector<Edge> edges(E);
    vector<vector<pair<int, int>>> graph(V);

    cout << "\nEnter " << E << " edges (format: u v weight):\n";

    for (int i = 0; i < E; i++) {
        cout << "Edge " << i + 1 << ": ";
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;

        graph[edges[i].u].push_back({edges[i].v, edges[i].weight});
        graph[edges[i].v].push_back({edges[i].u, edges[i].weight});
    }

    int source;
    cout << "\nEnter source vertex for Dijkstra (0 to " << V - 1 << "): ";
    cin >> source;

    kruskal(V, edges);
    prim(V, graph, 0);
    dijkstra(V, graph, source);

    return 0;
}