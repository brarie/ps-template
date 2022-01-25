const int MOD = 1e9 + 7;
const int NC = 4e6 + 5;

ll fact[NC], inv[NC];

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

void makecomb() {
	fact[0] = 1;
	for (ll i = 1; i < NC; i++)
		fact[i] = fact[i - 1] * i % MOD;
	inv[NC - 1] = minv(fact[NC - 1]);
	for (ll i = NC - 1; i > 0; i--)
		inv[i - 1] = inv[i] * i % MOD;
}

ll nCr(int n, int r) {
	if (n < r || n < 0 || r < 0) return 0;
	return fact[n] * inv[r] % MOD * inv[n - r] % MOD;
}