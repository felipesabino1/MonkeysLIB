#include<bits/stdc++.h>
using namespace std; 
 
const int N = 400100;
vector<int> adj[N];
int sz[N], did[N];
int pass = 0;
void dfs(int u,int p )
{
    sz[u] = 1;
    // cout << pass++ << '\n';
    for(int v:adj[u])
    {
        if(v == p || did[v])
            continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}
 
int centroid(int u,int p, int sub_sz)
{
    for(int v:adj[u])
    {
        if(v == p || did[v])
            continue;
        if(2*sz[v] >= sub_sz)
            return centroid(v, u, sub_sz);
    }
    return u;
}
int k, cs = 1;
map<pair<int,int>, int> dist;
int best[N], pai[N];
void dfs_calc(int u,int p, int orig, int dep)
{
    dist[{orig, u}] = dep;
    for(int v:adj[u])
    {
        if(v == p || did[v])
            continue;
        dfs_calc(v, u, orig, dep+1);
    }
}
 
void decomp(int u, int p)
{
    dfs(u, u);
    int at = centroid(u, u, sz[u]);
    pai[at] = p;
    dfs_calc(at, at, at, 0);
    if(u == p)
        pai[at] = at;
    // cout << at << ' ' << pai[at] << "<<<\n";
    did[at] = 1;
    for(int v:adj[at])
    {
        if(did[v])
            continue;
        decomp(v, at);
    }
}

 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        best[i] = n+1;
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    decomp(1, 1);
    int u = 1;
    best[u] = 0;
    int x = u;
    while(pai[u] != u)
    {
        u = pai[u];
        best[u] = min(best[u], dist[{u, x}]);
    }
    while(m--)
    {
        int t, u;
        cin >> t >> u;
        // cout << t << ' ' << u << '\n';
        if(t == 2)
        {
            int rs = best[u];
            int x = u;
            while(pai[u] != u)
            {
                u = pai[u];
                rs = min(rs, best[u] + dist[{u,x}]);
            }
            cout << rs << '\n';
        }else
        {
            best[u] = 0;
            int x = u;
            while(pai[u] != u)
            {
                u = pai[u];
                best[u] = min(best[u], dist[{u, x}]);
            }
        }
    }
    return 0;
}