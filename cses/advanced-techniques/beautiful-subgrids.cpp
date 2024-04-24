#pragma GCC target("popcnt")

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3000;
bitset<maxn> bs[maxn];

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> bs[i];

    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int x = (bs[i] & bs[j]).count();
            ans += (x * (x - 1)) >> 1;
        }
    }
    cout << ans << '\n';

    return 0;
}
