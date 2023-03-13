struct dsu {
    int n;
    vector<int> p;

    dsu(int _n) : n(_n) {
        p.resize(n);
        iota(p.begin(), p.end(), 0);
    }

    inline int find(int x) {
        return (x == p[x] ? x : (p[x] = find(p[x])));
    }

    inline bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) {
            return false;
        }
        p[u] = v;
        return true;
    }

    inline bool same(int u, int v) {
        return (find(u) == find(v));
    }
};