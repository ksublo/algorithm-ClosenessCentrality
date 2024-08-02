#include <chrono>
#include "Graph.h"

using namespace std;

int main() 
{
    string filename = "graph.txt"; 

    auto start = chrono::steady_clock::now();

    // Step 1: Read the graph from a text file
    GraphReader reader(filename);
    Graph g = reader.readGraph();
    cout << "graph uploaded" << endl;

    // Step 2: Find the largest component in the graph
    GraphAnalyzer analyzer(g);
    map<int,int> largestComponent = analyzer.findLargestComponent();
    cout << "the largest component was founded" << endl;
    
    // Step 3: Calculate the closeness centrality for the vertices in the largest component
    cout << "closeness centrality: " << endl;
    cout << " id  -------------- closeness centrality" << endl;
    analyzer.calculateClosenessCentrality(largestComponent);
    cout << "closeness centrality was founded" << endl;

    auto end = chrono::steady_clock::now();

    cout << "Time: " << chrono::duration_cast<chrono::minutes>(end - start).count() << " min" << endl;

    return 0;
}

/* compilation
g++ main.cpp Graph.cpp Grah.h -O3 -o project
./project
*/