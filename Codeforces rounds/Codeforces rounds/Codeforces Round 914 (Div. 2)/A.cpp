// https://codeforces.com/contest/1904/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl


ull solve1(ll a, ll b, ll xk, ll yk, ll xq, ll yq) {

  set<pair<ll, ll>> kpoints = {
    {xk + a, yk + b},
    {xk + a, yk - b},
    {xk - a, yk + b},
    {xk - a, yk - b},
    {xk + b, yk + a},
    {xk + b, yk - a},
    {xk - b, yk + a},
    {xk - b, yk - a}
  };

  set<pair<ll, ll>> qpoints = {
    {xq + a, yq + b},
    {xq + a, yq - b},
    {xq - a, yq + b},
    {xq - a, yq - b},
    {xq + b, yq + a},
    {xq + b, yq - a},
    {xq - b, yq + a},
    {xq - b, yq - a}
  };

  ll ans = 0;
  for (auto [x, y] : kpoints) {
    for (auto [x_, y_] : qpoints) {
      if (x == x_ && y == y_) {
        ans++;
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ll a, b;
    ll xk, yk, xq, yq;
    cin >> a >> b >> xk >> yk >> xq >> yq;

    auto ans = solve1(a, b, xk, yk, xq, yq);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
