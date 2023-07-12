// https://codeforces.com/group/4zVk9dZl6Q/contest/391178/problem/L
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define str string
#define fore(i, a, b) for (ll i = a, ggdem = b; i < ggdem; ++i)
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(), x.end()
#define mset(a, v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll solve(ll t, ll r, vector<ll> ws) {
  if (r > t) {
    return -1;
  }

  sort(ALL(ws));

  vector<ll> on(301, 0);
  set<ll> turnon;

  for (ll w : ws) {
    for (ll k = w - 1; on[w] < r; k--) {
      if (w - k > t) {
        return -1;
      }
      if (turnon.find(k) == turnon.end()) {
        fore(j, 0, t) {
          if (k + 1 + j >= 0 && k + 1 + j <= 300) {
            on[k + 1 + j]++;
          }
          turnon.insert(k);
        }
      }
    }
  }

  return turnon.size();
}

int main() {
  FIN;
  ull m;
  ll t, r;
  cin >> m >> t >> r;
  vector<ll> ws(m);
  fore(i, 0, m) {
    cin >> ws[i];
  }

  cout << solve(t, r, ws) << '\n';

  return 0;
}