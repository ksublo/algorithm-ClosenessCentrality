#include "Graph.h"

//class Graph
void Graph::addEdge(int u, int v)
{
    if (u >= adjList.size() || v >= adjList.size())
        adjList.resize(max(u, v) + 1);

    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

vector<int> &Graph::getNeighbors(int u)
{
    return adjList[u];
}

vector<int> Graph::getVertices()
{
    vector<int> vertices;
    for (int i = 0; i < adjList.size(); i++)
    {
        if (!adjList[i].empty()) 
            vertices.push_back(i); 
    }
    return vertices;
}

int Graph::size()
{
    return adjList.size();
}

//class GraphReader
GraphReader::GraphReader(const string &filename): file(filename) {}

Graph GraphReader::readGraph()
{
   Graph g;
   string line;
   int u, v;

    while (getline(file, line)) 
    {
        istringstream iss(line);
        iss >> u >> v;
        g.addEdge(u, v);
    }
    return g;
}

// class GraphAnalyzer
//private
unordered_set<int> GraphAnalyzer::bfs(int start)
{
    unordered_set<int> visited;
    queue<int> q;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) 
    {
        int current = q.front();
        q.pop();

        for (int neighbor : graph.getNeighbors(current)) 
        {
            if (visited.count(neighbor) == 0)
            {
                q.push(neighbor);
                visited.insert(neighbor);
            }
        }
    }
    return visited;
}

unordered_map<int, int> GraphAnalyzer::dijkstra(int start)
{
    unordered_map<int, int> distances;
    unordered_set<int> visited;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push(make_pair(0, start));
    distances[start] = 0;

    while (!pq.empty())
    {
        auto current = pq.top();
        pq.pop();
        int currentDist = current.first;
        int currentVertex = current.second;

        if (visited.count(currentVertex) == 0)
        {
            visited.insert(currentVertex);
            for (int neighbor : graph.getNeighbors(currentVertex))
            {
                if (visited.count(neighbor) == 0)
                {
                    int newDist = currentDist + 1;
                    if (distances.count(neighbor) == 0 || newDist < distances[neighbor])
                    {
                        distances[neighbor] = newDist;
                        pq.push(make_pair(newDist, neighbor));
                    }
                }
            }
        }
    }
    return distances;
}

//public
GraphAnalyzer::GraphAnalyzer(Graph &g) : graph(g) {}

map<int,int> GraphAnalyzer::findLargestComponent()
{
    unordered_set<int> visited;
    unordered_set<int> largestComponent;
    int maxSize = 0;

    for (int v : graph.getVertices()) 
    {
        if (visited.count(v) == 0) 
        {
            unordered_set<int> component = bfs(v);
            visited.insert(component.begin(), component.end());

            if (component.size() > maxSize)
            {
                maxSize = component.size();
                largestComponent = move(component);
            }
        }
    }

    map<int, int> sortedMap;
    for (int vertex : largestComponent)
    {
        sortedMap[vertex] = vertex;
    }

    return sortedMap;
}

void GraphAnalyzer::calculateClosenessCentrality(const map<int, int>& sortedMap)
{
    unordered_map<int, double> closenessCentrality;

    for (const auto& entryX : sortedMap) 
    {
        int x = entryX.first;

        int totalDist = 0;
        unordered_map<int, int> distances = dijkstra(x);

        for (const auto& entryY : sortedMap) 
        {
            int y = entryY.first;

            if (x != y) 
                totalDist += distances[y];  
        }

        closenessCentrality[x] = static_cast<double>(sortedMap.size() - 1) / totalDist;  
        cout << x << "  " << (sortedMap.size() - 1) << "/" << totalDist << "  " << fixed << setprecision(5) << closenessCentrality[x] << "\n";
    }
}