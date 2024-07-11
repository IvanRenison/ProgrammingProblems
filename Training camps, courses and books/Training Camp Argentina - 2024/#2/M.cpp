// https://codeforces.com/group/5GNF7zti59/contest/535183/problem/M
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

optional<vi> solve(ll n, const vector<vi>& fss) {
  ll m = fss.size();

  vector<vi> apps(n);
  vector<vi> uapps(n);
  fore(j, 0, m) {
    for (auto f : fss[j]) {
      apps[f].push_back(j);
    }
    if (fss[j].size() == 1)  {
      uapps[fss[j][0]].push_back(j);
    }
  }

  vi ans(m, -1);

  fore(f, 0, n) {
    if (uapps[f].size() > (m + 1) / 2) {
      return {};
    }

    ll count = 0;
    for (ll j : uapps[f]) {
      if (ans[j] == -1) {
        ans[j] = f;
        count++;
      }
    }

    for (ll j : apps[f]) {
      if (count + 1 > (m + 1) / 2) {
        break;
      }
      if (ans[j] == -1) {
        ans[j] = f;
        count++;
      }
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll t;
  cin >> t;
  while (t--) {
    ll n, m;
    cin >> n >> m;
    vector<vi> fss(m);
    for (vi& fs : fss) {
      ll k;
      cin >> k;
      fs = vi(k);
      for (ll& f : fs) {
        cin >> f;
        f--;
      }
    }

    auto ans = solve(n, fss);
    if (ans) {
      cout << "YES\n";
      for (ll f : *ans) {
        cout << f  +1 << ' ' ;;
      }
      cout << '\n';
    } else {
      cout << "NO\n";
    }
  }
}