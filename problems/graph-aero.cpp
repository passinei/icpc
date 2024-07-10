#include <bits/stdc++.h>

using namespace std;

const int maxn = 100'001;

int n;

int ccp[maxn], ccsz[maxn];

int p[maxn];
int f[maxn];

int vis[maxn];
int vis_it;

int bridges;

void build() {
    bridges = 0;
    for (int i = 1; i <= n; ++i) {
        ccp[i] = i;
        ccsz[i] = 1;
        p[i] = 0;
        f[i] = i;
        vis[i] = -1;
    }
    vis_it = 0;
}

int ccfind(int u) {
    if (u == ccp[u]) return u;
    return ccp[u] = ccfind(ccp[u]);
}

int find(int u) {
    if (u == f[u]) return u;
    return f[u] = find(f[u]);
}

void root(int u) {
    u = find(u);
    int r = u;
    vector<int> a;
    while (u) {
        a.push_back(u);
        u = find(p[u]);
    }
    for (int i = 1; i < a.size(); ++i) p[a[i]] = a[i - 1];
    for (auto x : a) {
        ccsz[r] = max(ccsz[r], ccsz[x]);
        ccp[x] = r;
    }
}

void add_edge(int u, int v) {
    u = find(u), v = find(v);
    int fu = ccfind(u), fv = ccfind(v);
    if (fu != fv) {
        if (ccsz[fu] < ccsz[fv]) swap(u, v), swap(fu, fv);
        root(v);
        p[v] = u;
        fv = v;
        ccp[fv] = fu;
        ccsz[fu] += ccsz[fv];
        ++bridges;
    } else if ((u) != (v)) {
        int lca = -1;
        ++vis_it;
        vector<int> pu, pv;
        while (lca == -1) {
            if (u) {
                u = find(u);
                pu.push_back(u);
                if (vis[u] == vis_it) { lca = u; break; }
                else vis[u] = vis_it;
                u = (p[u]);
            }
            if (v) {
                v = find(v);
                pv.push_back(v);
                if (vis[v] == vis_it) { lca = v; break; }
                else vis[v] = vis_it;
                v = (p[v]);
            }
        }
        for (auto x : pu) {
            f[x] = lca;
            if (x == lca) break;
            --bridges;
        }
        for (auto x : pv) {
            f[x] = lca;
            if (x == lca) break;
            --bridges;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    freopen("bridges.in", "r", stdin);
    freopen("bridges.out", "w", stdout);

    int m;
    cin >> n >> m;

    build();

    while (m--) {
        int u, v; cin >> u >> v;
        add_edge(u, v);
    }
    int k; cin >> k;
    while (k--) {
        int u, v; cin >> u >> v;
        add_edge(u, v);
        cout << bridges << '\n';
    }

    return 0;
}
