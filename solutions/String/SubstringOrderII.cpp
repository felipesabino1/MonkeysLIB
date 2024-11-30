ll dp[N]; 
string bfs(ll k)
{
    vector<pair<int,int>> ids;
    for(int pos = 1; pos < sz; pos++)
        ids.push_back({st[pos].len,pos});
    sort(ids.begin(), ids.end());
    reverse(ids.begin(), ids.end());
    for(auto [l,x]:ids){
        dp[x] = st[x].qt;
        // cout << x << ' ' << st[x].qt << '\n';
        for(auto [c,y]:st[x].next)
        {
            dp[x] += dp[y];
        }
        if(st[x].link != -1){
            // cout << x << " " << st[x].link << " << link\n";
            st[st[x].link].qt += st[x].qt;
        }
    }
    reverse(ids.begin(), ids.end());
    int pos = 0;
    string resp;
    while(k>0){
        for(auto [c,y]:st[pos].next)
        {
            if(dp[y] < k){
                // cout << c << ' ' << dp[y] << ' ' << y <<"\n"; 
                k-= dp[y];
            }
            else{
                k-=st[y].qt;
                // cout << c << ' ' << dp[y] << " " << y <<" <<go\n";
                resp.push_back(c);
                pos = y;    
                break;
            }
        }
    }
    return resp;
}