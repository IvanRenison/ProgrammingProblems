// https://codeforces.com/gym/103049/problem/E
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int)x.size())
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

void solve(ll ax, ll ay, ll bx, ll by, vii moves) {
  ll n = moves.size();


  set<ii> A;

  for(auto [x, y] : moves) {
    if (0 <= ax+x && ax+x < n && 0 <= ay+y && ay+y < n) {
      A.insert({ax+x, ay+y});
    }
  }

  for(auto [x, y] : moves) {
    if (A.find({bx-x, by-y}) != A.end()) {
      cout << "Alice wins\n";
      return;
    }
  }


  if (n <= 1000) {
    vector<vector<bool>> B(n, vector<bool>(n, false));
    B[bx][by]= true;
    for(auto [x, y] : moves) {
      if (0 <= bx+x && bx+x < n && 0 <= by+y && by+y < n) {
        B[bx+x][by+y] = true;
      }
      for(auto [x2, y2] : moves) {
        if (0 <= bx+x+x2 && bx+x+x2 < n && 0 <= by+y+y2 && by+y+y2 < n) {
          B[bx+x+x2][by+y+y2] = true;
        }
      }
    }

    fore(i, 0, n) {
      fore(j, 0, n) {
        if (!B[i][j]) {
          cout << "tie " << i + 1 << ' ' << j + 1 << '\n';
          return;
        }
      }
    }

    cout << "Bob wins\n";
    return;

  } else {

    set<ii> B;
    for(auto [x, y] : moves) {
      if (0 <= bx+x && bx+x < n && 0 <= by+y && by+y < n) {
        B.insert({bx+x, by+y});
      }
    }

    while (true) {
      ll x2 = rand() % n;
      ll y2 = rand() % n;

      bool valid = true;
      for(auto [x, y] : moves) {
        if (0 <= x2-x && x2-x < n && 0 <= y2-y && y2-y < n) {
          if (B.find({x2-x, y2-y}) != B.end()) {
            valid = false;
            break;
          }
        }
      }
      if (valid) {
        cout << "tie " << x2 + 1 << ' ' << y2 + 1 << '\n';
        return;
      }
    }
  }
}

int main(){FIN;

  ull n;
  cin >> n;
  ll ax, ay, bx, by;
  cin >> ax >> ay >> bx >> by;
  ax--, ay--, bx--, by--;
  vii moves(n);
  for(auto& [x, y] : moves) {
    cin >> x >> y;
  }

  solve(ax, ay, bx, by, moves);

	return 0;
}