#include<bits/stdc++.h>
using namespace std;

//template

//modint.cpp
 
const int N = 110;
const int M = 5010;
 
mi dp[N][N/2][M];
char vis[N][N/2][M];
int n;
int a[N];
//g = open groups
mi solve(int pos, int g,int sum)
{
    if(sum < 0)
        return 0;
    if(pos == n-1)
        return g <= 1;
    mi &ans = dp[pos][g][sum];
    if(vis[pos][g][sum])
        return ans;
    vis[pos][g][sum] = 1;
    // abrir um grupo
    if(2*g <= n)
    {
        ans += solve(pos+1,g+1,sum - (g+1)*(a[pos+1]-a[pos]));    
    }
    if(g != 0)
    {
        ans += g*solve(pos+1,g-1,sum - (g-1)*(a[pos+1]-a[pos]));    
    }
    ans += (g+1) * solve(pos+1,g,sum - (g)*(a[pos+1]-a[pos]));    
    return ans;
}
 
void test()
{
    int x;
    cin >> n >> x;
    rep(i, 0, n)
        cin >> a[i];
    sort(a,a+n);  
    cout << solve(0, 0, x).v << '\n';  
}
 
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    // cin >> t;
    while(t--)
        test();
    return 0;
}