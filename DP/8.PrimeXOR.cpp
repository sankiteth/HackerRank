#include<bits/stdc++.h>
#define LL long long
#define M 1000000007
using namespace std;

int q, n, f[8200] = {0}; // a[i] <= 4500. 4500 has 13 bits, hence highest value of XOR that 
                         // can be achieved = 2^13 - 1 = 8191
LL dp[1005][8200] = {0}, cnt[1005] = {0}; // 3500 <= a[i] <= 4500. Hence, at max, there are 1001 unique values 
                                          // in the array
vector<int> P;

void makePrime(){
    f[0] = f[1] = 1;
    for(int i=2; i*i < 8200; i++){
        if(!f[i]){
            for(int j=i+i; j< 8200; j+=i)// mark all multiples of i as not prime
                f[j] = 1;
        }
    }
    for(int i=2; i<8200; i++) if(!f[i]) P.push_back(i);
}

int main() {
    cin >> q;
    makePrime();

    while(q--){
        cin >> n;
        memset(cnt, 0, sizeof(cnt));
        memset(dp,0,sizeof(dp));
        
        for(int i=0,x; i<n; i++){
            cin >> x;
            cnt[x-3500]++; // number of times x appears in the array
        }
        
        // the elements in the array are considered in sorted order.
        //dp[i][j] = count of subsets that can be formed with the first "i" elements s.t. the XOR-sum of the 
        // elements in the subset is "j"
        
        dp[0][3500] = (cnt[0] + 1)/2; // the 0th element(which is 3500), when considered in odd multiples produce back
                                      // 3500 as resultant XOR-sum value
        dp[0][0] = (cnt[0] + 2) / 2;  // the 0th element(which is 3500), when considered in even multiples produce
                                      // 0 as resultant XOR-sum value
        for(int i=1; i<1005; i++){
            for(int j=0; j<8200; j++){ // dp[i][j] depends on previous row (i-1), which has already been calculated!
                dp[i][j] = (
                                dp[i-1][j]*((cnt[i]+2)/2) + // adding "i"th element in even multiple times to already
                    // formed multisets using previous (i-1) elements produces the same XOR-sum value
                                dp[i-1][j^(i+3500)]*((cnt[i]+1)/2) //adding "i"th element in odd multiple times to
                    // already formed multisets using previous (i-1) elements produces XOR-sum value (j XOR (i+3500)).
                    // (i+3500) is the "i"th unique value in the input array, after sorting it.
                            ) % M ;
            }
        }
        LL ans = 0;
        for(int p : P){
            (ans += dp[1004][p]) %= M;
        }
        cout << ans%M << endl;
    }
    return 0;
}