const int N = 200100;
const ll emp = 0; //NULL VALUE

ll a[N],tree[N << 2], lazy[N << 2];

ll f(ll a, ll b){return a+b;}//function

//node p is always ok
void push(int p, int tl, int tr)
{
    if(tl == tr || lazy[p] == emp)
        return;
    int tmid = (tl+tr) >> 1;

    //solve propagations
    tree[lef(p)] = f(tree[lef(p)], (ll)(tmid-tl+1) * lazy[p]);
    tree[rig(p)] = f(tree[rig(p)], (ll)(tr-tmid) * lazy[p]);
    
    //update lazy
    lazy[lef(p)] = f(lazy[lef(p)], lazy[p]);
    lazy[rig(p)] = f(lazy[rig(p)], lazy[p]);
    
    //clean lazy
    lazy[p] = emp;
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
        tree[p] = f(tree[p], (ll)(tr-tl+1) * v);

        lazy[p] = f(lazy[p], v);
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
