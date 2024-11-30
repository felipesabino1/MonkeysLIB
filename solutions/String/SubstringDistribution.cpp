int getlen(int x)
{
    if(x<=0)
        return 0;
    return st[x].len;
}
int rs[N];
void bfs(int n)
{
    vector<pair<int,int>> ids;
    for(int pos = 0; pos < sz; pos++){
        rs[getlen(st[pos].link)+1]++;
        rs[getlen(pos)+1]--;
    }
    for(int i = 1; i <= n; i++){
        rs[i] += rs[i-1];
        cout << rs[i] << ' ';
    }
    cout << '\n';
}