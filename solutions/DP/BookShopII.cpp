#include<bits/stdc++.h>
using namespace std;

//template
 
const int N = 100010;
 
vector<pii> obj;
int dp[N], vh[N], vs[N], vk[N];
void test()
{
    int n, x;
    cin >> n >> x;
 
    rep(i, 0, n)
        cin >> vh[i];
    rep(i, 0, n)
        cin >> vs[i];
    rep(i, 0, n)
        cin >> vk[i];
    rep(i, 0, n)
    {
        int h = vh[i], s = vs[i], k = vk[i];
        int sum = 1, pg = s, cost = h;
        while(sum <= k)
        {
            k-=sum;
            obj.eb(pg,cost);
            pg+=pg;
            cost+=cost;
            sum+=sum;
        }
        if(k != 0)
        {
            obj.eb(s*k,h*k);
        }
    }
    int mx = 0;
    dp[0] = 0;
    for(auto [p,c]:obj)
    {
        // cout << p << ' ' << c << '\n';
        rep(i, mx+1, 0)
        {
            if(i+c <= x)
                dp[i+c] = max(dp[i]+p,dp[i+c]);
        }
        mx+=c;
        mx = min(mx, x);
    }
    int rs = 0;
    rep(i, 0, x+1)
        rs = max(rs, dp[i]);
    cout << rs << '\n';
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