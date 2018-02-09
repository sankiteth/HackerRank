#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// greedily cover the houses with radios, starting from left
int main() {
    int n, k;
    cin >> n >> k;
    vector<int> houses(n);
    for(int i=0; i<n; i++){
        cin >> houses[i];
    }
    
    sort(houses.begin(), houses.end());
    auto cur = houses.begin();
    int ans = 0;
    while(cur != houses.end()){
        ans++;
        auto it = upper_bound(houses.begin(), houses.end(), *cur + k); // this it is one past the house where the 
        // transmitter should be installed
        it = upper_bound(houses.begin(), houses.end(), *(--it) + k);
        cur = it;
    }
    
    cout << ans << endl;
    return 0;
}