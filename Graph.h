#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <iomanip>

using namespace std;

/**
 * @brief A class Graph representing a graph.
 *
 * This class uses an adjacency list to represent the graph.
 */
class Graph
{
private:
    vector<vector<int>> adjList;
public:
     /**
     * @brief Add an edge between two vertices in the graph.
     *
     * @param u The index of the first vertex.
     * @param v The index of the second vertex.
     */
    void addEdge(int u, int v);
     /**
     * @brief Get the neighbors of a vertex in the graph.
     *
     * @param u The index of the vertex.
     * @return A reference to the vector of neighboring vertices.
     */
    vector<int>& getNeighbors(int u);
     /**
     * @brief Get a vector of all the vertices in the graph.
     *
     * @return A vector of the indices of all the vertices in the graph.
     */
    vector<int> getVertices();
     /**
     * @brief Get the number of vertices in the graph.
     *
     * @return The number of vertices in the graph.
     */
    int size();
};

/**
 * @brief A class for reading a graph from a file.
 */
class GraphReader 
{
private:
    ifstream file;
public:
    /**
     * @brief Construct a GraphReader object.
     *
     * @param filename The name of the file containing the graph data.
     */
    GraphReader(const string& filename);
    /**
     * @brief Read a graph from the file.
     *
     * @return The graph represented by the file data.
     */
    Graph readGraph();
};

/**
 * @brief A class for analyzing graphs.
 */
class GraphAnalyzer 
{
private:
    Graph& graph;
     /**
     * @brief Perform a breadth-first search starting at a given vertex.
     *
     * @param start The index of the starting vertex.
     * @return An unordered set containing the indices of all vertices in the connected component containing the starting vertex.
     */
    unordered_set<int> bfs(int start);
     /**
     * @brief Calculate the shortest path distances from a given vertex to all other vertices using Dijkstra's algorithm.
     *
     * @param start The index of the starting vertex.
     * @return An unordered map containing the shortest path distances to all other vertices.
     */
    unordered_map<int, int> dijkstra(int start);
public:
     /**
     * @brief Construct a GraphAnalyzer object.
     *
     * @param g The graph to analyze.
     */
    GraphAnalyzer(Graph& g);
    /**
     * @brief Find the largest connected component in the graph.
     *
     * @return A map containing the indices of all vertices in the largest connected component, sorted in increasing order.
     */
    map<int,int> findLargestComponent();
     /**
     * @brief Calculate the closeness centrality for each vertex in the largest connected component.
     *
     * @param sortedMap A map containing the indices of all vertices in the largest connected component, sorted in increasing order.
     */
    void calculateClosenessCentrality(const map<int,int>& sortedMap);
};
