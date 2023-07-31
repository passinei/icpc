#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4 + 1, inf = 2e9 + 1;
int n, m;
vector<int> g[maxn];
int d[7][maxn];
int f;
int h[maxn];
int k;
int p[6];
int c[maxn];
int car[maxn];
bitset<64> drv[maxn];
int dp[maxn][64];

void bfs(int r) {
    queue<int> q;
    q.push(r);
    d[c[r]][r] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            if (d[c[r]][v] < inf) continue;
            d[c[r]][v] = d[c[r]][u] + 1;
            q.push(v);
        }
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int tc; cin >> tc; while (tc--) {
        cin >> n >> m;

        for (int i = 1; i <= n; ++i) {
            g[i].clear();
            for (int j = 0; j < 7; ++j) d[j][i] = inf;
        }

        for (int i = 0; i < m; ++i) {
            int u, v; cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        cin >> f;
        for (int i = 1; i <= f; ++i) {
            drv[i].reset();
            drv[i][0] = 1;
            cin >> h[i];
            car[i] = 1;
        }

        cin >> k;
        for (int i = 0; i < k; ++i) {
            cin >> p[i];
            car[p[i]] = 0;
        }
        c[1] = 0;
        for (int i = 0; i < k; ++i) c[h[p[i]]] = i + 1;

        bfs(1);
        for (int i = 0; i < k; ++i) bfs(h[p[i]]);

        for (int msk = 1; msk < (1 << k); ++msk) {
            vector<int> ppl;
            for (int i = 0; i < k; ++i) {
                if (msk & (1 << i)) ppl.push_back(p[i]);
            }
            for (int i = 1; i <= f; ++i) {
                if (!car[i]) continue;
                int gdist = d[0][h[i]];
                sort(ppl.begin(), ppl.end());
                int fnd = 0;
                do {
                    int dist = d[0][h[ppl[0]]];
                    for (int j = 1; j < (int) ppl.size(); ++j) {
                        dist += d[c[h[ppl[j - 1]]]][h[ppl[j]]];
                    }
                    dist += d[c[h[ppl.back()]]][h[i]];
                    if (dist == gdist) fnd = 1;
                } while (next_permutation(ppl.begin(), ppl.end()));
                if (fnd) drv[i][msk] = 1;
            }
        }

        for (int i = 0; i <= f; ++i) {
            for (int j = 0; j < (1 << k); ++j) {
                if (i == 0) dp[i][j] = j == 0;
                else {
                    dp[i][j] = 0;
                    for (int msk = 0; msk <= j; ++msk) {
                        if (!drv[i][msk]) continue;
                        if (j - msk != (j ^ msk)) continue;
                        if (dp[i - 1][j ^ msk]) dp[i][j] = 1;
                    }
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < (1 << k); ++i) {
            if (dp[f][i]) {
                ans = max(ans, __builtin_popcount(i));
            }
        }
        ans = k - ans;
        cout << ans << '\n';
    }

    return 0;
}
