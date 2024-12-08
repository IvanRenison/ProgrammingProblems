// https://codeforces.com/gym/101492/problem/H
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, carranza = b; i < carranza; i++)
#define ALL(x) x.beind(), x.end()
#define SZ(x) (ll)(x).size()
#define mset(a, v) memset(a, v, sizeof(a))
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef long double ld;


vector<pair<char, ll>> solve(ll x, ll y, char dir) {

  vector<pair<char, ll>> ans;

  if (x == 0 && y == 0) {
    return ans;
  }

  if (x == 0) {
    if (y > 0) {
      if (dir == 'E') {
        ans.push_back({'D', -1}), dir = 'S';
      }
      if (dir == 'S') {
        ans.push_back({'D', -1}), dir = 'O';
      }
      if (dir == 'O') {
        ans.push_back({'D', -1}), dir = 'N';
      }
      ans.push_back({'A', y});
    } else {
      if (dir == 'O') {
        ans.push_back({'D', -1}), dir = 'N';
      }
      if (dir == 'N') {
        ans.push_back({'D', -1}), dir = 'E';
      }
      if (dir == 'E') {
        ans.push_back({'D', -1}), dir = 'S';
      }
      ans.push_back({'A', -y});
    }
  } else if (y == 0) {
    if (x > 0) {
      if (dir == 'S') {
        ans.push_back({'D', -1}), dir = 'O';
      }
      if (dir == 'O') {
        ans.push_back({'D', -1}), dir = 'N';
      }
      if (dir == 'N') {
        ans.push_back({'D', -1}), dir = 'E';
      }
      ans.push_back({'A', x});
    } else {
      if (dir == 'N') {
        ans.push_back({'D', -1}), dir = 'E';
      }
      if (dir == 'E') {
        ans.push_back({'D', -1}), dir = 'S';
      }
      if (dir == 'S') {
        ans.push_back({'D', -1}), dir = 'O';
      }
      ans.push_back({'A', -x});
    }
  } else if (x > 0 && y > 0) {
    if (dir == 'E') {
      ans.push_back({'A', x});
      ans.push_back({'D', -1}), dir = 'S';
      ans.push_back({'D', -1}), dir = 'O';
      ans.push_back({'D', -1}), dir = 'N';
      ans.push_back({'A', y});
    } else {
      if (dir == 'S') {
        ans.push_back({'D', -1}), dir = 'O';
      }
      if (dir == 'O') {
        ans.push_back({'D', -1}), dir = 'N';
      }
      ans.push_back({'A', y});
      ans.push_back({'D', -1}), dir = 'E';
      ans.push_back({'A', x});
    }
  } else if (x > 0 && y < 0) {
    if (dir == 'S') {
      ans.push_back({'A', -y});
      ans.push_back({'D', -1}), dir = 'O';
      ans.push_back({'D', -1}), dir = 'N';
      ans.push_back({'D', -1}), dir = 'E';
      ans.push_back({'A', x});
    } else {
      if (dir == 'O') {
        ans.push_back({'D', -1}), dir = 'N';
      }
      if (dir == 'N') {
        ans.push_back({'D', -1}), dir = 'E';
      }
      ans.push_back({'A', x});
      ans.push_back({'D', -1}), dir = 'S';
      ans.push_back({'A', -y});
    }
  } else if (x < 0 && y < 0) {
    if (dir == 'O') {
      ans.push_back({'A', -x});
      ans.push_back({'D', -1}), dir = 'N';
      ans.push_back({'D', -1}), dir = 'E';
      ans.push_back({'D', -1}), dir = 'S';
      ans.push_back({'A', -y});
    } else {
      if (dir == 'N') {
        ans.push_back({'D', -1}), dir = 'E';
      }
      if (dir == 'E') {
        ans.push_back({'D', -1}), dir = 'S';
      }
      ans.push_back({'A', -y});
      ans.push_back({'D', -1}), dir = 'E';
      ans.push_back({'A', -x});
    }
  } else {
    assert(x < 0 && y > 0);
    if (dir == 'N') {
      ans.push_back({'A', y});
      ans.push_back({'D', -1}), dir = 'E';
      ans.push_back({'D', -1}), dir = 'S';
      ans.push_back({'D', -1}), dir = 'O';
      ans.push_back({'A', -x});
    } else {
      if (dir == 'E') {
        ans.push_back({'D', -1}), dir = 'S';
      }
      if (dir == 'S') {
        ans.push_back({'D', -1}), dir = 'O';
      }
      ans.push_back({'A', -x});
      ans.push_back({'D', -1}), dir = 'N';
      ans.push_back({'A', y});
    }
  }

  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll x0, y0, xd, yd;
  char dir;
  cin >> x0 >> y0 >> dir >> xd >> yd;

  xd -= x0, x0 = 0;
  yd -= y0, y0 = 0;

  auto ans = solve(xd, yd, dir);
  cout << ans.size() << '\n';
  for (auto [c, d] : ans) {
    if (c == 'D') {
      cout << "D\n";
    } else {
      cout << "A " << d << '\n';
    }
  }
}
