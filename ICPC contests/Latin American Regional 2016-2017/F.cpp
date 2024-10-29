// https://matcomgrader.com/problem/9284/farm-robot
#include "bits/stdc++.h"
#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; ++i)
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((ll)x.size())
#define mset(a, v) memset((a), (v), sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    ll n, c, s;
    cin >> n >> c >> s;
    s--;

    ll ans = s == 0, cu = 0;
    while (c--) {
        ll ci;
        cin >> ci;
        cu = (cu + ci + n) % n;
        ans += cu == s;
    }
    cout << ans << "\n";
}
