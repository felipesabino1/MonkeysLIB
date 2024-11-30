#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = 998244353;
const int root = 565042129;//3^(mod/root_pw)
const int root_1 = 950391366;//inv(root)
const int root_pw = 1<<20;
const int N=100100;

int fat[N];
vector<int> a[N];
int exp(int n,int b)
{
	int rs=1;
	while(b)
	{
		if(b&1)
			rs=(int)(1LL*rs*n%mod);
		n=(int)(1LL*n*n%mod);
		b>>=1;
	}
	return rs;
}

void fft(vector<int> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);

        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i+j], v = (int)(1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)(1LL * w * wlen % mod);
            }
        }
    }

    if (invert) {
        int n_1 = exp(n, mod-2);
        for (int & x : a)
            x = (int)(1LL * x * n_1 % mod);
    }
}

void multiply(vector<int>  &a, vector<int>  &b) {
    // vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    if(b.size()<=30)
    {
    	vector<int> res(b.size()+a.size(),0);
    	for (int i = 0; i < a.size(); ++i)
    	{
    		for (int j = 0; j < b.size(); ++j)
    		{
    			res[i+j]+=(int)(1LL*a[i]*b[j]%mod);
    			if(res[i+j]>mod)
    				res[i+j]-=mod;
    		}
    	}
    	a=res;
    	return ;
    }
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    // cout<<n<<' '<<2*a.size()<<'\n';
    a.resize(n);
    b.resize(n);

    fft(a, 0);
    fft(b, 0);
    for (int i = 0; i < n; i++)
        a[i] = (int)(1LL*a[i]*b[i]%mod);
    fft(a, 1);
}



int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	// cout<<exp(3,952LL)<<" "<<exp(exp(3,952LL),mod-2)<<'\n';

	fat[0]=1;
	for (int i = 1; i < N; ++i)
	{
		fat[i]=(int)(1LL*fat[i-1]*i%mod);
	}
	// cout<<r[0]<<'\n';
	int q;
	cin>>q;
	while(q--)
	{
		int n;
		cin>>n;
		for (int i = 0; i < n; ++i)
		{
			a[i]=vector<int>(2);
			int x;
			cin>>x;
			a[i][0]=(1);
			a[i][1]=(x%mod);
		}
		// cout<<a[0].size()<<"\n";
		// for (int i = 0; i <a[0].size(); ++i)
		// {
		// 	cout<<i<<" "<<a[0][i]<<"\n";
		// }
		// for (int i = 1; i < n; ++i)
		// {
		// 	a[0]=multiply(a[0],a[i]);
		// 	cout<<a[0].size()<<"\n";
		// 	for (int i = 0; i <a[0].size(); ++i)
		// 	{
		// 		cout<<i<<" "<<a[0][i]<<"\n";
		// 	}
		// }
		for (int i = 1; i < n; i<<=1)
		{
			for (int j = 0; j+i < n ; j+=(i<<1))
			{
				// cout<<j<<" "<<j+i<<'\n';
				multiply(a[j],a[j+i]);
			}
		}
		int rs=0;
		for (int i = 1; i <= n; ++i)
		{
			// cout<<a[0][i]<<" "<<i<<"\n";
			rs += (int)(1LL*(1LL*a[0][i]*fat[i]%mod)*fat[n-i]%mod);
			if(rs>mod)
				rs-=mod;
		}
		rs = (int)(1LL*rs*exp(fat[n],mod-2)%mod);
		cout<<rs<<"\n";
	}	
	return 0;
}

