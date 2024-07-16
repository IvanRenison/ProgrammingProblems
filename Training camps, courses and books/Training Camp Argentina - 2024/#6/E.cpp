// https://codeforces.com/group/5GNF7zti59/contest/534709/problem/E
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((ll)x.size())
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
using namespace std;
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  ll n;
  cin >> n;
  vi a(n);
  fore(i, 0, n) cin >> a[i];
  sort(ALL(a));
  auto in = [&](ll x) {
    auto it = lower_bound(ALL(a), x);
    if (it == end(a))
      return false;
    return *it == x;
  };
  ll maxa = a.back();

  ll res = 1;
  vi ans = {a[0]};
  fore(i, 0, n) {
    ll off = a[i];
    for (ll j = 1; j <= maxa - off; j <<= 1) {
      if (in(j + off)) {
        if (in(2 * j + off)) {
          res = 3;
          ans = {0 + off, j + off, 2 * j + off};
        } else if (res < 2) {
          res = 2;
          ans = {0 + off, j + off};
        }
      }
    }
  }

  cout << res << "\n";
  fore(i, 0, res) {
    cout << ans[i] << " ";
  }
  cout << "\n";
}