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

ll dist(Point a, Point b) {
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

vector<Point> convexHull(vector<Point> pts) {
    int N = size(pts);
    Point p = *min_element(pts.begin(), pts.end());
    sort(pts.begin(), pts.end(), [&](const Point &u, const Point &v) {
        int t = ccw(p, u, v);
        if (t == 0) {
            return dist(p, u) < dist(p, v);
        }
        return t > 0;
    });

    vector<Point> res;
    for (int i = 0; i < N; i++) {
        while (size(res) >= 2 && ccw(res.end()[-2], res.end()[-1], pts[i]) <= 0) {
            res.pop_back();
        }
        res.push_back(pts[i]);
    }

    return res;
}