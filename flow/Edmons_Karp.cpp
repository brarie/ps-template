const int MXN = 800 + 5;
const ll INF = 1e14;

int N, M;
vector<int> adj[MXN];
int from[MXN];
ll flow[MXN][MXN], cap[MXN][MXN];

void add_edge(int u, int v, int c, int c_rev = 0) {
	adj[u].push_back(v);
	adj[v].push_back(u);
	cap[u][v] += c;
	cap[v][u] += c_rev;
}

ll rc(int x, int y) {
	return cap[x][y] - flow[x][y];
}

int bfs(int S, int T) {
	memset(from, -1, sizeof from);
	queue<int> q;
	q.push(S);
	from[S] = S;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (auto &nxt : adj[cur]) {
			if (from[nxt] == -1 && rc(cur, nxt) > 0) {
				from[nxt] = cur;
				if (nxt == T) {
					return 1;
				}
				q.push(nxt);
			}
		}
	}

	return 0;
}

ll maxFlow(int S, int T) {
	ll totalFlow = 0;
	while (bfs(S, T)) {
		ll curFlow = INF;
		for (int cur = T; cur != S; cur = from[cur]) {
			curFlow = min(curFlow, rc(from[cur], cur));
		}
		for (int cur = T; cur != S; cur = from[cur]) {
			flow[from[cur]][cur] += curFlow;
			flow[cur][from[cur]] -= curFlow;
		}
		totalFlow += curFlow;

	}

	return totalFlow;
}