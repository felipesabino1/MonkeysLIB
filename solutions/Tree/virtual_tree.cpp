#include<bits/stdc++.h>

using namespace std;

//template

const int N = 400100;
const int K = 20;
vector<int> adj[N];
int pai[N][K], in[N], out[N], cs = 0;

void pre_dfs(int u, int p)


// u is ancestor of v ?
bool is_ancestor(int u, int v)

int calc_lca(int a, int b)


int cor[N];
vector<int> c[N];
vector<int> nadj[N];

int lc[N];

ll dp[N][3];

ll calc(int u,int col, int p)
{
    dp[u][1] = (cor[u] == col);
    dp[u][2] = 0;
    for(int v:nadj[u])
    {
        if(v == p)
            continue;
        calc(v,col,u);
        dp[u][2] += dp[u][1]*dp[v][1];
        if(cor[u] != col){
            dp[u][1] += dp[v][1];
        }
        dp[u][2] += dp[v][2];
    }
    // cout << u << ' ' << dp[u][2] << '\n'; 
    return dp[u][2];
}


ll solve(vector<int> &at, int j)
{
    // solve for tree with one vertex
    if(at.size() <= 1)
        return 0;
    sort(all(at),[&](int a, int b){
            return in[a] < in[b];
        });
    int m = at.size();
    rep(i, 0, m)
        lc[i] = at[i];
    rep(i, 0, m-1){
        lc[i+m] = calc_lca(at[i],at[i+1]);
    }
    sort(lc,lc+m+m-1,[&](int a, int b){
            return in[a] < in[b];
        });
    m = unique(lc,lc+m+m-1)-lc;
    rep(i, 0, m)
        nadj[lc[i]].clear();
    
    vector<int> st;
    st.pb(lc[0]);
    rep(i, 1, m)
    {
        while(!is_ancestor(st.back(),lc[i]))
            st.pop_back();
        nadj[st.back()].pb(lc[i]);
        nadj[lc[i]].pb(st.back());
        st.pb(lc[i]);
    }
    // solve for virtual tree
    return calc(lc[0],j,lc[0]);
}

void test()
{
    int n;
    cin >> n;

    rep(i, 1, n+1){
        adj[i].clear();
        c[i].clear();
    }
    cs = 0;
    rep(i, 1, n+1)
    {
        cin >> cor[i];
        c[cor[i]].pb(i);
    }
    rep(i, 0, n-1)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }   
    pre_dfs(1,1);
    ll rs = 0;
    rep(i, 1, n+1)
    {
        rs += solve(c[i],i);
    } 
    cout << rs << '\n';
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    cin >> t;
    while(t--){
        test();
    }
    return 0;
}