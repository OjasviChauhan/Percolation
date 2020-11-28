#include <bits/stdc++.h>
using namespace std;

class Graph{
    int V;
    list<pair<int,int>> l;
    
    public:
        Graph(int V){
            this->V = V;
        }
        
        void addEdge(int u,int v){
            l.push_back(make_pair(u,v));
        }
        
        int findSet(int i,int parent[]){
            if(parent[i]==-1){
                return i;
            }
            return parent[i] = findSet(parent[i],parent);
        }
    
        void unionSet(int x,int y,int parent[],int rank[]){
            int s1 = findSet(x,parent);
            int s2 = findSet(y,parent);
            
            if(s1!=s2){
                if(rank[s1]<rank[s2]){
                    parent[s1] = s2;
                    rank[s2] += rank[s1];
                }
                else{
                    parent[s2] = s1;
                    rank[s1] += rank[s2];
                }
            }
        }
};

int main(){
    int V;
    cin>>V;
    
    int *parent = new int[V];
    int *rank = new int[V];
    
    for(int i=0;i<V;i++){
        parent[i] = -1;
        rank[i] = 1;
    }
    
    Graph g(V);
    for(int i=0;i<V;i++){
        int u,v;
        cin>>u>>v;
        g.addEdge(u,v);
    }
    cout<<g.findSet(1,parent)<<endl;
    
return 0;
}
