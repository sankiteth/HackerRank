#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<vi> vvi;

void dfs_visit(vvi& adj, vb& visited, vi& components, int source, int component){
    visited[source] = true;
    components[source] = component;
    
    for(auto i = adj[source].begin(); i != adj[source].end(); i++){
        if(!visited[*i]){
            dfs_visit(adj, visited, components, *i, component);
        }    
    }
}

int dfs(vvi& adj, vb& visited, vi& components,  int& num_nodes){
    int component = 0;
    for(int i=0; i<num_nodes; i++){
        if(!visited[i]){ // if current node not visited, start a dfs from current node
            dfs_visit(adj, visited, components, i, component);
            component++;
        }
    }
    
    return component;
}

int main() {
    int q;
    cin >> q;
    for(int i=0; i<q; i++){
        int num_cities, num_roads; double c_lib, c_road;
        cin >> num_cities >> num_roads >> c_lib >> c_road;
        
        vvi adj(num_cities, vector<int>());
        for(int i=0; i<num_roads; i++){
            int u, v;
            cin >> u >> v;
            u--; v--; // change 0-indexed
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        if(c_lib <= c_road){ // build library at each city
            cout << fixed << setprecision(0) << (double)(num_cities*c_lib) << endl;
        }
        else{ // build one library, and (num_nodes_in_comp-1) roads in each component
            vb visited(num_cities, false);
            vi components(num_cities); // which component each city lies in
            int num_comps = dfs(adj, visited, components, num_cities); // return number of components
            vi comp_map(num_comps, 0); // number of nodes in each component
            for(int i=0; i<num_cities; i++){
                comp_map[ components[i] ]++;
            }
            
            double cost = 0;
            for(int i=0; i<num_comps; i++){
                cost += (c_lib + (double)( ( comp_map[i]-1 )*c_road ) ); // 1 library for each coponent, and num_roads = 
                // num_nodes in component - 1
            }
            
            cout << fixed << setprecision(0) << cost << endl;
        }
    }
    return 0;
}
