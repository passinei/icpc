#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    const int maxn = 1e6 + 10;

    vector<int> t;
    vector<int> p(maxn, -1);

    {
        int x; cin >> x;
        t.push_back(0);
        p[x] = 0;
    }

    const int K = 1005;

    for (int i = 0; i < K + 5; ++i) {
        cout << "+ " << 1 << endl;
        int x; cin >> x;
        t.push_back(t.back() + 1);
        if (p[x] != -1) {
            int ans = t.back() - t[p[x]];
            cout << "! " << ans << endl;
            return 0;
        }
        p[x] = t.size() - 1;
    }

    for (int i = 0; i < K + 5; ++i) {
        cout << "+ " << K << endl;
        int x; cin >> x;
        t.push_back(t.back() + K);
        if (p[x] != -1) {
            int ans = t.back() - t[p[x]];
            cout << "! " << ans << endl;
            return 0;
        }
        p[x] = t.size() - 1;
    }

    return 0;
}