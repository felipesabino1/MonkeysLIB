const int N = 2010;
const uint64_t p[4] = {33, 73, 37, 93}, mod[2] = {1000000007, 1000000009};
uint64_t ppow[4][N];

void build()
{
    for (int j = 0; j < 4; j++){
        ppow[j][0] = 1;        
        for (int i = 1; i < N; i++) {
            ppow[j][i] = (ppow[j][i-1] * p[j]) % mod[j>>1];
        }
    }
}

//needed for get_hash_equal
uint64_t fastExp(uint64_t a, uint64_t p, uint64_t mod) {
    return p == 0 ? 1 : ((fastExp((a * a) % mod, p / 2, mod) % mod) * (p & 1 ? a%mod : 1)) % mod;
}
unordered_map<uint64_t, uint64_t> memo[2];
uint64_t getInv(uint64_t a, uint64_t m){
    int at = (m - mod[0])>>1;
    if (memo[at].count(a)) return memo[at][a];
    return memo[at][a] = fastExp(a, m-2, m);
}

struct Hash {
    int n, m;
    vector<vector<pair<uint64_t, uint64_t>>>h;
 
    Hash () {}
 
    void init(vector<string> &word2d) {
        n = word2d.size();
        m = word2d[0].size();
        h.resize(n+1, vector(m+1, mp((uint64_t)0,(uint64_t)0)));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++){
                int code = word2d[i-1][j-1];
                h[i][j] = {((code * ppow[0][i])%mod[0] * ppow[1][j])%mod[0],
                           ((code * ppow[2][i])%mod[1] * ppow[3][j])%mod[1]};

            }
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 1; j <= m; j++)
            {
                h[i][j] = {(h[i][j].ft + h[i][j-1].ft)%mod[0],
                           (h[i][j].sd + h[i][j-1].sd)%mod[1]};
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++)
            {
                h[i][j] = {(h[i][j].ft + h[i-1][j].ft)%mod[0],
                           (h[i][j].sd + h[i-1][j].sd)%mod[1]};
            }
        }
    }
    
    pair<uint64_t, uint64_t> get_hash(int i, int j, int height, int width) {
        int i2 = i + height - 1, j2 = j + width - 1;
        pair<uint64_t, uint64_t> r = {
            (h[i2][j2].ft + mod[0] + mod[0] - h[i2][j-1].ft - h[i-1][j2].ft + h[i-1][j-1].ft)%mod[0],
            (h[i2][j2].sd + mod[1] + mod[1] - h[i2][j-1].sd - h[i-1][j2].sd + h[i-1][j-1].sd)%mod[1]
        };
        return r;
    }

    pair<uint64_t, uint64_t> get_hash_equal(int i, int j, int height, int width) {
        pair<uint64_t, uint64_t> r = get_hash(i, j, height, width);
        r = {
            (r.ft * getInv((ppow[0][i-1] * ppow[1][j-1])%mod[0], mod[0]))%mod[0],
            (r.sd * getInv((ppow[2][i-1] * ppow[3][j-1])%mod[1], mod[1]))%mod[1]
        };
        return r;
    }
    
};

Hash h1, h2;
vector<string> ss1, ss2;

int sv[N][N];
void test()
{
    int n,m,n2,m2;
    string s;
    cin >> n >> m;
    rep(i, 0, n){
        cin >> s;
        ss1.pb(s);
    }
    cin >> n2 >> m2;
    rep(i, 0, n2){
        cin >> s;
        ss2.pb(s);
    }
    build();
    h1.init(ss1);
    h2.init(ss2);

    auto target = h1.get_hash_equal(1, 1, n, m);
    for(int i = 0; i < n2 - n + 1; i++){
        for(int j = 0; j < m2 - m + 1; j++){
            if (target == h2.get_hash_equal(i+1, j+1, n, m)){
                sv[i][j]++;
                sv[i][j+m]--;
                sv[i+n][j]--;
                sv[i+n][j+m]++;
            }
        }
    }
 
    rep(i, 0, n2){
        rep(j, 1, m2){
            sv[i][j] += sv[i][j-1];
        }
    }
    rep(j, 0, m2){
        rep(i, 1, n2){
            sv[i][j] += sv[i-1][j];
        }
    }
 
    rep(i, 0, n2){
        rep(j, 0, m2){
            if (sv[i][j] > 0){
                cout << ss2[i][j];
            }
            else{
                cout << ".";
            }
        }
        cout << "\n";
    }
}   
