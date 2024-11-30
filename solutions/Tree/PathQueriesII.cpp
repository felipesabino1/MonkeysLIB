#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
const int N = 200100;
 
class Segtree {
    public:
    const ll emp = 0; //NULL VALUE
    vector<ll> tree;
    Segtree(){}
    ll f(ll a, ll b){return max(a,b);}//function
    
    void updt(int p, int tl, int tr, int k, ll v)
    {
        if(tl == tr){
            tree[p] = v;
            return;
        }
        int tmid = (tl+tr) >> 1;
        if (tmid < k)
            updt(rig(p), tmid+1, tr, k, v);
        else
            updt(lef(p), tl, tmid, k, v);
        tree[p] = f(tree[lef(p)], tree[rig(p)]);
        
    }
    
    ll query(int p, int tl, int tr, int l, int r)
    {
        if(l > r)
            return emp;
        if(tl == l && tr == r)
            return tree[p];
        int tmid = (tl+tr) >> 1;
        return f(query(lef(p), tl, tmid, l, min(r,tmid)),
            query(rig(p), tmid+1, tr, max(l,tmid+1), r));
    }
 
};
Segtree tree[N];
 
vector<int> adj[N];
int depth[N], hd[N], sz[N], pai[N], sub_sz[N], pos[N];
ll a[N];
 
void dfs(int u,int p = -1)
{
    pai[u] = p;
    sub_sz[u] = 1;
    if(p!=-1)
        depth[u] = depth[p] + 1;
 
    for(int v: adj[u])
    {
        if(v != p){
            dfs(v, u);
            sub_sz[u] += sub_sz[v];
        }
    }
}
void dfs2(int u,int p = 1)
{
    for(int v: adj[u])
    {
        if(v == p)
            continue;
        if(sub_sz[u] <= 2*sub_sz[v]){
            hd[v] = hd[u];
            pos[v] = ++sz[hd[u]];
            dfs2(v, u);
        }else
        {
            hd[v] = v;
            sz[v] = 1;
            pos[v] = 1;
            dfs2(v, u);
        }
    }
    if(u == hd[u])
        tree[u].tree.resize(sz[u] << 2,0);
}
void build_hld(int n)
{
    dfs(1);
    hd[1] = sz[1] = pos[1] =  1;
    dfs2(1);
    for(int i = 1; i <= n; i++)
    {
        tree[hd[i]].updt(1,1,sz[hd[i]],pos[i],a[i]);
    }
}
ll query(int a,int b)
{
    ll ans = 0;
    while(hd[a] != hd[b])
    {
        // cout << a << ' '<< b << '\n';
        if(depth[hd[a]] > depth[hd[b]])
            swap(a,b);
        ans = max(ans, tree[hd[b]].query(1,1,sz[hd[b]],pos[hd[b]],pos[b]));
        b = pai[hd[b]];
    }
    if(pos[a] > pos[b])
        swap(a,b);
    ans = max(ans, tree[hd[b]].query(1,1,sz[hd[b]],pos[a],pos[b]));
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
 
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    build_hld(n);
    while(q-- )
    {
        int t;
        cin >> t;
        if(t == 2)
        {
            int u, v;
            cin >> u >> v;
            cout << query(u, v) << "\n";
        }else
        {
            int u;
            ll x;
            cin >> u >> x;
            tree[hd[u]].updt(1,1,sz[hd[u]],pos[u],x);
            a[u] = x;
        }
    }
    return 0;
}