// https://redprogramacioncompetitiva.com/contests/2023/13
#ifdef ONLINE_JUDGE
#pragma GCC optimize("O2,unroll-loops,modulo-sched,modulo-sched-allow-regmoves,gcse-sm,gcse-las,ipa-pta,tree-loop-im,tree-loop-ivcanon,ivopts,tree-vectorize")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,tune=native")
#endif
#include "bits/stdc++.h"
// #include "ext/pb_ds/assoc_container.hpp"
// #include "ext/pb_ds/tree_policy.hpp"
// #include "ext/rope"
// using namespace __gnu_pbds;
using namespace __gnu_cxx;
using namespace std;
typedef long long ll;
typedef long double ld;
// typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fori(i, a, b) for (ll i = a; i < (ll)(b); i++)
#define rof(i, a, b) for (ll i = a - 1; i >= b; i--)
#define fore(xs, x) for (auto& x : xs)
#define forp(xs, a, b) for (auto& [a, b] : xs)
#define prnt(x) cout << (x) << "\n"
#define all(x) begin(x), end(x)
#define SZ(x) (ll)(x.size())
#define ii pair<ll, ll>
#define vii vector<ii>
#define vvii vector<vii>
#define vi vector<ll>
#define vvi vector<vi>
#define vd vector<ld>
#define vvd vector<vd>
#define vc vector<char>
#define vvc vector<vector<char>>
constexpr array<ii, 4> dir = {mp(1, 0), mp(0, 1), mp(-1, 0), mp(0, -1)};
constexpr ll INF = 1e18;
constexpr ld EPS = 1e-7;
constexpr ll MOD = 1e9 + 7;

ll euclid(ll a, ll b, ll& x, ll& y) {
    if (!b) return x = 1, y = 0, a;
    ll d = euclid(b, a % b, y, x);
    return y -= a / b * x, d;
}

struct Mod {
    ll x;
    Mod(ll xx) : x(xx) {}
    Mod() : x(0) {}
    Mod operator+(Mod b) { return Mod((x + b.x) % MOD); }
    Mod operator-(Mod b) { return Mod((x - b.x + MOD) % MOD); }
    Mod operator*(Mod b) { return Mod((x * b.x) % MOD); }
    Mod operator/(Mod b) { return *this * invert(b); }
    Mod invert(Mod a) {
        ll _x, y, g = euclid(a.x, MOD, _x, y);
        assert(g == 1);
        return Mod((_x + MOD) % MOD);
    }
    Mod operator^(ll e) {
        if (!e) return Mod(1);
        Mod r = *this ^ (e / 2);
        r = r * r;
        return e & 1 ? *this * r : r;
    }
};

map<ll, Mod> d_chance;
void init_chance() {
    fori(a1, 1, 7)
        fori(a2, 1, 7) {
        ll a = a1 + a2;

        fori(b1, 1, 7)
            fori(b2, 1, 7) {
            ll b = b1 + b2;

            ll d = a - b;
            d_chance[d] = d_chance[d] + Mod(1) / Mod(6 * 6 * 6 * 6);
        }
    }
}

array<Mod, 3> play(Mod old_m) {
    Mod a = 0, b = 0, m = 0;
    forp(d_chance, d, chance) {
        if (d <= 0) {
            b = b + chance * abs(d);
            m = m + chance * 1;
        } else {
            Mod change_chance = Mod(d) / Mod(10);
            a = a + chance * change_chance * 0;
            m = m + chance * change_chance * d;

            Mod add_chance = Mod(10 - d) / Mod(10);
            a = a + chance * add_chance * (old_m * Mod(d));
            m = m + chance * add_chance * 1;
        }
    }

    return {a, b, m};
}

int main() {
    FIN;

    ll n;
    cin >> n;
    init_chance();

    Mod a = 0, b = 0, m = 1;
    fori(i, 0, n) {
        array<Mod, 3> res = play(m);
        a = a + res[0], b = b + res[1], m = res[2];
    }

    cout << a.x << " " << b.x << "\n";

    return 0;
}
