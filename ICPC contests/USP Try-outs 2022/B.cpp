// https://codeforces.com/gym/103934/problem/B
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


pair<vii, vii> simComp(ll X, ll C, vi& ds) {
    sort(ALL(ds));
    vii ans;
    vii ans2;
    ll bord_start = 0, pass = 0;
    bool in_ans = false;
    for (ll d : ds) {
        if (d - bord_start > X) {
            if (in_ans) {
                ans.back().second = bord_start + X;
                in_ans = false;
            } else {
                ans.push_back({bord_start + X, bord_start + X});
            }
            bord_start += X;
            pass = 0;
            if (bord_start + X < d) {
                ll diff = d - bord_start;
                diff = (diff / X) * X;
                ans2.push_back({bord_start, bord_start + diff});
                bord_start += diff;
            }
        }
        pass++;
        if (pass == C) {
            ans.back().second = d;
            bord_start = d;
            pass = 0;
            in_ans = false;
        } else if (pass == C - 1) {
            ans.push_back({d, -1});
            in_ans = true;
        }
    }
    if (in_ans) {
        ans.back().second = bord_start + X;
    } else if (pass > 0) {
        ans.push_back({bord_start + X, bord_start + X});
    }
    ans2.push_back({ans.back().second, ans.back().second + X * (ll)(1e9 + 5)});
    return {ans, ans2};
}

ll solve(ll C, ll X, ll T, ll t0, ll t1, ll t2, vii& dcs) {
    ll N = dcs.size();


    if (C == 1 || X == 1) {
        return max({T - t0, T - t1, T - t2});
    }

    vi ts = {t0, t1, t2};
    vector<vi> dss(3);
    for (auto [d, c] : dcs) {
        dss[c].push_back(d);
    }

    ll ans = 0;
    fore(i, 0, 3) {
        auto [trips, trips_ranges] = simComp(X, C, dss[i]);

        ll t = T - ts[i];

        if (t == 0) {
            continue;
        }

        for (auto [l, r] : trips) {
            if (l <= t) {
                ll this_ans = min(r, t);
                assert(this_ans + ts[i] <= T);
                ans = max(ans, this_ans);
            }
        }

        for (auto [l, r] : trips_ranges) {
            if (l <= t) {
                ll diff = min(t, r) - l;
                ll after = (diff / X) * X;
                ll this_ans = l + after;
                assert(this_ans + ts[i] <= T);
                ans = max(ans, this_ans);
            }
        }

    }

    return ans;


}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll C, X, T, N;
    cin >> C >> X >> T >> N;
    ll t0, t1, t2;
    cin >> t0 >> t1 >> t2;
    vii dcs(N);
    for (auto& [d, c] : dcs) {
        cin >> d >> c;
        c--;
    }
    cout << solve(C, X, T, t0, t1, t2, dcs) << '\n';

}
