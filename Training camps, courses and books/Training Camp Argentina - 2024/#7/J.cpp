// https://codeforces.com/group/5GNF7zti59/contest/534927/problem/J
#include<bits/stdc++.h>
#define fst first
#define snd second
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i =a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef long double ld;
typedef vector<ld> vd;

pair<ll, vi> solve(ll h, ll g, vi& as) {
  ll n = as.size();
  fore(i, 0, 2*n) {
    as.push_back(0);
  }
  ll diff = (1 << h) - (1 << g);

  vi depth(n + 1);

  vi ans_v;

  function<bool(ll)> can = [&](ll i) -> bool {
    if (i >= (1 << g)) {
      return as[i-1] > 0;
    }
    ll j = as[2*i - 1] > as[2*i] ? 2*i : 2*i+1;
    return can(j);
  };

  function<void(ll)> op = [&](ll i) {
    if (as[i-1] == 0) {
      return;
    }
    while (as[i-1] > 0 && can(i)) {
      ans_v.push_back(i);
      for (ll k = i; as[k - 1] > 0;) {
        ll j = as[2*k - 1] > as[2*k] ? 2*k : 2*k+1;
        as[k - 1] = as[j - 1];
        k = j;
      }
      if (ans_v.size() >= diff) {
        return;
      }
    }

    op(2*i);
    if (ans_v.size() >= diff) {
      return;
    }
    op(2*i+1);
  };

  op(1);

  ll sum = accumulate(ALL(as), 0ll);

  return {sum, ans_v};
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll t;
  cin >> t;
  while (t--) {
    ll h, g;
    cin >> h >> g;
    ll n = (1 << h) - 1;
    vi as(n);
    for (ll& a : as) {
      cin >> a;
    }

    auto [ans, v] = solve(h, g, as);
    cout << ans << '\n';
    for (ll a : v) {
      cout << a << ' ';
    }
    cout << '\n';
  }
}