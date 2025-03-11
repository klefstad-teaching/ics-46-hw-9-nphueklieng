#include "dijkstras.h"

// ------------------- Dijkstra's Shortest Path ---------------------- //

vector<int> dijkstra_shortest_path (const Graph& G, int source, vector<int> & previous) {
    // Dijkstra's Algorithm
    int n = G.numVertices;

    vector<int> distances (n , INF);
    vector<bool> visited (n , false);
    previous.resize(n, UNDEFINED);

    distances[source] = 0;
    previous[source] = UNDEFINED;

    priority_queue< pair<int , int>, vector<pair<int,int>>, greater<pair<int,int>> > min_heap;      // Node {vertex, weight}
    min_heap.push({0 , source});

    while (! min_heap.empty() ) {
        int u = min_heap.top().second;
        min_heap.pop();
        
        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge & edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                min_heap.push({distances[v] , v});
            }
        }
    }
    return distances;   // Runtime COmplexity: O((|E| + |V|) log |V|) for binary heap for PriorityQueue
}

vector<int> extract_shortest_path(const vector<int>& previous, int destination) {
    // Extract from the destination to the source using the previous vector
    vector<int> shortest_path;

    for (int v = destination ; v != UNDEFINED ; v = previous[v])
        shortest_path.push_back(v);

    reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;
}

void print_path (const vector<int> & v, int total) {
    // Print the vector as the path
    for (auto & word : v)
        cout << word << " ";

    cout << endl << "Total cost: " << total << endl;
}
