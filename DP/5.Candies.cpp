#include <bits/stdc++.h>
#include <numeric>

using namespace std;
typedef long long int lli;

vector<lli> num_candies; // number of candies that each child gets

lli candies(int n, vector <int>& arr) {
    for(int i=1; i<n; i++){ // forward pass
        if(arr[i] > arr[i-1]){
            num_candies[i] = num_candies[i-1] + 1;
        }
    }
    
    for(int i=n-2; i>=0; i--){
        if(arr[i] > arr[i+1] && num_candies[i] <= num_candies[i+1]){ // i should get more than i+1
            num_candies[i] = num_candies[i+1]+1;
        }
    }
    
    return accumulate( num_candies.begin(), num_candies.end(), (lli)0);
}


// not DP!! Greedy
int main() {
    int n;
    cin >> n;
    vector<int> arr(n+1);
    for(int arr_i = 0; arr_i < n; arr_i++){
       cin >> arr[arr_i];
    }
    
    num_candies = vector<lli>(n, 1);// initially 1 candy given to each child
    
    lli result = candies(n, arr);
    cout << result << endl;
    return 0;
}
