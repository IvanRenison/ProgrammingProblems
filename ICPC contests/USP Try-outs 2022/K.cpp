// https://codeforces.com/gym/103934/problem/K
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

ll solve(ll B, viiii& XYTVs) {
    ll N = XYTVs.size();


    vi max_pays;

    fore(i, 0, N) {
        auto [X, Y, T, V] = XYTVs[i];
        ll wolk_time = Y - X;
        if (wolk_time > T) {
            // train_time = Y / B
            if (Y <= T * B) { // train_time <= T
                max_pays.push_back(V);
            }
        }
    }

    sort(ALL(max_pays));

    ll win = 0;
    ll ans = 0;
    ll go = max_pays.size();
    for (ll v : max_pays) {
        ll this_win = v * go;
        if (this_win > win) {
            win = this_win;
            ans = v;
        }
        go--;
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll N, B;
    cin >> N >> B;
    viiii XYTVs(N);
    for (auto& [X, Y, T, V] : XYTVs) {
        cin >> X >> Y >> T >> V;

    }

    cout << solve(B, XYTVs) << '\n';
}
