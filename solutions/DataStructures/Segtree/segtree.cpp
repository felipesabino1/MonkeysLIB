const int N = 200100;
const ll emp = 0; //NULL VALUE

ll a[N],tree[N << 2];

ll f(ll a, ll b){return a+b;}//function

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
