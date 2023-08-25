#include <bits/stdc++.h>

using namespace std;

#define int long long

struct P {
    int x, y;
};

bool comp_x(const P& l, const P& r) {
    if (l.x != r.x) return l.x < r.x;
    return l.y < r.y;
}

struct comp_y {
    bool operator()(const P& l, const P& r) const {
        if (l.y != r.y) return l.y < r.y;
        return l.x < r.x;
    }
};

int dist(const P& l, const P& r) {
    int dx = l.x - r.x, dy = l.y - r.y;
    return dx * dx + dy * dy;
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n; cin >> n;
    vector<P> a(n);
    for (auto& [x, y] : a) cin >> x >> y;
    sort(a.begin(), a.end(), comp_x);

    int ans = 8e18;

    set<P, comp_y> c;
    c.insert(a[0]);

    int p = -1;
    for (int i = 1; i < n; ++i) {
        ans = min(ans, dist(a[i], a[i - 1]));
 
        int sq = ceil(sqrt(ans));
        while (a[i].x - a[p + 1].x >= sq) {
            ++p;
            c.erase(a[p]);
        }

        auto l = c.lower_bound({(int) -1e9, a[i].y - sq});
        auto r = c.upper_bound({(int) 1e9, a[i].y + sq});
        for (auto q = l; q != r; ++q) {
            ans = min(ans, dist(a[i], *q));
        }

        c.insert(a[i]);
    }

    cout << ans << '\n';

    return 0;
}
