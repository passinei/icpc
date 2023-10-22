#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 1, maxk = 20, inf = 2e9;
vector<int> g[maxn];
int rmv[maxn];
int sz[maxn];
int d[maxk][maxn];
int r[maxk][maxn];
int red[maxk][maxn];

int subtree_size(int u, int p) {
    sz[u] = 1;
    for (int v : g[u]) {
        if (v == p || rmv[v]) continue;
        sz[u] += subtree_size(v, u);
    }
    return sz[u];
}

int find_centroid(int u, int p, int n) {
    for (int v : g[u]) {
        if (v == p || rmv[v]) continue;
        if (sz[v] * 2 > n) return find_centroid(v, u, n);
    }
    return u;
}

void process(int cen, int layer) {
    queue<int> q;
    q.push(cen);
    d[layer][cen] = 0;
    r[layer][cen] = cen;
    red[layer][cen] = inf;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            if (rmv[v] || r[layer][v]) continue;
            d[layer][v] = d[layer][u] + 1;
            r[layer][v] = cen;
            q.push(v);
        }
    }
}

void centroid_decomp(int u, int layer) {
    int cen = find_centroid(u, 0, subtree_size(u, 0));

    process(cen, layer);

    rmv[cen] = 1;
    for (int v : g[cen]) {
        if (rmv[v]) continue;
        centroid_decomp(v, layer + 1);
    }
}

void mark(int u) {
    for (int layer = 0; r[layer][u]; ++layer) {
        int cen = r[layer][u];
        red[layer][cen] = min(red[layer][cen], d[layer][u]);
    }
}

int qry(int u) {
    int res = inf;
    for (int layer = 0; r[layer][u]; ++layer) {
        int cen = r[layer][u];
        res = min(res, d[layer][u] + red[layer][cen]);
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n, q; cin >> n >> q;
    for (int i = 0; i < n - 1; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    centroid_decomp(1, 0);
    mark(1);

    while (q--) {
        int tp, u; cin >> tp >> u;
        if (tp == 1) {
            mark(u);
        } else {
            int ans = qry(u);
            cout << ans << '\n';
        }
    }

    return 0;
}
