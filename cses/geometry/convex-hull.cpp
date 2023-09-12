#include <bits/stdc++.h>

using namespace std;

#define int long long

bool left(pair<int, int> A, pair<int, int> B, pair<int, int> C) {
    return
        (C.second - B.second) * (B.first - A.first)
        >
        (B.second - A.second) * (C.first - B.first);
}

vector<pair<int, int>> upper_hull(vector<pair<int, int>> a) {
    vector<pair<int, int>> res;
    for (auto p : a) {
        while (res.size() >= 2 && left(res[res.size() - 2], res.back(), p)) {
            res.pop_back();
        }
        res.push_back(p);
    }
    res.pop_back();
    return res;
}

vector<pair<int, int>> convex_hull(vector<pair<int, int>> a) {
    vector<pair<int, int>> res;
    sort(a.begin(), a.end());
    for (auto p : upper_hull(a)) res.push_back(p);
    reverse(a.begin(), a.end());
    for (auto p : upper_hull(a)) res.push_back(p);
    return res;
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (auto& [x, y] : a) cin >> x >> y;

    vector<pair<int, int>> ans = convex_hull(a);
    cout << (int) ans.size() << '\n';
    for (auto [x, y] : ans) cout << x << ' ' << y << '\n';
    
    return 0;
}
