vector<pll> line;
vector<double> point;

// different slope
double inter(pll L1, pll L2) {
	return (double)(L1.se - L2.se) / (L2.fi - L1.fi);
}

void insert_line(ll m, ll n) {
	pll nl = pll(m, n);
	while (sz(line) >= 2 && inter(line[sz(line) - 2], line.back()) >= inter(line.back(), nl)) {
		line.pop_back();
		point.pop_back();
	}
	if (!line.empty()) {
		point.push_back(inter(line.back(),nl));
	}
	line.push_back(nl);
}

ll query_line(int x) {
	int p = lower_bound(all(point), x) - point.begin();
	return line[p].fi * x + line[p].se;
}