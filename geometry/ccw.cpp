using Point = pair<ll, ll>;

int ccw(Point a, Point b, Point c) {
    ll T = a.first * b.second + b.first * c.second + c.first * a.second;
    T -= b.first * a.second + c.first * b.second + a.first * c.second;
    if (T > 0) {
        return 1;
    } else if (T < 0) {
        return -1;
    }
    return 0;
}