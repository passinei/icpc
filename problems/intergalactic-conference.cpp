#include <bits/stdc++.h>

using namespace std;

// fft mod adapted from:
// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/FastFourierTransformMod.h

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1);  // (^ 10% faster if double)
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n); rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
    }
    vi rev(n);
    rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
            // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
            auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
            C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
            a[i + j + k] = a[i + j] - z;
            a[i + j] += z;
        }
}
typedef vector<ll> vl;
template<int M> vl convMod(const vl &a, const vl &b) {
    if (a.empty() || b.empty()) return {};
    vl res(sz(a) + sz(b) - 1);
    int B=32-__builtin_clz(sz(res)), n=1<<B, cut=int(sqrt(M));
    vector<C> L(n), R(n), outs(n), outl(n);
    rep(i,0,sz(a)) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
    rep(i,0,sz(b)) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
    fft(L), fft(R);
    rep(i,0,n) {
        int j = -i & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
    }
    fft(outl), fft(outs);
    rep(i,0,sz(res)) {
        ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
        ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);

        // res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
        res[i] = ((av * cut + bv) * cut + cv); // erased % M, original above
    }
    return res;
}

const int X = 500'001, M = 1'000'000'001;

vl A(X), B(X), a(X), b(X);

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int g, p; cin >> g >> p;
        A[g] = p;
        a[g] = 1;
    }
    for (int i = 0; i < m; ++i) {
        int g, p; cin >> g >> p;
        B[g] = p;
        b[g] = 1;
    }

    ll base = 0;

    for (int i = 1; i < X; ++i) {
        if (a[i] && b[i]) {
            base += (A[i] + B[i]);
            A[i] = 0;
            B[i] = 0;
        }
    }

    vl u = convMod<M>(A, b), v = convMod<M>(B, a);

    ll ans = 0;
    for (int i = 1; i < X; ++i) ans = max(ans, u[2 * i] + v[2 * i]);
    ans += base;
    cout << ans << '\n';

    return 0;
}
