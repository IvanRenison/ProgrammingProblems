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

typedef bitset<1000> B;

ll toNum(char c) {
  if ('0' <= c && c <= '9') {
    return c - '0';
  } else {
    return 10 + c - 'a';
  }
}

vi solve(ll m, vi& as, vector<B>& values, vi& us) {
  ll f = as.size(), n = values.size(), q = us.size();

  vi ans;

  fore(i, 0, n) {
    bool found = false;
    for (ll u : us) {
      bool valid = true;
      for (ll a : as) {
        if (!(values[i][(u * a) % m])) {
          valid = false;
          break;
        }
      }
      if (valid) {
        found = true;
        break;
      }
    }
    if (found) {
      ans.push_back(i);
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("filter.in", "r", stdin);
  freopen("filter.out", "w", stdout);
#endif

  ll m, f;
  cin >> m >> f;
  vi as(f);
  for (ll& a : as) {
    cin >> a;
  }
  ll n;
  cin >> n;
  vector<B> values(n);
  for (B& val : values) {
    string s;
    cin >> s;
    ll i = 0;
    for (char c : s) {
      ll d = toNum(c);
      fore(j, 0, 4) if (d & (1 << j)) {
        val[i + j] = 1;
      }
      i += 4;
    }
  }
  ll q;
  cin >> q;
  vi us(q);
  for (ll& u : us) {
    cin >> u;
  }
  vi ans = solve(m, as, values, us);
  cout << ans.size();
  for (ll a : ans) {
    cout << ' ' << a;
  }
  cout << '\n';

}