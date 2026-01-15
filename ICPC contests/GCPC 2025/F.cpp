// https://codeforces.com/gym/106129/problem/F
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, mpisp = b; i < mpisp; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef tuple<ll, ll, ll> iii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef long double ld;


ll maxr = 2501;
vector<bool> isPrime(maxr, true);

void init() {
  isPrime[0] = isPrime[1] = false;

  fore(i, 2, maxr) {
    if (isPrime[i]) {
      for (ll j = 2 * i; j < maxr; j += i) {
        isPrime[j] = false;
      }
    }
  }

}


ll solve(vector<string>& grid) {
  ll h = grid.size(), w = grid[0].size();

  auto can = [&](ll l) -> bool {
    if (l == 1) {
      return true;
    }
    if (l > min(h, w)) {
      return false;
    }
    vector<vector<bool>> used(h, vector<bool>(w, false));

    fore(i, 0, h) fore(j, 0, w) {
      if (!used[i][j] && grid[i][j] == '#') {
        if (i + l > h || j + l > w) {
          return false;
        }
        fore(i2, i, i + l) fore(j2, j, j + l) {
          if (grid[i2][j2] != '#' || used[i2][j2]) {
            return false;
          }
          used[i2][j2] = true;
        }
      }
    }

    return true;
  };

/*   for (ll p = min(w, h) + 1; p--;) {
    if (can(p)) {
      return p;
    }
  } */

  ll ans = 1;
  fore(p, 2, min(w, h) + 2) if (isPrime[p]) {
    ll q = 1;
    while (can(q * p)) {
      //cout << p << '\n';
      q *= p;
    }
    ans *= q;
  }

  return ans;
}


int main() {
	//cin.tie(0)->sync_with_stdio(0);
  //freopen("F.in", "r", stdin);

  init();

  ll h, w;
  cin >> h >> w;
  vector<string> grid(h);
  for (string& row : grid) {
    cin >> row;
  }

  auto ans = solve(grid);
  cout << ans << '\n';

/*   cout << 2500 << ' ' << 2500 << '\n';
  fore(i, 0, 2500) {
    fore(j, 0, 2500) {
      cout << '#';
    }
    cout << '\n';
  } */

}
