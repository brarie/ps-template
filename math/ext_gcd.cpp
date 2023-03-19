// Solve ax + by = c
// Goal: Find x, y such that 0 <= x < b
pair<ll, ll> ext_gcd(ll a, ll b, ll c) {
    if (b == 0) {
        return {1, 0};
    }
    auto [prv_x, prv_y] = ext_gcd(b, a % b, c);
    ll cur_x = (prv_y % b + b) % b;
    ll cur_y = (c - __int128(a) * cur_x) / b;
    return {cur_x, cur_y};
}