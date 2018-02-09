#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool comp (string i, string j) 
{ 
    int n=i.length();
    int m=j.length();
    if(n==m)
        return (i<j);
    else
        return (n<m);   
}

int main() {
    int n;
    cin >> n;
    vector<string> v(n);
    for(int i=0; i<n; i++){
        cin >> v[i];
    }
    
    sort(v.begin(), v.end(), comp);
    for(int i=0; i<n; i++){
        cout << v[i] << endl;
    }
    return 0;
}