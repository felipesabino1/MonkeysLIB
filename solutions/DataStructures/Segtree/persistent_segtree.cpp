#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

#define lef(x) (tree[x].l)
#define rig(x) (tree[x].r)

const int N = 200100;
const ll emp = 0; //NULL VALUE

struct node
{
    int l, r;
    ll v;
    node(): l(-1), r(-1), v(0){};
    node(int l, int r, ll v): l(l), r(r), v(v){};
};

ll a[N];
node tree[N << 6];
int last = 2;
int head[N];
ll f(ll a, ll b){return a+b;}//function

void build(int p, int tl, int tr)
{
    if(tl == tr)
    {
        tree[p].v = a[tl];
		return;
    }

	int tmid = (tl + tr) >> 1;
    tree[p].l = last++;
    tree[p].r = last++;
	build(lef(p), tl, tmid);
	build(rig(p), tmid+1, tr);
	tree[p].v = f(tree[lef(p)].v, tree[rig(p)].v);
    
}

void updt(int p,int np, int tl, int tr, int k, ll v)
{
    tree[np] = tree[p];
    if(tl == tr){
        tree[np].v = v;
        return;
    }
    int tmid = (tl+tr) >> 1;
    if (tmid < k){
        tree[np].r = last++;
        updt(rig(p), rig(np), tmid+1, tr, k, v);
    }
    else{
        tree[np].l = last++;
        updt(lef(p), lef(np), tl, tmid, k, v);
    }
    tree[np].v = f(tree[lef(np)].v, tree[rig(np)].v);
    
}

ll query(int p, int tl, int tr, int l, int r)
{
    if(l > r)
        return emp;
    if(tl == l && tr == r)
        return tree[p].v;
    int tmid = (tl+tr) >> 1;
    return f(query(lef(p), tl, tmid, l, min(r,tmid)),
        query(rig(p), tmid+1, tr, max(l,tmid+1), r));
}
int walk(int u,int v,int lc,int plc,int d,int tl,int tr){
	if(tl==tr)
		return tl;
	int at=0;
	int mid=(tl+tr)/2;
	at+=tree[lef(u)].v;
	at+=tree[lef(v)].v;
	at-=tree[lef(lc)].v;
	at-=tree[lef(plc)].v;
	// cout<<at<<" "<<tl<<" "<<tr<<"\n";
	if(at>=d)
		return walk(tree[u].l,tree[v].l,tree[lc].l,tree[plc].l,d,tl,mid);
	if(at<d)
		return walk(tree[u].r,tree[v].r,tree[lc].r,tree[plc].r,d-at,mid+1,tr);
}