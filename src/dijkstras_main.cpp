#include "dijkstras.h"

int main () {

    string filename = "./src/small.txt";
    Graph G;
    file_to_graph (filename , G);
    int source = 0;


    vector<int> previous (G.numVertices , UNDEFINED);
    vector<int> distances = dijkstra_shortest_path(G , source, previous);

    for (int i = 0 ; i  < G.numVertices ; ++ i) {
        vector<int> shortest_path = extract_shortest_path (previous, i);
        print_path(shortest_path , distances[i]);
    }

    return 0;
}