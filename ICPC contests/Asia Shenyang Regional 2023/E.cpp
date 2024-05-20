// https://codeforces.com/gym/104869/problem/E

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
typedef tuple<ull, ull, bool, ull> uubu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

bool seComen(ull q, ull i, ull j) {
  return j > i && (i != 0 && j - i > q);
}

optional<ull> solve(ull x, ull y, ull p, ull q) {

  vector<vector<vb>> vis(x + 1, vector<vb>(y + 1, vb(2, false)));

  queue<uubu> que;
  que.push({x, y, false, 0});
  vis[x][y][false] = true;

  while (!que.empty()) {
    auto [i, j, l, d] = que.front();
    que.pop();

    if (i == x && l) {
      return d;
    }

    fore(a, 0, i + 1) {
      fore(b, 0, j + 1) {
        if (a + b > p) {
          break;
        }
        ll ni = i - a, nj = j - b;
        if (!vis[x - ni][y - nj][!l] && !seComen(q, ni, nj)) {
          que.push({x - ni, y - nj, !l, d + 1});
          vis[x - ni][y - nj][!l] = true;
        }
      }
    }
  }


  return {};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull x, y, p, q;
  cin >> x >> y >> p >> q;

  auto ans = solve(x, y, p, q);
  if (ans) {
    cout << *ans << '\n';
  } else {
    cout << "-1\n";
  }

  return EXIT_SUCCESS;
}
