#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>
#include <unordered_set>
using namespace std;

class Graph {
public:
    int V;
    vector<vector<int>> adj;

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected graph
    }

    void parallelBFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "Parallel BFS starting from node " << start << ": ";

        while (!q.empty()) {
            int sz = q.size();
            vector<int> next_level;

            #pragma omp parallel for
            for (int i = 0; i < sz; i++) {
                int node;
                #pragma omp critical
                {
                    if (!q.empty()) {
                        node = q.front();
                        q.pop();
                        cout << node << " ";
                    }
                }

                #pragma omp parallel for
                for (int j = 0; j < adj[node].size(); j++) {
                    int neighbor = adj[node][j];
                    if (!visited[neighbor]) {
                        #pragma omp critical
                        {
                            if (!visited[neighbor]) {
                                visited[neighbor] = true;
                                next_level.push_back(neighbor);
                            }
                        }
                    }
                }
            }

            for (int n : next_level) {
                q.push(n);
            }
        }
        cout << endl;
    }




    void parallelDFSUtil(int v, vector<bool>& visited) {
        #pragma omp critical
        {
            if (!visited[v]) {
                visited[v] = true;
                cout << v << " ";
            }
        }

        #pragma omp parallel for
        for (int i = 0; i < adj[v].size(); i++) {
            int neighbor = adj[v][i];
            if (!visited[neighbor]) {
                parallelDFSUtil(neighbor, visited);
            }
        }
    }

    void parallelDFS(int start) {
        vector<bool> visited(V, false);
        cout << "Parallel DFS starting from node " << start << ": ";
        parallelDFSUtil(start, visited);
        cout << endl;
    }
};

int main() {
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    g.parallelBFS(0);
    g.parallelDFS(0);

    return 0;
}
