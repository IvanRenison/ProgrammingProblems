// https://codeforces.com/gym/104875
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(), x.end()
#define SZ(x) ll(x.size())
#define fore(i, a, b) for (ll i = a; i < b; ++i)
#define mset(a, v) memset((a), (v), sizeof(a))
#define pb push_back
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
constexpr ld EPS = 1e-8;

ll s;

ll sqrtfl(ld x) {
    ll l = 0, r = x;
    while (l <= r) {
        ll m = (l + r) / 2;
        if (m * m <= x)
            l = m + 1;
        else
            r = m - 1;
    }
    return r;
}

bool can(ld m) {
    ll cnt = 0;
    for (ll i = 1; i < m; i++) {
        cnt += 2 * sqrtfl(m * m - i * i);
    }
    return 2 * cnt > s;
}

int main() {
    FIN;

    cin >> s;

    ld l = 0, r = sqrtl(s) * 1.5 + 500;
    while (r - l > EPS) {
        ld m = (l + r) / 2;
        if (can(m))
            r = m;
        else
            l = m;
    }

    cout << fixed << setprecision(16) << (r + l) / 2 << '\n';

    return 0;
}
