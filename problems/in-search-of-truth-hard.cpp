#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    const int maxn = 1e6 + 10;

    int mx = -1;
    {
        int x; cin >> x;
        mx = x;
    }

    const int K = 333;

    for (int i = 0; i < K; ++i) {
        int u = rng() % ((int) 1e6 - 1) + 1;
        cout << "+ " << u << endl;
        int x; cin >> x;
        mx = max(mx, x);
    }

    vector<int> t(maxn, -1);
    int sum = 0;

    for (int i = 0; i < K; ++i) {
        cout << "+ " << 1 << endl;
        int x; cin >> x;
        mx = max(mx, x);
        sum += 1;
        if (t[x] != -1) return cout << "! " << sum - t[x] << endl, 0;
        t[x] = sum;
    }

    {
        cout << "+ " << mx << endl;
        int x; cin >> x;
        sum += mx;
        if (t[x] != -1) return cout << "! " << sum - t[x] << endl, 0;
        t[x] = sum;
    }

    for (int i = 0; i < K; ++i) {
        cout << "+ " << K << endl;
        int x; cin >> x;
        sum += K;
        if (t[x] != -1) return cout << "! " << sum - t[x] << endl, 0;
        t[x] = sum;
    }

    return 0;
}