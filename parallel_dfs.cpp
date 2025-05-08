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

    void parallelDfsUtil(vector<bool> visited,int v){

        #pragma omp critical
        {
            if(!visited[v]){
                visited[v]=true;
                cout<<v<<" ";
            }
        }

        #pragma omp parallel for
        for(int i=0;i<adj[v].size();i++){
            int neighbor=adj[v][i];
            if(!visited[neighbor]){
                    parallelDfsUtil(visited,neighbor);
                }      
        
        }
    }

    void parallelDfs(int start){
        vector<bool> visited(V,false);
        //cout<<"dfs:"<<start;
        parallelDfsUtil(visited,start);
        cout<<endl;
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

    //g.parallelBFS(0);
    g.parallelDfs(0);

    return 0;
}
