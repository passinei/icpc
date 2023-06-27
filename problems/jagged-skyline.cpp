#include <bits/stdc++.h>

using namespace std;

#define int long long

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    random_device rd;
    mt19937 g(rd());

    int w, h; cin >> w >> h;

    vector<int> v(w);
    for (int i = 1; i <= w; ++i) v[i - 1] = i;
    shuffle(v.begin(), v.end(), g);

    pair<int, int> ans = make_pair(0, w);
    for (int i = 0; i < w; ++i) {
        int x = v[i];

        cout << "? " << x << ' ' << ans.first + 1 << endl;
        string s; cin >> s;
        if (s[0] == 's') continue;

        int l = 0, r = h;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            cout << "? " << x << ' ' << mid << endl;
            string s; cin >> s;
            if (s[0] == 's') {
                r = mid - 1;
            } else {
                l = mid;
            }
        }
        int y = l;
        ans = make_pair(y, x);
        if (ans.first == h) return cout << "! " << ans.second << ' ' << ans.first << endl, 0;
    }
    
    cout << "! " << ans.second << ' ' << ans.first << endl;

    return 0;
}
