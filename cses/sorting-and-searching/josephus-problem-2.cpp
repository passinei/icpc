#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using namespace std;

typedef tree<
    int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update
> indexed_set;

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n, k; cin >> n >> k;

    indexed_set c;
    for (int i = 1; i <= n; ++i) c.insert(i);

    vector<int> ans;
    int p = 0;
    while (c.size()) {
        p = (p + k) % ((int) c.size());
        int x = *c.find_by_order(p);
        ans.push_back(x);
        c.erase(x);
    }

    for (int x : ans) cout << x << ' ';
    cout << '\n';

    return 0;
}
