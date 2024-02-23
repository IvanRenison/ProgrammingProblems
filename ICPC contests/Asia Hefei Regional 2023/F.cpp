// https://codeforces.com/gym/104857/problem/F
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define mset(a, v) memset((a), (v), sizeof(a))
#define SZ(x) (ll(x.size()))
#define ALL(x) x.begin(), x.end()
#define FIN ios::sync_with_stdio(0), cout.tie(0), cin.tie(0)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

int main() {
    FIN;

    ll n;
    cin >> n;
    map<string, ll> m;
    fore(i, 0, n) {
        string s;
        cin >> s;
        m[s]++;
    }

    ll ma = 0;
    string ans;
    for (auto it = m.begin(); it != m.end(); it++) {
        if (it->snd > ma) {
            ma = it->snd;
            ans = it->fst;
        }
    }

    if (ma * 2 > n) {
        cout << ans << "\n";
    } else {
        cout << "uh-oh\n";
    }

    return 0;
}