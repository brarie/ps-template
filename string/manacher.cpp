vector<int> manacher_odd(string S) {
	int N = sz(S);
	S = "#" + S + "$";
	vector<int> p(N + 2);
	int l = 0, r = 1;
	for (int i = 1; i <= N; i++) {
		if (i < r) {
			p[i] = min(r - i, p[l + r - i]);
		}
		while (S[i - p[i]] == S[i + p[i]]) {
			p[i]++;
		}
		if (i + p[i] > r) {
			l = i - p[i];
			r = i + p[i];
		}
	}

	return vector<int>(begin(p) + 1, end(p) - 1);
}

// d0 := i번 문자가 중심일 때, 뻗어나갈 수 있는 최대 길이
// d1 := i-1, i번 문자가 중심일 때, 뻗어나갈 수 있는 최대 길이
// ex) "aba" 인 경우, d1[1] = 1, d2[2] = 0, d0[0] = 1, d0[1] = 2, d0[2] = 1;
pair<vector<int>, vector<int>> manacher(string S) {
	int N = sz(S);
	string T;
	for (auto &s : S) {
		T += string("#") + s;
	}
	vector<int> res = manacher_odd(T + "#");
	vector<int> d0(N);
	vector<int> d1(N);
	for (int i = 1; i + 1 < sz(res); i++) {
		(i % 2 ? d0[i / 2] : d1[i / 2]) = res[i] / 2;
	}

	return { d0, d1 };
}