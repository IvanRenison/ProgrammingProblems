// https://codeforces.com/gym/104114/problem/A
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)
#define SZ(x) (ll)(x).size()
#define mset(a, v) memset((a), (v), sizeof(a))
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s, t;
    cin >> s >> t;
    ll n = s.size(), m = t.size();

    vector<vi> apps(26);
    fore(i, 0, n) {
        apps[s[i] - 'a'].push_back(i);
    }

    ll i = 0;
    ll ans = 1;
    for (char c : t) {
        if (i == n) {
            ans++;
            i = 0;
        }
        auto it = lower_bound(ALL(apps[c - 'a']), i);
        if (it == apps[c - 'a'].end()) {
            i = apps[c - 'a'][0] + 1;
            ans++;
        } else {
            i = *it + 1;
        }
    }

    cout << ans << '\n';

}
