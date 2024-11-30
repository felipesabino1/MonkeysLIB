#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N = 200100;
// KEEP
vector<int> adj[N];
int sz[N], did[N];
void dfs(int u,int p )
{
    sz[u] = 1;
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
// SOLVE PROBLEM
int k, cs = 1;
ll mp[N], vis[N];
void push(int x)
{
    if(vis[x] != cs)
    {
        vis[x] = cs;
        mp[x] = 0;
    }
}
ll calc(int u, int p,int dep)
{
    ll rs = 0;
    if(dep <= k){
        push(k-dep);
        rs = mp[k-dep];
    }
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
    mp[dep]++;
    for(int v:adj[u])
    {
        if(v == p || did[v])
            continue;
        put(v, u, dep+1);
    }
}

//DECOMPOSITION
ll decompose(int u)
{
    dfs(u, u);
    u = centroid(u, u, sz[u]);

	//SOLVE PROBLEM
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
    rs += mp[k];

	//PROPAGATE DECOMPOSITION
    did[u] = 1;

    for(int v:adj[u])
    {
        if(did[v])
            continue;
        rs += decompose(v);
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
    cout << decompose(1) << '\n';
    return 0;
}
