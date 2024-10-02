// https://codeforces.com/gym/104875
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(), x.end()
#define SZ(x) ll(x.size())
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define mset(a, v) memset((a), (v), sizeof(a))
#define pb push_back
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

ll h, r, da, dw;

ld gss(ld a, ld b, ld (*f)(ld)) {
    ld r = (sqrt(5) - 1) / 2, eps = 1e-7;
    ld x1 = b - r * (b - a), x2 = a + r * (b - a);
    ld f1 = f(x1), f2 = f(x2);
    while (b - a > eps)
        if (f1 < f2) {
            b = x2;
            x2 = x1;
            f2 = f1;
            x1 = b - r * (b - a);
            f1 = f(x1);
        } else {
            a = x1;
            x1 = x2;
            f1 = f2;
            x2 = a + r * (b - a);
            f2 = f(x2);
        }
    return a;
}

ld func(ld x) {
    ld M = x * dw + (h - x) * da, wcm = x / 2, acm = x + (h - x) / 2;
    return (wcm * x * dw + acm * (h - x) * da) / M;
}

int main() {
    FIN;
    cin >> h >> r >> da >> dw;

    cout << fixed << setprecision(16) << gss(0, h, func) << "\n";

    return 0;
}
