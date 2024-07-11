// https://codeforces.com/group/5GNF7zti59/contest/535183/problem/L
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

vi solve(const vi& as) {
  ll n = as.size();

  vi counter(30);
  for (ll a : as) {
    fore(i, 0, 30) {
      if (a & (1 << i)) {
        counter[i]++;
      }
    }
  }

  ll g = counter[0];
  fore(i, 1, 30) {
      g = gcd(g, counter[i]);
  }

    vi ans;
  fore(i, 1, n + 1) {
    if (g % i == 0) {
      ans.push_back(i);
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    vi as(n);
    for (ll& a : as) {
      cin >> a;
    }

    vi ans = solve(as);
    for (ll a : ans) {
      cout << a << ' ';
    }
    cout << '\n';
  }

}