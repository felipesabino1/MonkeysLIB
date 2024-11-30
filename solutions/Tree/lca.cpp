e#include<bits/stdc++.h>
using namespace std;

const int N = 300100;
const int K = 20;
vector<int> adj[N];
int pai[N][K], in[N], out[N], cs = 0;

void pre_dfs(int u, int p)
{
    in[u] = cs++;
    pai[u][0] = p;
    for(int i = 1; i < K; i++){
        pai[u][i] = pai[pai[u][i-1]][i-1];
    }
    for(int v : adj[u])
        if(v != p)
            pre_dfs(v, u);
    out[u] = cs++;
}

// u is ancestor of v ?
bool is_ancestor(int u, int v)
{
    return in[u] <= in[v] && out[v] <= out[u];
}

int calc_lca(int a, int b)
{
    if(is_ancestor(a, b))
        return a;
    if(is_ancestor(b, a))
        return b;
    for(int i = K-1; i >=0; i--)
    {
        if(!is_ancestor(pai[b][i], a))
            b = pai[b][i];
    }
    return pai[b][0];
}



void test()
{
    int n, q;
    cin >> n;
    for(int i = 0, u, v; i < n-1; i++)
    {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    pre_dfs(1, 1);
    cin >> q;
    while(q--)
    {
        int a, b;
        cin >> a >> b;
        cout << calc_lca(a, b) << '\n';
    }
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    test();

    return 0;
}