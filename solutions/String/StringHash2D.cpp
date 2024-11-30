    //UVALive-6893
#include <bits/stdc++.h>
using namespace std;

const int N=2010;
typedef long long ll;

int n[2],m[2];
string s[2][N];
struct Hash {
    uint64_t p, mod, ppow[N], ppow2[N], p2;
    uint64_t h[N][N];

    Hash() : p(33), mod(1000000007), p2(73) {
        ppow[0] = 1;
        ppow2[0] = 1;
        for (int i = 1; i < N; i++) {
            ppow[i] = (ppow[i-1] * p) % mod;
            ppow2[i] = (ppow2[i-1] * p2) % mod;
        }
    }

    void init(int at) {
        h[0][0]=0;
        for (size_t i = 1; i <= n[at]; i++) {
            h[i][0]=0;
            for (int j = 1; j <= m[at] ; ++j)
            {
                h[0][j]=0;
                int code=1;
                if(s[at][i-1][j-1]=='x'){
                    // cout<<i<<" "<<j<<"\n";
                    code=2;
                }
                h[i][j]=((code*ppow[i])%mod*ppow2[j])%mod;
            }
        }
        for (size_t i = 1; i <= n[at]; i++) {
            for (int j = 1; j <= m[at]  ; ++j)
            {
                h[i][j]=(h[i][j]+h[i-1][j])%mod;
            }
        }
        for (size_t i = 1; i <= n[at]; i++) {
            for (int j = 1; j <= m[at]  ; ++j)
            {
                h[i][j]=(h[i][j]+h[i][j-1])%mod;
            }
        }
    }

    uint64_t get_hash(int i, int j,int hh,int w) {
        uint64_t r;
        // cout<<h[hh][w]<<"\n";
        r = ((h[hh][w]+ mod + mod - h[hh][j-1] - h[i-1][w] + h[i-1][j-1])%mod)%mod;
        return r;
    }
};

template<typename T>
ostream& operator<<(ostream& os, pair<T, T> p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

Hash h1, h2;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    while(cin>>n[0]>>m[0]>>n[1]>>m[1])
    {
        for (int i = 0; i < n[0]; ++i)
        {
            cin>>s[0][i];
        }
        for (int i = 0; i < n[1]; ++i)
        {
            cin>>s[1][i];
        }
        h1.init(0);
        h2.init(1);
        int rs=0;
        uint64_t at=h1.get_hash(1,1,n[0],m[0]);
        for (int i = 1; i <= n[1]-n[0]+1; ++i)
        {
            for (int j = 1; j <= m[1]-m[0]+1; ++j)
            {
                uint64_t at2=h2.get_hash(i,j,i+n[0]-1,j+m[0]-1);
                // if(i==2 && j==1)
                // {
                //     cout<<at2<<" "<<((((h1.ppow[i-1]*h1.ppow2[j-1])%h1.mod)*at)%h1.mod)<<"\n";
                // }
                if(at2==
                    ((((h1.ppow[i-1]*h1.ppow2[j-1])%h1.mod)*at)%h1.mod)){
                    rs++;
                    // cout<<i<<" "<<j<<"\n";
                }
            }
        }
        cout<<rs<<"\n";
    }
    return 0;
}  