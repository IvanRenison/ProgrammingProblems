// https://codeforces.com/gym/105544
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define ALL(x) x.begin(),x.end()
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    reverse(ALL(s));
    while (s.size() % 3 != 0) {
      s += "0";
    }
    ll n = s.size();
    ll ans = 0;
    for (ll i = 0; i < n; i += 3) {
      ll x = 0;
      x += (s[i] - '0');
      x += (s[i + 1] - '0') * 10;
      x += (s[i + 2] - '0') * 100;
      if ((i / 3) % 2 == 0) {
        ans += x;
      } else {
        ans -= x;
      }
    }

    cout << abs(ans) << ' ';
    cout << (abs(ans) % 13 == 0 ? "YES" : "NO") << '\n';


  }

}