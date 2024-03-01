struct MaxFlow {
    struct Edge {
        int nxt;
        int rev;
        ll res;
    };
    
    int sz;
    int S, T;
    ll MAXFLOW_INF = 1E14;
    vector<vector<Edge>> adj;
    vector<int> from_node;
    vector<int> from_edge;
    
    MaxFlow(int sz_): sz(sz_), adj(sz_) {}
    void setS(int S_) { S = S_; }
    void setT(int T_) { T = T_; }
    void setST(int S_, int T_) { setS(S_); setT(T_); }
    void add_edge(int u, int v, ll c) {
        Edge forward = { v, int(adj[v].size()), c };
        Edge reverse = { u, int(adj[u].size()), 0 };
        adj[u].push_back(forward);
        adj[v].push_back(reverse);
    }
    
    int bfs() {
    	from_node = vector<int>(sz, -1);
    	from_edge = vector<int>(sz, -1);
    	queue<int> q;
    	q.push(S);
    	from_node[S] = S;
    	while (!q.empty()) {
    		int cur = q.front();
    		q.pop();
            
            for (int i = 0; i < adj[cur].size(); i++) {
    		    auto &[nxt, rev, res] = adj[cur][i];
    			if (from_node[nxt] == -1 && res > 0) {
    				from_node[nxt] = cur;
    				from_edge[nxt] = i;
    				if (nxt == T) {
    					return 1;
    				}
    				q.push(nxt);
    			}
    		}
    	}
    
    	return 0;
    }
    
    ll maxFlow() {
    	ll totalFlow = 0;
    	while (bfs()) {
    		ll curFlow = MAXFLOW_INF;
    		for (int cur = T; cur != S; cur = from_node[cur]) {
    			curFlow = min(curFlow, adj[from_node[cur]][from_edge[cur]].res);
    		}
    		for (int cur = T; cur != S; cur = from_node[cur]) {
                int prv_node = from_node[cur];
                int prv_edge = from_edge[cur];
                adj[prv_node][prv_edge].res -= curFlow;
                adj[cur][adj[prv_node][prv_edge].rev].res += curFlow;
    		}
    		totalFlow += curFlow;
    
    	}
    
    	return totalFlow;
    }
};
