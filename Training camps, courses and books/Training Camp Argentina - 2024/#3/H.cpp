// https://codeforces.com/group/5GNF7zti59/contest/535420/problem/H
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;

char query(ll x, ll y) {
  cout << "? " << x << ' ' << y << endl;
  char c;
  cin >> c;
  return c;
}

bool in(ll x, ll y) {
  char c = query(x, y);
  return c == 'x';
}

ll solve() {
  ll i = 0;
  while (true) {
    if (in(i == 0 ? 0 : 1ll << (i - 1), 1ll << i)) {
      break;
    }
    i++;
  }

  if (i == 0) {
    return 1;
  }

  ll l = 1ll << (i - 1), r = (1ll << i) + 1;
  while (l + 1 < r) {
    ll m = (l + r) / 2;
    if (in(1ll << (i - 1), m)) {
      r = m;
    } else {
      l = m;
    }
  }

  return l + 1;
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);

  while (true) {
    string s;
    cin >> s;
    if (s == "start") {
      ll a = solve();
      cout << "! " << a << endl;
    } else {
      break;
    }
  }
}
