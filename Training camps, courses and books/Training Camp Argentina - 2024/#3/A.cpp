// https://codeforces.com/group/5GNF7zti59/contest/535420/problem/A
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(), x.end()
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

ll solve_for(vii& g) {
  ll n = SZ(g);
  map<ll, ll> cnt;
  for(auto &[ry, vy] : g) {
    cnt[vy]++;
  }
  ll res = n * (n - 1);
  for(auto &[k, v] : cnt) {
    res -= v * (v - 1);
  }
  assert(res % 2 == 0);
  return res;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  ll n, a, b;
  cin >> n >> a >> b;
  vector<array<ll, 4>> in(n);
  fore(i, 0, n) {
    ll x, vx, vy;
    cin >> x >> vx >> vy;
    in[i] = {x, a * x, vx, vy};
  }

  map<ll, vector<ii>> by_vx;
  array<array<ll, 2>, 2> mat = {{{a, -1}, {1, a}}};
  for (auto &[rx, ry, vx, vy] : in) {
    ll rxn = mat[0][0]*rx + mat[0][1]*ry;
    ll ryn = mat[1][0]*rx + mat[1][1]*ry;
    assert(rxn == 0);
    ll vxn = mat[0][0]*vx + mat[0][1]*vy;
    ll vyn = mat[1][0]*vx + mat[1][1]*vy;
    by_vx[vxn].pb({ryn, vyn});
  }

  ll ans = 0;
  for (auto &[vx, g] : by_vx) {
    ans += solve_for(g);
  }

  cout << ans << "\n";
}