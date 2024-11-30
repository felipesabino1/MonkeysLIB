#include<bits/stdc++.h>
using namespace std;

//template

const int N = 100100;
 
vector<int> adj[N];
bitset<N> bt;
int vis[N], cont[N];
int dfs(int v)
{
    vis[v] = 1;
    int qt = 1;
    for(int u: adj[v])
    {
        if(vis[u])
            continue;
        qt+=dfs(u);
    }
    return qt;
}
vector<int> movs;
void test()
{
    int n, m;
    cin >> n >> m;
    while(m--)
    {
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    rep(i, 1, n+1)
        if(!vis[i])
            cont[dfs(i)]++;
 
    rep(i, 1, n+1)
    {
        int s = i, tot = cont[i]*i;
        while(tot > 0)
        {
            movs.pb(min(tot,s));
            tot-=s;
            s+=s;
        }
    }
    for(int x:movs)
    {
        bt |= bt<<x;
        bt[x] = 1;
    }
    rep(i, 1, n+1)
    {
        cout << bt[i];
    }
    cout << '\n';
 
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