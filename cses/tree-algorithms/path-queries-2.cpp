#include <bits/stdc++.h>

using namespace std;

struct Seg {
    int T;
    vector<int> t;

    Seg(vector<int>& a) {
        T = 1;
        while (T < (int) a.size()) T *= 2;
        t.resize(2 * T, 0);
        for (int i = 0; i < T; ++i) t[i + T] = a[i];
        for (int i = T - 1; i; --i) t[i] = max(t[2 * i], t[2 * i + 1]);
    }

    void upd(int k, int x) {
        t[k += T] = x;
        for (int i = k / 2; i; i /= 2) t[i] = max(t[2 * i], t[2 * i + 1]);
    }

    int qry(int l, int r, int tl, int tr, int ptr) {
        if (tl > r || tr < l) return 0;
        if (tl >= l && tr <= r) return t[ptr];
        int mid = (tl + tr) / 2;
        return max(qry(l, r, tl, mid, 2 * ptr), qry(l, r, mid + 1, tr, 2 * ptr + 1));
    }
    int qry(int l, int r) { return qry(l, r, 0, T - 1, 1); }
};

const int maxn = 2e5 + 10;
const int maxk = 20;
int n;
vector<int> g[maxn];
int val[maxn];
int p[maxn];
int pt[maxn][maxk];
int sub[maxn];
int top[maxn];
int pos[maxn];
int dep[maxn];
vector<int> arr[maxn];
Seg* seg[maxn];

void dfs_ini(int u, int par) {
    sub[u] = 1;
    dep[u] = dep[par] + 1;
    p[u] = par;

    pt[u][0] = par;
    int w = par;
    for (int i = 1; i < maxk; ++i) pt[u][i] = w = pt[w][i - 1];

    for (int v : g[u]) {
        if (v == par) continue;
        dfs_ini(v, u);
        sub[u] += sub[v];
    }
}

void dfs_hld(int u, int tp) {
    top[u] = tp;
    pos[u] = arr[tp].size();
    arr[tp].push_back(val[u]);
    if (sub[u] == 1) return;
    pair<int, int> mx = {-1, -1};
    for (int v : g[u]) {
        if (v == p[u]) continue;
        mx = max(mx, {sub[v], v});
    }
    int big = mx.second;
    dfs_hld(big, tp);
    for (int v : g[u]) {
        if (v == big || v == p[u]) continue;
        dfs_hld(v, v);
    }
}

int lca(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    int k = dep[v] - dep[u];
    for (int i = 0; i < maxk; ++i) {
        if (k & (1 << i)) v = pt[v][i];
    }
    if (u == v) return u;
    for (int i = maxk - 1; i >= 0; --i) {
        if (pt[u][i] != pt[v][i]) u = pt[u][i], v = pt[v][i];
    }
    if (u != v) u = p[u], v = p[v];
    return u;
}

int pth_qry(int anc, int u) {
    if (top[u] == top[anc]) return seg[top[u]]->qry(pos[anc], pos[u]);
    int ans = seg[top[u]]->qry(pos[top[u]], pos[u]);
    u = p[top[u]];
    while (top[u] != top[anc]) {
        ans = max(ans, seg[top[u]]->qry(pos[top[u]], pos[u]));
        u = p[top[u]];
    }
    ans = max(ans, seg[top[u]]->qry(pos[anc], pos[u]));
    return ans;
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> val[i];

    for (int i = 0; i < n - 1; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs_ini(1, 0);
    dfs_hld(1, 1);

    for (int i = 1; i <= n; ++i) {
        if (i == top[i]) seg[i] = new Seg(arr[i]);
    }

    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int u, x; cin >> u >> x;
            seg[top[u]]->upd(pos[u], x);
        } else {
            int u, v; cin >> u >> v;
            int anc = lca(u, v);
            int ans = max(pth_qry(anc, u), pth_qry(anc, v));
            cout << ans << ' ';
        }
    }
    cout << '\n';

    return 0;
}
