// https://codeforces.com/group/5GNF7zti59/contest/536252/problem/K
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(X) X.begin(),X.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef long double ld;

void solve() {
  ll n; cin >> n;

  auto q1 = [](ll l, ll r) {
    cout << 1 << " " << r - l << " " << 1 << " ";
    fore(i, l, r) {
      cout << i + 1 << " ";
    }
    cout << endl;
    ll dist;
    cin >> dist;
    if (dist == -1) exit(0);
    return dist;
  };

  ll bfs1 = q1(1, n);
  ll l = 1, r = n;
  while(r - l > 1) {
    ll mid = (l + r) / 2;
    // cerr << "l r: " << l+1 << " " << r+1 << " " << mid+1 << endl;
    ll first = q1(l, mid);
    if (first == bfs1) {
      r = mid;
    } else {
      l = mid;
    }
  }
  ll targ = l;
  cout << 1 << " " << n - 1 << " " << l + 1 << " ";
  fore(i, 0, n) if (i != targ) {
    cout << i + 1 << " ";
  }
  cout << endl;
  ll res;
   cin >> res;
   if (res == -1) exit(0);
   cout << "-1 " << res << endl;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll t; cin >> t;
  while(t--) {
    solve();
  }
}