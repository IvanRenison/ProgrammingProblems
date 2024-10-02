// https://codeforces.com/gym/104114/problem/E
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

vii solve(vi& ps) {
    ll n = ps.size();

    array<vi, 3> game = {ps, {}, {}};

    vii ans;

    auto move = [&](ll a, ll b) {
        assert(a != b);
        assert(a < 3 && b < 3);
        assert(!game[a].empty());
        ans.push_back({a, b});
        game[b].push_back(game[a].back());
        game[a].pop_back();
    };

    fore(i, 0, n) {
        move(0, 1);
        ll count = 0;
        while (!game[2].empty() && game[2].back() < game[1].back()) {
            move(2, 0);
            count++;
        }
        move(1, 2);
        fore(j, 0, count) {
            move(0, 2);
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;
    vi ps(n);
    for (ll& p : ps) {
        cin >> p;
        p--;
    }
    vii ans = solve(ps);
    cout << ans.size() << '\n';
    for (auto [a, b] : ans) {
        cout << a + 1 << ' ' << b + 1 << '\n';
    }
}
