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
int cont[N], vis[N];
void push(int x)
{
    if(vis[x] != cs)
    {
        vis[x] = cs;
        cont[x] = 0;
    }
}
int calc(int u, int p,int dep)
{
    ll rs = 0;
    if(dep <= k){
        push(k-dep);
        rs = cont[k-dep];
    }else
        return 0;
    for(int v:adj[u])
    {
        if(v == p || did[v])
            continue;
        rs += calc(v, u, dep+1);
    }
    return rs;
}
void put(int u, int p,int dep)
{
    push(dep);
    cont[dep]++;
    if(dep > k)
        return;
    for(int v:adj[u])
    {
        if(v == p || did[v])
            continue;
        put(v, u, dep+1);
    }
}
ll decomp(int u)
{
    // cout << u << " <<< \n";
    dfs(u, u);
 
    // cout << u << " <<< \n";
    u = centroid(u, u, sz[u]);
    cs++;
    ll rs = 0;
    for(int v:adj[u])
    {
        if(did[v])
            continue;
        rs += calc(v, u, 1);
        put(v, u, 1);
    }
    push(k);
    rs += cont[k];
    if(rs == 0)
        return 0;
    // cout << u << ' ' << rs << '\n';
    did[u] = 1;
    for(int v:adj[u])
    {
        if(did[v])
            continue;
        rs += decomp(v);
    }
    return rs;
}
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n >> k;
 
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cout << decomp(1) << '\n';
    return 0;
}