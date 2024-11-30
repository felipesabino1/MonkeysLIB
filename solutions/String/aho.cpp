const int K = 26;
struct node {
    int fim = 0,p,link = 0,elink = -1,len;
    int go[K] = {0},nxt[K] = {0};
    node(int p=0,int len = 0) : p(p),len(len) {};
};
vector<node> t(1);
void add_string(string const& s) {
    int v = 0;
    for (char ch : s) {
        ch-='a';
        if (!t[v].nxt[ch]) {
            t[v].nxt[ch] = t.size();
            t.eb(v,t[v].len+1);
        }
        v = t[v].nxt[ch];
    }
    // maybe change this to a vector with some ids
    t[v].fim = 1;
}

void calc_link()
{
    queue<int> q;
    q.push(0);
    while(!q.empty())
    {
        int v = q.front();
        q.pop();
        int lk = t[v].link;
        rep(i, 0, K)
        {
            if(!t[v].nxt[i])
                t[v].go[i] = t[lk].go[i];
            else{
                t[v].go[i] = t[v].nxt[i];
                t[t[v].go[i]].link = (!v?0:t[lk].go[i]);
                q.push(t[v].nxt[i]);
            }
        }
        //exit link is the first link with fim != 0
        if(t[lk].fim)
            t[v].elink = lk;
        else
            t[v].elink = t[lk].elink;
    }
}