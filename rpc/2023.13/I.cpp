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


int main() {
    FIN;

    ll n, d;
    cin >> n >> d;

    ll last = n % 10;
    if (last < d)
        prnt(n + d - last);
    else
        prnt(n - last + 10 + d);

    return 0;
}
