// https://codeforces.com/contest/2111/problem/E

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


string solve(string& s, vector<pair<char, char>>& ops) {
  ull m = ops.size();

  ull ba = 0, ca = 0, bc = 0, bca = 0, cb = 0, cba = 0;
  for (ull i = m; i--;) {
    auto [x, y] = ops[i];
    if (x == 'b' && y == 'a') {
      ba++;
    } else if (x == 'c' && y == 'a') {
      ca++;
    } else if (x == 'c' && y == 'b') {
      cb++;
      if (ba > 0) {
        cb--;
        ba--;
        cba++;
      }
    } else if (x == 'b' && y == 'c') {
      bc++;
      if (ca > 0) {
        bc--;
        ca--;
        bca++;
      }
    }
  }

  for (char& x : s) {
    if (x == 'b') {
      if (ba > 0) {
        ba--;
        x = 'a';
      } else if (cba > 0) {
        cba--;
        x = 'a';
        cb++;
      } else if (bca > 0) {
        bca--;
        x = 'a';
      }
    } else if (x == 'c') {
      if (ca > 0) {
        ca--;
        x = 'a';
      } else if (bca > 0) {
        bca--;
        x = 'a';
      } else if (cba > 0) {
        cba--;
        x = 'a';
      } else if (cb > 0) {
        cb--;
        x = 'b';
      }
    }
  }

  return s;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<pair<char, char>> ops(m);
    for (auto& [x, y] : ops) {
      cin >> x >> y;
    }


    auto ans = solve(s, ops);
    cout << ans << '\n';
  }

}
