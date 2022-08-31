vector<int> getLCP(string S, vector<int> sa) {
	int N = sz(S);
	vector<int> lcp(N), inv_sa(N);
	for (int i = 0; i < N; i++) {
		inv_sa[sa[i]] = i;
	}

	for (int i = 0, k = 0; i < N; i++) {
		if (inv_sa[i]) {
			for (int j = sa[inv_sa[i] - 1]; max(i + k, j + k) < N && S[i + k] == S[j + k]; k++);
			lcp[inv_sa[i]] = k;
			k = max(0, k - 1);
		}
	}

	return lcp;
}
