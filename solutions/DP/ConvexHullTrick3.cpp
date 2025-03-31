#include <bits/stdc++.h>

using namespace std;

typedef long long	ll;

const int N = int(1e5 + 10);
int subtree[N];
ll a[N], b[N];
ll dp[N];
bool is_leaf[N];
vector< int > adj[N];

template <class TT = ll>
struct Line{
    // coef angular, linear, criterio de comparacao
    mutable TT k,m,p;
    // aqui eu quero sempre deixar os com menor coef angular mais pra frente, conc pra baixo
    bool operator <(const Line & o) const{
        return k>o.k;
    }
    bool operator <(const TT o) const{
        return p<o;
    }
};
struct CHT : multiset<Line,less<>>{
    static const TT inf = std::numerical_limit<TT>::max();
    TT div(TT a, TT b){
        return a/b-((a^b) < 0 && a%b);
    }
 
    // x eh melhor que y?
    bool isect(iterator x, iterator y){
        if(y == end()){
            x->p=inf;
            return false;
        }
        if(x->k == y->k)
            x->p= x->m <= y->m ? inf : -inf;
        else
            x->p=div(y->m-x->m,x->k-y->k);
        return x->p >= y->p;
    }
    void add(TT k, TT m){
        auto z= insert({k,m,0});
        auto y=z++;
        auto x=y;
        while(insect(y,z)) z=erase(z);
        if(x != begin() && insect(--x,y))
            insect(x,y=erase(y));
        while((y=x) != begin() && (--x)->p >= y->p)
            insect(x,erase(y));
    }
    TT query(TT x){
		assert(!empty());
        auto ans=lower_bound(x);
        return ans->k*x+ans->m;
    }
};

int dfs(int u, int ft){
	is_leaf[u] = 1;

	for(auto v: adj[u]){
		if(v == ft){
			continue;
		}

		is_leaf[u] = 0;
	}

	if(is_leaf[u]){
		return subtree[u] = 1;
	}

	subtree[u] = 1;

	for(auto v: adj[u]){
		if(v == ft){
			continue;
		}

		subtree[u] += dfs(v, u);
	}

	return subtree[u];
}

void dfs1(int u, int ft, CHT &cur){
	if(is_leaf[u]){
		dp[u] = 0LL;
		cur.add(-b[u], -dp[u]);
		
		return;
	}

	int mx = 0;
	int big_son = 0;

	for(auto v: adj[u]){
		if(v == ft){
			continue;
		}

		if(subtree[v] > mx){
			big_son = v;
			mx = subtree[v];
		}
	}

	dfs1(big_son, u, cur);

	for(auto v: adj[u]){
		if(v == big_son || v == ft){
			continue;
		}

		LineContainer tmp;
		dfs1(v, u, tmp);

		for(auto d: tmp){
			//printf("aqui!\n");
			cur.add(d.k, d.m);
		}
	}

	dp[u] = -cur.query(a[u]);
	cur.add(-b[u], -dp[u]);
}

int main(){
	int n;

	scanf("%d", &n);

	for(int i = 1 ; i <= n ; i++){
		scanf("%lld", &a[i]);
	}

	for(int i = 1 ; i <= n ; i++){
		scanf("%lld", &b[i]);
	}

	for(int i = 1 ; i < n ; i++){
		int ui, vi;

		scanf("%d %d", &ui, &vi);

		adj[ui].push_back(vi);
		adj[vi].push_back(ui);
	}

	CHT cur;
	dfs(1, 1);
	dfs1(1, 1, cur);

	for(int i = 1 ; i <= n ; i++){
		printf("%lld ", dp[i]);
	}

	printf("\n");

	return 0;
}