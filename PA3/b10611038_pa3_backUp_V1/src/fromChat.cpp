#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <list>
#include <climits> // For INT_MAX

using namespace std;

class Graph {
public:
    map<int, list<pair<int, int>>> adjList; // Adjacency list with weights (node -> [(neighbor, weight)])

    // Function to add an edge with a weight
    void add_edge_weighted(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // Undirected graph
    }

    // Function to print the adjacency list representation
    void print() {
        cout << "Adjacency list for the Graph: " << endl;
        for (auto i : adjList) {
            cout << i.first << " -> ";
            for (auto j : i.second) {
                cout << "(" << j.first << ", " << j.second << ") ";
            }
            cout << endl;
        }
    }

    // Prim's MST Algorithm
    void prim_mst(int start) {
        map<int, int> key; // Min weight to connect each node
        map<int, int> parent; // Parent of each node in the MST
        map<int, bool> inMST; // Tracks if a node is included in MST

        // Priority queue for edges (min-heap based on weight)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Initialize all keys as infinite and parents as -1
        for (auto i : adjList) {
            key[i.first] = INT_MAX;
            parent[i.first] = -1;
            inMST[i.first] = false;
        }

        // Start from the given node
        key[start] = 0;
        pq.push({0, start}); // Push the start node with weight 0

        while (!pq.empty()) {
            int u = pq.top().second; // Get the node with the smallest key
            pq.pop();

            // If the node is already in MST, skip
            if (inMST[u]) continue;

            inMST[u] = true; // Include the node in MST

            // Traverse all neighbors of u
            for (auto neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                // If v is not in MST and weight of (u, v) is smaller than current key of v
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push({key[v], v}); // Push updated key and node
                }
            }
        }

        // Print the MST
        cout << "Minimum Spanning Tree (MST):" << endl;
        int total_weight = 0;
        for (auto i : adjList) {
            int node = i.first;
            if (parent[node] != -1) { // Exclude the root node
                cout << parent[node] << " - " << node << " (Weight: " << key[node] << ")" << endl;
                total_weight += key[node];
            }
        }
        cout << "Total Weight of MST: " << total_weight << endl;
    }
};

// Example Usage
int main() {
    Graph g;
    g.add_edge_weighted(0, 1, 4);
    g.add_edge_weighted(0, 2, 3);
    g.add_edge_weighted(1, 2, 1);
    g.add_edge_weighted(1, 3, 2);
    g.add_edge_weighted(2, 3, 4);
    g.add_edge_weighted(3, 4, 2);
    g.add_edge_weighted(4, 5, 6);

    g.print();
    g.prim_mst(0);

    return 0;
}
