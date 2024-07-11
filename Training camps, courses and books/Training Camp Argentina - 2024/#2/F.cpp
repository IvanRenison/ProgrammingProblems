// https://codeforces.com/group/5GNF7zti59/contest/535183/problem/F
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((ll)x.size())
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

ii solve(vi &a, ll k) {
  if (!SZ(a)) return {0, 0};
  sort(ALL(a));
  ll largest = a[SZ(a) - 1];
  ll ans = 0;
  while(SZ(a)) {
    ll dist = a.back();
    ans += 2 * dist;
    fore(i, 0, min(k, SZ(a))) a.pop_back();
  }
  return {ans - largest, largest};
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  ll t;
  cin >> t;
  while (t--) {
    ll n, k;
    cin >> n >> k;
    vi pos, neg;
    fore(i, 0, n) {
      ll x; cin >> x;
      if (x > 0) pos.pb(x);
      else if (x < 0) neg.pb(-x);
    }

    auto [ans1, w1] = solve(pos, k);
    auto [ans2, w2] = solve(neg, k);
    ll ans = ans1 + ans2;
    ans += min(w1, w2);

    cout << ans << "\n";
  }
}