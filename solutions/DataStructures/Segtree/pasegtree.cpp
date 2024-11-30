#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)

const int N = 200100;
const ll emp = 0; //NULL VALUE

ll a[N],tree[N << 2];
pair<ll,ll> lazy[N << 2];

ll f(ll a, ll b){return a+b;}//function

pair<ll,ll> ff(pair<ll,ll> a, pair<ll,ll> b){return pair<ll,ll>{a.first+b.first,a.second+b.second};}//function

//node p is always ok

// PA FORMULAS
// an = a1 + r * (n-1)
// sn = (a1 + an) * (n) / 2
void push(int p, int tl, int tr)
{
    if(tl == tr || lazy[p] == pair<ll,ll>{emp,emp})
        return;
    int tmid = (tl+tr) >> 1;

    //solve propagations
    ll at = lazy[p].first + lazy[p].second * (tmid-tl);
    ll sum = (at + lazy[p].first) * (tmid-tl+1) >> 1;
    tree[lef(p)] = f(tree[lef(p)], sum);

    at += lazy[p].second;
    ll at2 = lazy[p].first + lazy[p].second * (tr - tl);
    sum = (at + at2) * (tr-tmid) >> 1;
    tree[rig(p)] = f(tree[rig(p)], sum);
    
    //update lazy
    lazy[lef(p)] = ff(lazy[lef(p)], lazy[p]);
    lazy[rig(p)] = ff(lazy[rig(p)], pair<ll,ll>{at,lazy[p].second});
    
    //clean lazy
    lazy[p] = {emp,emp};
}

void build(int p, int tl, int tr)
{
    if(tl == tr)
    {
        tree[p] = a[tl];
		return;
    }
	int tmid = (tl + tr) >> 1;
	build(lef(p), tl, tmid);
	build(rig(p), tmid+1, tr);
	tree[p] = f(tree[lef(p)], tree[rig(p)]);
    
}

void updt(int p, int tl, int tr, int l, int r, ll v)
{
    if(l > r)
        return ;
    if(tl == l && tr == r){
        ll at = tl-v+1;
        ll at2 = tr -v+1;
        ll sum = (at + at2) * (tr-tl+1) >> 1;
        tree[p] = f(tree[p], sum);

        lazy[p] = ff(lazy[p], {tl-v+1,1});
        return;
    }
    //push if go down
    push(p,tl,tr);

    int tmid = (tl+tr) >> 1;
    updt(lef(p), tl, tmid, l, min(r,tmid), v);
    updt(rig(p), tmid+1, tr, max(l,tmid+1), r, v);
    tree[p] = f(tree[lef(p)], tree[rig(p)]);
    
}



ll query(int p, int tl, int tr, int l, int r)
{
    if(l > r)
        return emp;
    if(tl == l && tr == r)
        return tree[p];
    //push if go down
    push(p,tl,tr);
    int tmid = (tl+tr) >> 1;
    return f(query(lef(p), tl, tmid, l, min(r,tmid)),
        query(rig(p), tmid+1, tr, max(l,tmid+1), r));
}
