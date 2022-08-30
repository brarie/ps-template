vector<int> suffixArray(string S) {
	int N = sz(S);
	const int M = max(N, 26) + 1;
	vector<int> sa(N), g(N + 1), ng(N + 1);
	vector<int> cnt(M), nsa(N);

	for (int i = 0; i < N; i++) {
		sa[i] = i;
		g[i] = S[i] - 'a' + 1;
	}
	g[N] = 0;
	for (int k = 1; k < N; k <<= 1) {
		auto cmp = [&](const int &u, const int &v) {
			if (g[u] == g[v]) {
				return g[u + k] < g[v + k];
			}

			return g[u] < g[v];
		};
		auto countingSort = [&](int x) {
			for (int i = 0; i < M; i++) {
				cnt[i] = 0;
			}
			for (int i = 0; i < N; i++) {
				cnt[g[min(sa[i] + x, N)]]++;
			}
			for (int i = 1; i < M; i++) {
				cnt[i] += cnt[i - 1];
			}
			for (int i = N - 1; i >= 0; i--) {
				nsa[--cnt[g[min(sa[i] + x, N)]]] = sa[i];
			}
			sa = nsa;
		};
		countingSort(k);
		countingSort(0);

		ng[sa[0]] = 1, ng[N] = 0;
		for (int i = 1; i < N; i++) {
			ng[sa[i]] = ng[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
		}
		swap(g, ng);
	}

	return sa;
}