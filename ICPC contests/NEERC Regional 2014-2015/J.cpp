// https://codeforces.com/gym/100553
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

vi solve(string& s) {
  ll n = s.size(), len = n;
  assert(n != 10);
  if (n > 10) {
    assert(n % 2 == 1);
    n = (n + 9) / 2;
  }

  function<optional<vi>(ll, ll)> f = [&](ll i, ll x) -> optional<vi> {
    if (i == len) {
      return {vi{}};
    }
    if (s[i] == '0') {
      return {};
    }
    ll d = s[i] - '0';
    if (!(x & (1ll << d))) {
      auto rec = f(i + 1, x | (1ll << d));
      if (rec.has_value()) {
        rec->push_back(d);
        return rec;
      }
    }

    if (i + 1 == len) {
      return {};
    }

    d = (s[i] - '0') * 10 + s[i + 1] - '0';

    if (x & (1ll << d) || d > n) {
      return {};
    }

    auto rec = f(i + 2, x | (1ll << d));
    if (rec.has_value()) {
      rec->push_back(d);
    }
    return rec;
  };

  vi ans = *f(0, 0);
  reverse(ALL(ans));
  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("joke.in", "r", stdin);
  freopen("joke.out", "w", stdout);
#endif

  string s;
  cin >> s;
  for (ll x : solve(s)) {
    cout << x << ' ';
  }
  cout << '\n';

}