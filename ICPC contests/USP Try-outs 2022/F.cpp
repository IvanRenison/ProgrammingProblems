// https://codeforces.com/gym/103934/problem/F
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, efunca = b; i < efunca; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<pair<ll, ll>> vii;
typedef tuple<ll,ll,ll,ll> iiii;
typedef vector<iiii> viiii;
typedef long double ld;

ll solve(ll N) {
    if (N == 1) {
        return 0;
    }

    if (N % 2 == 1) {
        N++;
    }

    ll rec = solve(N / 2);

    ll ans = N - 2 - 2 * rec;

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll N;
    cin >> N;
    cout << solve(N) + 1 << '\n';
}
