#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;

int timer;
vector<int> tin, low;
vector<pair<int, int>> bridges;

void dfs(int u, int p) {
    low[u] = tin[u] = timer++;
    for (int v : g[u]) {
        if (v == p) continue;
        if (tin[v] != -1) low[u] = min(low[u], tin[v]);
        else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) {
                bridges.emplace_back(min(u, v), max(u, v));
            }
        }
    }
}

void find_bridges() {
    int n = g.size();
    timer = 0;
    tin.assign(n, -1);
    low.assign(n, -1);
    bridges.clear();
    for (int i = 0; i < n; ++i) {
        if (tin[i] != -1) continue;
        dfs(i, -1);
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n, m; cin >> n >> m;
    g.resize(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    find_bridges();

    cout << (int) bridges.size() << '\n';
    for (auto&[u, v] : bridges) cout << u + 1 << ' ' << v + 1 << '\n';

    return 0;
}
