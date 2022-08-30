vector<int> suffixArray(string S) {
	int N = sz(S);
	vector<int> sa(N), g(N + 1);
	for (int i = 0; i < N; i++) {
		sa[i] = i;
		g[i] = S[i];
	}
	g[N] = -1;
	for (int k = 1; k < N; k <<= 1) {
		auto cmp = [&](const int &u, const int &v) {
			if (g[u] == g[v]) {
				return g[u + k] < g[v + k];
			}

			return g[u] < g[v];
		};

		sort(all(sa), cmp);
		vector<int> ng(N + 1);
		ng[sa[0]] = 0, ng[N] = -1;
		for (int i = 1; i < N; i++) {
			ng[sa[i]] = ng[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
		}
		swap(g, ng);
	}

	return sa;
}