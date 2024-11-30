int best = 0, dep[N], pai[N]; 
string bfs()
{
    vector<pair<int,int>> ids;
    for(int pos = 1; pos < sz; pos++)
        ids.push_back({st[pos].len,pos});
    sort(ids.begin(), ids.end());
    reverse(ids.begin(), ids.end());
    for(auto [l,x]:ids){
        if(st[x].link != -1){
            // cout << x << " " << st[x].link << " << link\n";
            st[st[x].link].qt += st[x].qt;
        }
    }
    reverse(ids.begin(), ids.end());
    int at = -1;
    for(auto [l,pos]:ids){
        if(st[pos].qt<2)
            continue;
        if(dep[pos] == 0){
            dep[pos] = 1;
        }
        if(dep[pos] > best){
            best = dep[pos];
            at = pos;
        }
        for(auto [x,y]:st[pos].next)
        {
            if(st[y].qt>1){
                if(dep[y] < dep[pos]+1)
                {
                    dep[y] = dep[pos]+1;
                    pai[y] = pos;
                }
                dep[y] = max(dep[y],dep[pos]+1);
            }
        }
    }
    if(at == -1)
        return "-1";
    string resp;
    while(at)
    {
        for(auto [x,y]:st[pai[at]].next)
        {
            if(y == at){
                resp.push_back(x);
            }
        }
        at = pai[at];
    }
    reverse(all(resp));
    return resp;
 
}