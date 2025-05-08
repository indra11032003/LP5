#include<iostream>
using namespace std;
#include<stack>
#include<queue>
#include<omp.h>
#include<unordered_set>

class Graph{

    public:
        vector<vector<int>> adj;
        int V;

        Graph(int V){
            this->V=V;
            adj.resize(V);
        }
        void addEdge(int u,int v){
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        void pbfs(int start){
            vector<bool> visited(V,false);
            queue<int> q;
            visited[start] = true;
            q.push(start);
    
            cout << "Parallel BFS starting from node " << start << ": ";
            while(!q.empty()){
                int sz=q.size();
                vector<int> next_level;
                #pragma omp parallel for
                for(int i=0;i<sz;i++){
                    int node;
                    #pragma omp critical
                    {
                        node = q.front();
                        q.pop();
                        cout << node << " ";
                    }

                    #pragma omp parallel for
                    for(int j=0;j<adj[node].size();j++){
                        int neighbor=adj[node][j];
                       if(!visited[neighbor]){
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
            cout<< endl;
        }

       // cout<< endl;

};

int main() {
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    g.pbfs(0);
    //g.parallelDFS(0);

    return 0;
}