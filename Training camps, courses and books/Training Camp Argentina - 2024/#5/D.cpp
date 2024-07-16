// https://codeforces.com/group/5GNF7zti59/contest/536252/problem/D
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

bool force(ll a, ll b, ll c) {
  vi as = {a, b, c};
  for (ll i = 1; ; i++) {
    if (i % 7 != 0) {
      as[2]--;
      sort(ALL(as));
      if (as[0] == 0) {
        return false;
      }
    } else {
      as[0]--, as[1]--, as[2]--;
      if (as[2] == 0) {
        return true;
      }
    }
  }
}

bool solve(ll a, ll b, ll c) {
  if (a == b && b == c) {
    return a % 3 == 0;
  }

  ll x = (c - a + b - a) / 6;
  ll y = (c - a + b - a) % 6;

  if (a - x < 0) {
    return false;
  }
  if (y != 0 && y != 3) {
    return false;
  }

  if (a - x == 0) {
    return y == 0;
  }

  if (y == 0) {
    return (a - x) % 3 == 0 && (a - x) > 1;
  } else {
    return (a - x) % 3 == 2;
  }

}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll t;
  cin >> t;
  while (t--) {
    vi as(3);
    for (ll& a : as) {
      cin >> a;
    }
    sort(ALL(as));

    bool ans = solve(as[0], as[1], as[2]);
    cout << (ans ? "Yes" : "No") << '\n';
  }

/*   fore(_, 0, 10000) {
    ll a = rand() % 10 + 1, b = rand() % 10 + 1, c = rand() % 10;

    bool ans = solve(a, b, c);
    bool ansf = force(a, b, c);
    if (ans != ansf) {
      cerr << a << ' ' << b << ' ' << c << '\n';
      cerr << ans << endl;
      return 1;
    }
  } */

}
