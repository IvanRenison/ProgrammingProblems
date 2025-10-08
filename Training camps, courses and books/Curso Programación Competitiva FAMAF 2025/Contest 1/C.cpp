// https://codeforces.com/group/Xaa6lwRoge/contest/604333/problem/C

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;


ull solve(vector<string> &grid) {
  ull r = grid.size(), c = grid[0].size();

  ull empty_rows = 0;
  fore(i, 0, r) {
    bool empty = true;
    fore(j, 0, c) {
      if (grid[i][j] == 'S') {
        empty = false;
        break;
      }
    }
    if (empty) {
      empty_rows++;
    }
  }

  ull empty_cols = 0;
  fore(j, 0, c) {
    bool empty = true;
    fore(i, 0, r) {
      if (grid[i][j] == 'S') {
        empty = false;
        break;
      }
    }
    if (empty) {
      empty_cols++;
    }
  }

  ull ans = empty_rows * c + empty_cols * r - empty_rows * empty_cols;

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull r, c;
  cin >> r >> c;
  vector<string> grid(r);
  fore(i, 0, r) {
    cin >> grid[i];
  }

  auto ans = solve(grid);
  cout << ans << '\n';

}
