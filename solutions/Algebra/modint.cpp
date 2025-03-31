const int MOD = 1'000'000'007;

struct mi {
    int v;  
    explicit operator int() const { return v; }
    mi() { v = 0; }
    mi(long long int _v) : v(_v % MOD + (_v % MOD < 0) * MOD) {}
    
    friend mi operator -(const mi & at){
        return mi(-at.v);
    }

    void operator +=(const mi & ot){
        v += ot.v;
        v -= (v >= MOD) * MOD;
    }
    void operator -=(const mi & ot) {
        v -= ot.v;
        v += (v < 0) * MOD;
    }
    void operator *=(const mi & ot){
        v = 1ll * v * ot.v % MOD;
    }
    void operator /=(const mi & ot){
        v = 1ll * v * inv(ot).v % MOD;
    }
    friend mi operator +(const mi & a, const mi & b){
        return mi(a.v + b.v);
    }
    friend mi operator -(const mi & a, const mi & b){
        return mi(a.v - b.v);
    }
    friend mi operator *(const mi & a, const mi & b){
        return mi(1ll * a.v * b.v);
    }
    friend mi operator /(const mi & a, const mi & b){
        return mi(1ll * a.v * inv(b).v);
    }

    friend mi fexp(mi a, long long int b){
        mi ans(1);
        while(b){
            if(b&1) ans = ans*a;
            a *= a;
            b >>= 1;
        }
        return ans;
    }
    friend mi inv(const mi & a){
        assert(a.v != 0);
        return fexp(a, MOD - 2);
    }

    friend ostream& operator <<(ostream & out, const mi & at){
        return out << at.v;
    }
    friend istream& operator >>(istream & in, mi & at){
        return in >> at.v;
    }
};