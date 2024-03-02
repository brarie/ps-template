struct Bipartite_Matching {
    int L_sz, R_sz;
    vector<vector<int>> adj;
    vector<int> y_match;
    vector<int> tried_match;
    
    Bipartite_Matching(int L_sz_, int R_sz_): L_sz(L_sz_), R_sz(R_sz_), adj(L_sz_) {};
    
    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }
    
    bool try_match(int cur) {
        if (tried_match[cur]) {
            return false;
        }
        tried_match[cur] = true;
        for (auto &nxt : adj[cur]) {
            if (y_match[nxt] == -1 || try_match(y_match[nxt])) {
                y_match[nxt] = cur;
                return true;
            }
        }
        
        return false;
    }
    
    int get_match() {
        int ret = 0;
        y_match = vector<int>(R_sz, -1);
        for (int i = 0; i < L_sz; i++) {
            tried_match = vector<int>(L_sz, 0);
            if (try_match(i)) {
                ret += 1;
            }
        }
        
        return ret;
    }
};
