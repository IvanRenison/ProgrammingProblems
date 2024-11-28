// https://codeforces.com/contest/2039/problem/C2

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


ull solve(ull x, ull m) {
  ull ans = 0;
  fore(y, 1, min(x + 1, m + 1)) {
    ull xy = x ^ y;
    if (xy % y == 0 || xy % x == 0) {
      ans++;
    }
  }

  if (m > x) {
    ull nm = m > 4 * x ? m - 4 * x : x;

    ull mul = (nm + x - 1) / x;
    ans += mul - 1;

    for (ull xy = mul * x + x; xy < m + 2 * x; xy += x) {
      ull y = x ^ xy;
      if (y <= m && y > x && (xy % x == 0 || xy % y == 0)) {
        ans++;
      }
    }
  }

  return ans;
}

ull force(ull x, ull m) {
  ull ans = 0;
  fore(y, 1, m + 1) {
    ll xy = x ^ y;
    if (xy % x == 0 || xy % y == 0) {
      ans++;
    }
  }
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef TEST
  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull x, m;
    cin >> x >> m;

    auto ans = solve(x, m);
    cout << ans << '\n';
  }
#else
  fore(_, 0, 1000) {
    ull x = rand() % 10 + 1;
    ull m = rand() % 10 + 1;
    if (solve(x, m) != force(x, m)) {
      cerr << x << ' ' << m << endl;
      cerr << solve(x, m) << ' ' << force(x, m) << endl;
      return 1;
    }
  }
#endif
}
