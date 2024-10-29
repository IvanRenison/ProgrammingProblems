// https://matcomgrader.com/problem/9286/hotel-rewards
#include "bits/stdc++.h"
#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((ll)x.size())
#define mset(a, v) memset((a), (v), sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

struct TreeSum {
    typedef ll T;
    static constexpr T neut = 0;
    T f(T a, T b) { return a + b; }

    vector<T> s; ll n;
    TreeSum(ll n = 0, T def = neut) : s(2*n, def), n(n) {}
    void upd(ll pos, T val) {
        for (s[pos += n] = val; pos /= 2;) {
            s[pos] = f(s[pos*2], s[pos * 2 + 1]);
        }
    }
    T query(ll b, ll e) {
        T ra = neut, rb = neut;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};
struct TreeMax {
    typedef ii T;
    T neut = {-1,-1};
    T f(T a, T b) { return max(a,b); }

    vector<T> s; ll n;
    TreeMax(ll n = 0) : s(2*n, neut), n(n) {}
    void upd(ll pos, T val) {
        for (s[pos += n] = val; pos /= 2;) {
            s[pos] = f(s[pos*2], s[pos * 2 + 1]);
        }
    }
    T query(ll b, ll e) {
        T ra = neut, rb = neut;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

ll solve(ll K, vi& Ps) {
    ll N = Ps.size();

    TreeSum activeSum(N);
    TreeMax activeMax(N);

    fore(i, 0, N) {
        activeSum.upd(i, 1);
        activeMax.upd(i, {1, i});
    }

    vi is(N);
    iota(ALL(is), 0ll);

    sort(ALL(is), [&](ll i, ll j) { return Ps[i] > Ps[j]; });

    ll free = N / (K + 1);

    ll ans = 0;

    fore(k, 0, N) {
        // cerr << "k = " << k << endl;
        ll i = is[k];
        // cerr << "i = " << i << endl;

        ll i_active = activeSum.query(i, i + 1);
        ll sum = activeSum.query(0, i);
        // cerr << "i_active = " << i_active << endl;
        // cerr << "sum = " << sum << endl;
        if (sum >= K + !i_active) {
            fore(_, 0, K + !i_active) {
                auto vj = activeMax.query(0, i);
                ll v = vj.fst, j = vj.snd;
                assert(v == 1);
                ans += Ps[j];
                activeSum.upd(j, 0);
                activeMax.upd(j, {0, j});
            }
            if (i_active) {
                activeSum.upd(i, 0);
                activeMax.upd(i, {0,i});
            } else {
                ans -= Ps[i];
            }
        }
    }

    fore(i, 0, N) {
        ll i_active = activeSum.query(i, i + 1);
        if (i_active) {
            ans += Ps[i];
        }
    }

    return ans;
}


int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    ll N, K;
    cin >> N >> K;
    vi Ps(N);
    for (ll& P : Ps) {
        cin >> P;
    }
    ll ans = solve(K, Ps);
    cout << ans << '\n';

}
/*
6 2
10 3 12 15 12 18
k = 0
i = 5
i_active = 1
sum = 5
k = 1
i = 3
i_active = 0
sum = 3
52
*/
