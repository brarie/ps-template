struct dsu {
	int n;
	vector<int> p;

	dsu(int _n) : n(_n) {
		p.resize(n);
		iota(all(p), 0);
	}

	inline int find(int x) {
		return (x == p[x] ? x : (p[x] = find(p[x])));
	}

	inline void merge(int u, int v) {
		u = find(u), v = find(v);
		if (u == v) return;
		p[u] = v;
	}
};