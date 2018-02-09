#include <bits/stdc++.h>

using namespace std;

vector<vector<long> > memo;
vector <long> c;

long getWays(long m, long n){
    if(memo[m][n] != -1){
        return memo[m][n];
    }
    
    if(n == 0){
        return 1; // can always make 0 sum with empty subset
    }
    
    if(m == 0) {
        return (n%c[m]) == 0; // check if n can be formed with multiple c0 coins
    }
    
    long ways1 = getWays(m-1, n); // do not take mth coin
    
    long ways2 = 0;
    if(n-c[m] >= 0){
        ways2 = getWays(m, n-c[m]); // take 1 mth coin
    }
    
    long ways = ways1 + ways2;        
    memo[m][n] = ways;
    return ways;
}


int main() {
    int n;
    int m;
    cin >> n >> m;
    c = vector<long>(m);
    for(int c_i = 0; c_i < m; c_i++){
       cin >> c[c_i];
    }
    
    memo = vector<vector<long> >(m, vector<long>(n+1, -1)); // num of ways to make sum n, using coins c0, c1, ..., cm.
    
    // Print the number of ways of making change for 'n' units using coins having the values given by 'c'
    cout << getWays(m-1, n) << endl;
    return 0;
}
