struct MCMF {
    struct Edge {
        int nxt;
        int rev;
        int res;
        int cost;
    };
    
    int sz;
    int S, T;
    int MCMF_INF = int(1E9);
    vector<vector<Edge>> adj;
    vector<int> dist;
    vector<int> inQ;
    vector<int> from_node;
    vector<int> from_edge;
    
    
    // 0-based MCMF
    MCMF(int sz_): sz(sz_), adj(sz_), from_node(sz_), from_edge(sz_) {}
    void setS(int S_) { S = S_; }
    void setT(int T_) { T = T_; }
    void setST(int S_, int T_) { setS(S_); setT(T_); }
    
    void add_edge(int u, int v, int cap, int cost) {
        Edge forward = { v, int(adj[v].size()), cap, cost };
        Edge reverse = { u, int(adj[u].size()), 0, -cost };
        adj[u].push_back(forward);
        adj[v].push_back(reverse);
    }
    
    bool spfa() {
        dist = vector<int>(sz, MCMF_INF);
        inQ = vector<int>(sz, 0);
        queue<int> q;
        q.push(S);
        inQ[S] = 1;
        dist[S] = 0;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            inQ[cur] = 0;
            for (int i = 0; i < adj[cur].size(); i++) {
                auto &[nxt, rev, res, cost] = adj[cur][i];
                if (res > 0 && dist[nxt] > dist[cur] + cost) {
                    dist[nxt] = dist[cur] + cost;
                    from_node[nxt] = cur;
                    from_edge[nxt] = i;
                    if (!inQ[nxt]) {
                        inQ[nxt] = 1;
                        q.push(nxt);
                    }
                }
            }
        }
        
        return dist[T] != MCMF_INF;
    }
    
    pair<int, int> getMCMF() {
        int total_flow = 0, total_cost = 0;
        while (spfa()) {
            int cur_flow = MCMF_INF;
            for (int cur = T; cur != S; cur = from_node[cur]) {
                cur_flow = min(cur_flow, adj[from_node[cur]][from_edge[cur]].res);
            }
            for (int cur = T; cur != S; cur = from_node[cur]) {
                int prv_node = from_node[cur];
                int prv_edge = from_edge[cur];
                adj[prv_node][prv_edge].res -= cur_flow;
                adj[cur][adj[prv_node][prv_edge].rev].res += cur_flow;
                total_cost += cur_flow * adj[prv_node][prv_edge].cost;
            }
            total_flow += cur_flow;
        }
        
        return make_pair(total_flow, total_cost);
    }
};
