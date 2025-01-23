#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

// Define a structure for edges
struct Edge {
    int to;
    int weight;
};

// Graph representation
class Graph {
private:
    unordered_map<int, vector<Edge>> adjList; // Adjacency list

public:
    void addEdge(int from, int to, int weight) {
        adjList[from].push_back({to, weight});
        adjList[to].push_back({from, weight}); // For undirected graph
    }

    vector<Edge> getNeighbors(int node) {
        return adjList[node];
    }

    void updateWeight(int from, int to, int newWeight) {
        for (auto &edge : adjList[from]) {
            if (edge.to == to) {
                edge.weight = newWeight;
                break;
            }
        }
        for (auto &edge : adjList[to]) {
            if (edge.to == from) {
                edge.weight = newWeight;
                break;
            }
        }
    }
};

// Dijkstra's algorithm for shortest path
vector<int> dijkstra(Graph &graph, int start, int nodes) {
    vector<int> distances(nodes, numeric_limits<int>::max());
    distances[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // Min-heap
    pq.push({0, start});

    while (!pq.empty()) {
        auto [currentDist, currentNode] = pq.top();
        pq.pop();

        for (const auto &edge : graph.getNeighbors(currentNode)) {
            int newDist = currentDist + edge.weight;
            if (newDist < distances[edge.to]) {
                distances[edge.to] = newDist;
                pq.push({newDist, edge.to});
            }
        }
    }

    return distances;
}

int main() {
    Graph graph;
    int nodes = 6; // Example graph with 6 nodes

    // Adding edges
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 8);
    graph.addEdge(3, 4, 3);
    graph.addEdge(4, 5, 6);

    int start = 0, destination = 5;

    // Initial shortest path
    vector<int> distances = dijkstra(graph, start, nodes);
    cout << "Initial shortest path from node " << start << " to node " << destination << " is: " << distances[destination] << endl;

    // Simulating congestion by updating weights
    cout << "Updating weight between node 2 and node 3 to simulate congestion." << endl;
    graph.updateWeight(2, 3, 15);

    // Recalculate shortest path
    distances = dijkstra(graph, start, nodes);
    cout << "Updated shortest path from node " << start << " to node " << destination << " is: " << distances[destination] << endl;

    return 0;
}
