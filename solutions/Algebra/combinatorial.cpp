#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200100;
const ll mod = 1000000007LL;
ll fat[N], ifat[N], pot[N];
ll inv (ll x)
{
    ll b = mod - 2;
    ll rs = 1;
    while (b)
    {
        if(b&1)
            rs = x * rs % mod;
        x = x * x % mod;
        b >>= 1;
    }
    return rs; 
}
//take k eq objects between n
ll comb (ll n, ll k)
{
    if (n < k)
        return 0;
    ll ans = fat[n] * ifat[k] % mod;
    ans = ans * ifat[n-k] % mod;
    // cout << n << " " << k << " " << ans << '\n';
    return ans;
}
//put n eq objects in k boxes
ll sb (ll n, ll k)
{
    ll ans = fat[n + k - 1] * ifat[n] % mod;
    ans = ans * ifat[k - 1] % mod;
    // cout << n << " " << k << " " << ans << '\n';
    return ans;
}


    //Count how to label N + K pairs of parentheses with K left ones already fixed 
//(k=0 means normal catalan)
ll catalan(ll n, ll k)
{
    ll ans = (k+1) * comb(2*n + k, n) % mod;
    ans = ans * inv(n+k+1) % mod;
    // cout << n  << " " << k << " " << ans << '\n';
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    fat[0] = ifat[0] = pot[0] = 1;
    for (ll i = 1; i < N; i++)
    {
        fat[i] = fat[i-1] * i % mod;
        pot[i] = pot[i-1] * 2LL % mod;
    }
    ifat[N-1] = inv(fat[N-1]);
    for (ll i = N-2; i >= 0; i--)
        ifat[i] = ifat[i+1] * (i+1) %mod;
    return 0;
}
