#include<bits/stdc++.h>
using namespace std;
//template

const int MAXN = 2e5+100;
const int MAXMASK = (1<<20)+100;
const int MAXB = 21;
 
int X[MAXN];
 
int dp[MAXMASK][MAXB];
int custo[MAXMASK];
int resp[MAXN][3];
 
void sosdp(){
    rep(mask, 0, MAXMASK){
        dp[mask][MAXB-1] = custo[mask];
        for (int i = MAXB-2; i >= 0; i--){
        // rep (i, MAXB-1, 0){
            dp[mask][i] = dp[mask][i+1];
            if (mask&(1 << i)){
                dp[mask][i] += dp[mask - (1 << i)][i+1];
            }
        }
    }
}
 
void test()
{
    int n;
    cin >> n;
    rep(i, 0, n){
        cin >> X[i];
        custo[X[i]]++;
    }
    sosdp();
    rep(i, 0, n){
        resp[i][0] = dp[X[i]][0];
        int mask = X[i]^((1<<(MAXB-1))-1);
        resp[i][2] = dp[mask][0];
        custo[X[i]]--;
        custo[mask]++;
        // cout << mask << endl;
    }
    sosdp();
    rep(i, 0, n){
        int mask = X[i]^((1<<(MAXB-1))-1);
        resp[i][1] = dp[mask][0];
    }
    rep(i, 0, n){
        cout << resp[i][0] << " " << resp[i][1] << " " << n-resp[i][2] << "\n";
    }
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    // cin >> t;
    while(t--)
        test();
    return 0;
}