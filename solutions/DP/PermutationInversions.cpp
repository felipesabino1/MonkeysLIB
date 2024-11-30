#include<bits/stdc++.h>
using namespace std;
 
//template
 
const int N = 510;
const ll mod = 1000000007LL;
 
ll dp[2][N*N];
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
 
    cin >> n >> k;
 
    dp[0][0] = 1;
    rep(j, 1, k + 1)
        dp[0][j] = 1;
 
    rep(i, 1, n+1)
    {
        rep(j, 0, k + 1)
        {
            int l = j-i;
            dp[1][j] = dp[0][j];
            if(l >= 0)
                dp[1][j] -= dp[0][l];
            if(dp[1][j] < 0)
                dp[1][j] += mod;
        }
        // error(i);
        // error(dp[1][k]);
        dp[0][0] = dp[1][0];
        rep(j, 1, k + 1){
            dp[0][j] = dp[1][j] + dp[0][j-1];
            // cout << dp[0][j] << '\n';
            if(dp[0][j] >= mod)
                dp[0][j] -= mod;
        }
    }
    cout << dp[1][k] << '\n';
    return 0;
}
// 3 2 1 -> 1