#include <bits/stdc++.h>

using namespace std;

#define int long long

const int maxn = 4e5 + 10, inf = 8e18;
int n;
vector<pair<int, int>> g[maxn];
int d[maxn];

void dijkstra(int s) {
    for (int i = 2 * 1; i <= 2 * n + 1; ++i) d[i] = inf;
    priority_queue<pair<int, int>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [dist, u] = pq.top(); pq.pop();
        if (d[u] != inf) continue;
        d[u] = -dist;
        for (auto [v, w] : g[u]) {
            pq.push({-(d[u] + w), v});
        }
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int m; cin >> n >> m;
    while (m--) {
        int u, v, w; cin >> u >> v >> w;
        g[2 * u].emplace_back(2 * v, w);
        g[2 * u + 1].emplace_back(2 * v + 1, w);
        g[2 * u].emplace_back(2 * v + 1, w / 2);
    }

    dijkstra(2 * 1);
    int ans = d[2 * n + 1];
    cout << ans << '\n';

    return 0;
}
