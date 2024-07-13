// https://codeforces.com/group/5GNF7zti59/contest/535722/problem/L
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  ll a, b, c, x, y, z;
  cin >> a >> b >> c >> x >> y >> z;
  ll d = a - x, e = b - y, f = c - z;
  if (d > 0) {
    d /= 2;
  }
  if (e > 0) {
    e /= 2;
  }
  if (f > 0) {
    f /= 2;
  }

  bool ans = d + e + f >= 0;

  cout << (ans ? "Yes" : "No") << '\n';
}
