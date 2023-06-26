#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5 + 1;
const int r = sqrt(maxn) + 1;

pii a[maxn];
vector<int> v[maxn];
vector<int> w[maxn];

const int M = 10733791, P = 105883;
vector<pii> t[M];

int hsh(int x, int y) {
    return ((long long) x * P + y) % M;
}

void insert(int x, int y) {
    int h = hsh(x, y);
    t[h].emplace_back(x, y);
}

bool query(int x, int y) {
    if (x < 0 || x >= maxn || y < 0 || y >= maxn) return 0;
    int h = hsh(x, y);
    int fnd = 0;
    for (auto q : t[h]) {
        if (q.first == x && q.second == y) {
            fnd = 1;
            break;
        }
    }
    return fnd;
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
    sort(a, a + n);

    for (int i = 0; i < n; ++i) insert(a[i].first, a[i].second);

    long long ans = 0;

    for (int i = 0; i < n; ++i) v[a[i].first].push_back(a[i].second);

    for (int x = 0; x < maxn; ++x) {
        int m = v[x].size();
        if (m < r) {
            for (int i = 0; i < m; ++i) {
                for (int j = i + 1; j < m; ++j) {
                    int d = v[x][j] - v[x][i];
                    ans += query(x - d, v[x][i]) && query(x - d, v[x][j]);
                    if (x + d < maxn && v[x + d].size() >= r) {
                        ans += query(x + d, v[x][i]) && query(x + d, v[x][j]);
                    }
                }
            }
        } else {
            for (int i = 0; i < m; ++i) w[v[x][i]].push_back(x);
        }
    }

    for (int y = 0; y < maxn; ++y) {
        int m = w[y].size();
        for (int i = 0; i < m; ++i) {
            for (int j = i + 1; j < m; ++j) {
                int d = w[y][j] - w[y][i];
                ans += query(w[y][i], y - d) && query(w[y][j], y - d);
            }
        }
    }

    cout << ans << '\n';

    return 0;
}