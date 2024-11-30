#include<bits/stdc++.h>
using namespace std;

//template
#pragma region 

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;

// #pragma GCC optimize("Ofast") // for fast N^2
// #pragma GCC target("avx2") // for fast N^2
// #pragma GCC target("popcnt") // for fast popcount

#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
#define mt make_tuple
#define mp make_pair
#define eb emplace_back
#define pb push_back
#define HERE cout << "HERE" << endl;
// loop that goes (begin,..,end]
#define rep(i, begin, end) for (__typeof(begin) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
// #define rep(i, begin, end) for(int i = begin; i < end; i++)

typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
typedef pair<ld, ld> pdb;
 
template<class T> using ordset = tree<T,null_type, less<T>,
rb_tree_tag, tree_order_statistics_node_update>;

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
 
//error debug
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
 
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " = " << a << endl;
	err(++it, args...);
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#pragma endregion

void test() {

}   
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    // cin >> t;
    while(t--) test();
    
    return 0;
}

