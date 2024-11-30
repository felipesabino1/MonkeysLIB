int VALS_IN_EDGES = 0;
// namespace HLD { 
	int n; 
    vector<int> adj[N];
	int par[N], root[N], dep[N], sz[N], ti;
	int pos[N]; 
    vector<int> rpos; // rpos not used but could be useful
	void add_edge(int x, int y) { adj[x].pb(y), adj[y].pb(x); }
	void dfsSz(int x) { 
		sz[x] = 1; 
		for(auto y:adj[x]) {
			par[y] = x; dep[y] = dep[x]+1;
			adj[y].erase(find(all(adj[y]),x)); /// remove parent from adj list
			dfsSz(y); sz[x] += sz[y];
			if (sz[y] > sz[adj[x][0]]) swap(y,adj[x][0]);
		}
	}
	void dfsHld(int x) {
		pos[x] = ti++; rpos.pb(x);
		for(auto y:adj[x]) {
			root[y] = (y == adj[x][0] ? root[x] : y);
			dfsHld(y); 
        }
	}
	void init(int nn, int r = 1) { 
        n = nn; 
		par[r] = dep[r] = ti = 0; 
        dfsSz(r); 
		root[r] = r; 
        dfsHld(r); 
        // build(1, 1, n);
	}
	int lca(int x, int y) {
		for (; root[x] != root[y]; y = par[root[y]])
			if (dep[root[x]] > dep[root[y]]) swap(x,y);
		return dep[x] < dep[y] ? x : y;
	}
	int dist(int x, int y) { // # edges on path
	 	return dep[x]+dep[y]-2*dep[lca(x,y)]; 
    }
	template <class BinaryOp>
	void processPath(int x, int y, BinaryOp op) {
		for (; root[x] != root[y]; y = par[root[y]]) {
			if (dep[root[x]] > dep[root[y]]) 
                swap(x,y);
			op(pos[root[y]],pos[y]); 
        }
		if (dep[x] > dep[y]) 
            swap(x,y);
		op(pos[x]+VALS_IN_EDGES,pos[y]); 
	}
	void modifyPath(int x, int y, int v) { 
		processPath(x,y,[&v](int l, int r) { 
			updt(1, 1, n, l, r, v); }); 
    }
    void modifyVert(int x, int v) { 
		updt(1,1,n,pos[x],pos[x],v); 
    }
	ll queryPath(int x, int y) { 
		ll res = 0; processPath(x,y,[&res](int l, int r) { 
			res = f(res,query(1, 1, n, l, r)); });
		return res; 
    }
	void modifySubtree(int x, int v) { 
		updt(1,1,n,pos[x]+VALS_IN_EDGES,pos[x]+sz[x]-1,v); 
    }