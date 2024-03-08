// https://codeforces.com/contest/1250/problem/F
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
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    ll n;
    cin >> n;

    ll m = 1e18;
    fore(i, 1, n + 1) {
        if (n % i == 0)
            m = min(m, 2 * i + 2 * (n / i));
    }
    cout << m << "\n";

    return 0;
}
