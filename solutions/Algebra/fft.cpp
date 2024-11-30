const double PI = acos(-1)

struct complex_t {
  double a {0.0}, b {0.0};
  complex_t() {}
  complex_t(double na, double nb) : a{na}, b{nb} {}
  const complex_t operator+(const complex_t &c) const {
    return complex_t(a + c.a, b + c.b);
  }
  const complex_t operator-(const complex_t &c) const {
    return complex_t(a - c.a, b - c.b);
  }
  const complex_t operator*(const complex_t &c) const {
    return complex_t(a*c.a - b*c.b, a*c.b + b*c.a);
  }
};
using base = complex_t;
//using base = complex<double>;


vector<long long> polinomio;

void fft (vector<base> & a, bool invert) 
{
	int n = (int) a.size();
 
	for (int i=1, j=0; i<n; ++i) 
	{
		int bit = n >> 1;
		for (; j>=bit; bit>>=1)
			j -= bit;
		j += bit;
		if (i < j)
			swap (a[i], a[j]);
	}
	for (int len=2; len<=n; len<<=1) 
	{
		double ang = 2*PI/len * (invert ? -1 : 1);
		base wlen (cos(ang), sin(ang));
		for (int i=0; i<n; i+=len) {
			base w =  complex_t(1.0, 0.0);
			for (int j = 0; j < len/2; ++j) {
				base u = a[i+j],  v = a[i+j+len/2] * w;
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
				w = w * wlen;
			}
		}
	}
	if (invert)
		for (int i=0; i<n; ++i)
			a[i].a /= n, a[i].b /= n;
}
void multiply(vector<int> &a, vector<int> &b){
	polinomio.clear();
	vector<base>fa;
	vector<base>fb;
	int n = 1;
	while(n < a.size() + b.size())
		n <<= 1;
	fa.resize(n);
	fb.resize(n);
	for (int i = 0; i < a.size(); i++)
		fa[i] = complex_t(a[i], 0.0);
	for (int i = 0; i < b.size(); i++)
		fb[i] = complex_t(b[i], 0.0);
	fft(fa, false);
	fft(fb, false);
	for (int i = 0; i < n; i++)
		fa[i] = fa[i] * fb[i];
	fft(fa, true);

	for (int i = 0; i < n; i++){
		//cout << i << " " << fa[i].a << endl;
		polinomio.push_back(round(fa[i].a));
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	vector<int> a = {1, 2, 4};
	vector<int> b = {1, 3};
	multiply(a, b);
	for (auto ci: polinomio)
		cout << ci << " ";
	cout << endl;
	return 0;
}
