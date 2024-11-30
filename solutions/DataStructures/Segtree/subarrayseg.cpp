const int N = 200100;
const ll emp = -2000000000000000LL; //NULL VALUE

struct dt
{
    ll l, r, mx, tot;
    dt(){};
    dt(ll a):l(a), r(a), mx(max(a,0LL)), tot(a){};
};
ll a[N];
dt tree[N << 2];

dt f(dt a, dt b){
    dt x;
    x.mx = max(a.mx, b.mx);
    x.mx = max(x.mx, a.r + b.l);
    x.r = max(a.r + b.tot, b.r);
    x.l = max(b.l + a.tot, a.l);
    x.tot = a.tot + b.tot;
    return x;
}//function


void build(int p, int tl, int tr)
{
    if(tl == tr)
    {
        tree[p] = dt(a[tl]);
		return;
    }
	int tmid = (tl + tr) >> 1;
	build(lef(p), tl, tmid);
	build(rig(p), tmid+1, tr);
	tree[p] = f(tree[lef(p)], tree[rig(p)]); 
    
}


void updt_point(int p, int tl, int tr, int k, ll v)
{
    if(tl == tr){
        tree[p] = dt(v);
        return;
    }

    int tmid = (tl+tr) >> 1;
    if (tmid < k)
        updt_point(rig(p), tmid+1, tr, k, v);
    else
        updt_point(lef(p), tl, tmid, k, v);
    tree[p] = f(tree[lef(p)], tree[rig(p)]);
    // cout << tl << " " << tr << ' '<< tree[p].mx << '\n';
}