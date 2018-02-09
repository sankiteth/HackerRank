#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <iomanip>
using namespace std;

class Disjoint_Set{ // Disjoint set data structure with path compression and rank by union
  public:
    vector<int> parent;
    vector<int> rank; // rank of each node, so that when merging 2 trees in union_set, we can make the smaller tree
    int num;          // the subtree of the larger tree
    
    Disjoint_Set(int n) : num(n){
        rank = vector<int>(n, 0);
        parent = vector<int>(n);
        for(int i=0; i<num; i++){
            parent[i] = i;
        }
    }
    
    int find_set(int u){
        if(parent[u] == u){ // has no parent; single till now
            return u;
        }
        else{
            int u_set = find_set(parent[u]); // recusively go up the tree to find the final root of the tree   
            parent[u] = u_set; // path compression - make parent of u u_set, so that next time query returns in O(1)
            return u_set;
        }
    }
    
    void union_set(int u, int v){
        int u_set = find_set(u);
        int v_set = find_set(v);
        
        // Attach smaller rank tree under root of high rank tree
        // (Union by Rank)
        if (rank[u_set] < rank[v_set]){
            parent[u_set] = v_set;
        }
        else if (rank[u_set] > rank[v_set]){
            parent[v_set] = u_set;   
        }
        else{ // If ranks are same, then make one as root and increment its rank by one
            parent[v_set] = u_set;
            rank[u_set]++;
        }
    }
};

int main() {
    int N, P;
    cin >> N >> P;
    vector<pair<int, int> > edges(P);
    for(int i=0; i<P; i++){
        int u, v;
        cin >> u >> v;
        edges[i] = make_pair(u, v);
    }
    
    Disjoint_Set df(N);
    for(int i=0; i<P; i++){
        int u = edges[i].first;
        int v = edges[i].second;

        if(df.find_set(u) != df.find_set(v)){
            df.union_set(u, v);
        }
    }
    
    vector<int> components(N, 0); // nodes belonging to the same component will belong to the same set
    for(int i=0; i<N; i++){
        int comp = df.find_set(i);
        components[comp]++;
    }
    
    vector<int> groups;
    for(int i=0; i<N; i++){
        if(components[i] > 0){
            groups.push_back(components[i]);
        }
    }
    
    long long int sum = 0;
    long long int result = 0;
    for(int i=0; i<groups.size(); i++){
        result += sum*groups[i];
        sum += groups[i];
    }
    
    cout << fixed << setprecision(0) << result << endl;
    return 0;
}
