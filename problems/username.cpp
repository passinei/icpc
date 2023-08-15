#include <bits/stdc++.h>

using namespace std;

#define int long long
#define sz(x) ((int) (x).size())

const int maxn = 1e5 + 10;
const int P = 37, M = 1000133333;

string s, t;
int p[maxn];
int invp;

int fexp(int a, int b) {
    if (b == 0) return 1 % M;
    int f = fexp(a, b / 2);
    f = (f * f) % M;
    if (b % 2) f = (f * a) % M;
    return f;
}

int inv(int n) {
    return fexp(n, M - 2);
}

int ord(char ch) {
    return ch - 'a' + 1;
}

vector<int> hsh(string& a, int len) {
    vector<int> res;
    int h = 0;
    for (int i = 0; i < len; ++i) {
        h = (h + ord(a[i]) * p[i]) % M;
    }
    res.push_back(h);
    for (int i = len; i < sz(a); ++i) {
        h = (h + M - ord(a[i - len]) * p[0]) % M;
        h = (h * invp) % M;
        h = (h + ord(a[i]) * p[len - 1]) % M;
        res.push_back(h);
    }
    return res;
}

int f(int len) {
    vector<int> ht = hsh(t, len);
    sort(ht.begin(), ht.end());
    vector<int> hs = hsh(s, len);
    sort(hs.begin(), hs.end());
    int ptr = 0;
    for (int h : hs) {
        while (ptr < sz(ht) && ht[ptr] < h) ++ptr;
        if (ht[ptr] != h) return 1;
    }
    return 0;
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    p[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        p[i] = (p[i - 1] * P) % M;
    }
    invp = inv(P);

    cin >> s >> t;

    int l = 1, r = sz(s);
    while (l < r) {
        int mid = (l + r) / 2;
        if (f(mid)) r = mid;
        else l = mid + 1;
    }
    if (!f(l)) cout << "-1\n";
    else cout << l << '\n';

    return 0;
}
