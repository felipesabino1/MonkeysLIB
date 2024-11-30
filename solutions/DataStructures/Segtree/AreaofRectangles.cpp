const int N = 1000001;
 
vector<pii> event[2*N + 100][2]; 
 
pii stree[8*N+ 100];
int lazy[8*N+ 100];
 
pii merge(pii a, pii b)
{
    if(a.ft == b.ft)
        a.sd+=b.sd;
    if(a.ft <= b.ft)
        return a;
    return b;
}
 
void push(int p, int tl, int tr)
{
    if(tl != tr && lazy[p] != 0)
    {
        stree[lef(p)].ft += lazy[p];
        stree[rig(p)].ft += lazy[p];
        lazy[lef(p)] += lazy[p];
        lazy[rig(p)] += lazy[p];
    }
    lazy[p] = 0;
}
 
void build(int p, int tl, int tr)
{
    if(tl == tr)
    {
        stree[p] = {0,1};
        return;
    }
    int tmid = (tl+tr) >> 1;
    build(lef(p), tl, tmid);
    build(rig(p), tmid+1, tr);
    stree[p] = merge(stree[lef(p)],stree[rig(p)]);
}
 
 
void updt(int p, int tl, int tr,int l, int r, int x)
{
    if(l > r)
        return;
    if(tl == l && tr == r)
    {
        stree[p].ft+=x;
        lazy[p]+=x;
        return;
    }
    int tmid = (tl+tr) >> 1;
    push(p, tl, tr);
    updt(lef(p), tl, tmid, l, min(r,tmid), x);
    updt(rig(p), tmid+1, tr, max(l, tmid+1), r, x);
    stree[p] = merge(stree[lef(p)],stree[rig(p)]);
}
 
 
void test()
{
    int n;
    cin >> n;
    pii pt;
    rep(i, 1, n+1)
    {
        // cout << i << endl;
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        pii at = pii{y1+N,y2+N-1};
        // cout << x1+N << ' ' << x2+N << endl;    
        event[x1+N][0].pb(at);
        event[x2+N][1].pb(at);
    }
    build(1,1,2*N);
    ll rs = 0;
    rep(i, 0, 2*N)
    {
        for(auto [l,r]:event[i][0])
        {
            // cout << l << ' ' << r << '\n';
            updt(1, 1, 2*N, l, r, 1);
        }
        for(auto [l,r]:event[i][1])
        {
            // cout << l << ' ' << r << '\n';
            updt(1, 1, 2*N, l, r, -1);
        }
        // if(stree[1].sd != 2*N)
        //     cout << i << ' ' << stree[1] << '\n';
        if(stree[1].ft != 0)
            rs += 2*N;
        else
            rs += 2*N-stree[1].sd;
    }
    cout << rs << '\n';
}
 
 