// https://codeforces.com/gym/104505/problem/G
#include "bits/stdc++.h"
#define fst first
#define snd second
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll(x.size()))
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    ll n, f;
    cin >> n >> f;
    vector<ii> a(n);
    fore(i, 0, n) cin >> a[i].fst >> a[i].snd;
    for (auto [x, y] : a) {
        if (f >= max(x, y))
            f += max(x, y);
        else if (f >= min(x, y))
            f += min(x, y);
        else {
            cout << "N\n";
            return 0;
        }
    }
    cout << "S\n";

    return 0;
}
