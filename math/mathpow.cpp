const int MOD = 1e9 + 7;

ll mpow(ll a, ll b) {
	ll ret = 1;
	a %= MOD;
	while (b) {
		if (b & 1) {
			ret = (a * ret) % MOD;
		}
		b >>= 1;
		a = (a * a) % MOD;
	}
	return ret;
}

ll minv(ll a) {
	return mpow(a, MOD - 2);
}