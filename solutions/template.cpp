#include<bits/stdc++.h>
using namespace std;

//template
#pragma region 

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
template<class T> using ordset = tree<T,null_type, less<T>,
rb_tree_tag, tree_order_statistics_node_update>;

// #pragma GCC optimize("Ofast") // for fast N^2
// #pragma GCC target("avx2") // for fast N^2
// #pragma GCC target("popcnt") // for fast popcount

#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)

using ll = long long int;
using ld = long double;
using pll = pair<ll,ll>;
using pii = pair<int,int>;
using pdb = pair<ld,ld>;
 
//read and print pair
template<typename T, typename T1>
ostream & operator<<(ostream &os, pair<T, T1> p){
    os << "(" << p.ft << "," << p.sd << ")";
    return os;
}
template<typename T, typename T1>
istream & operator>>(istream &is, pair<T, T1>& p){
    is >> p.ft >> p.sd;
    return is;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#pragma endregion

void test() {

}   
 
int32_t main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int ttt_ = 1;
    // cin >> ttt_;
    while(ttt_--) test();
    return 0;
}

