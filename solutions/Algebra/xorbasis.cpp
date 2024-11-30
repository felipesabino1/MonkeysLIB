struct Basis {
  vector<ll> B;
  ll reduce(ll x) {
    for (auto b : B) x = min(x, x^b);
    return x;
  }
  void insert(ll x) {
    ll r = reduce(x);
    if (r) B.push_back(r);
  }
};
 