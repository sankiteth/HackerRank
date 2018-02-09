#include <bits/stdc++.h>
#include <cmath>

using namespace std;

int cost(vector <int> arr, int N) {
    int ret = 0;
    // dp[i][0] = max S such that we chose A[i] = 1 as per definition, the minimum possible value for A[i]
    // dp[i][i] = max S such that we chose A[i] = B[i], the maximum possible value for A[i]
    vector<vector<int> > dp(N+1, vector<int>(2, 0));
    dp[1][0] = arr[0]-1; // base cases
    dp[1][1] = arr[1]-1;
    
    for(int i=2; i<N; i++){
        dp[i][0] = max(dp[i-1][0], dp[i-1][1] + (arr[i-1]-1) );
        dp[i][1] = max(dp[i-1][0] + (arr[i]-1), dp[i-1][1] + abs(arr[i]-arr[i-1]) );
    }
    
    return max(dp[N-1][0], dp[N-1][1]);
}

int main() {
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;
        vector<int> arr(n);
        for(int arr_i = 0; arr_i < n; arr_i++){
           cin >> arr[arr_i];
        }

        int result = cost(arr, n);
        cout << result << endl;
    }
    return 0;
}
