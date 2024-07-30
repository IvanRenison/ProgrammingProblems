// https://codeforces.com/contest/1997/problem/D

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


ull solve(const vu& as, const vu& ps) {
  ull n = as.size();

  vector<vu> suns(n);
  fore(i, 0, n - 1) {
    suns[ps[i]].push_back(i + 1);
  }

  function<ull(ull)> f = [&](ull u) -> ull {
    if (suns[u].empty()) {
      return as[u];
    }
    ull m = inf;
    for (ull v : suns[u]) {
      m = min(m, f(v));
    }

    if (m <= as[u]) {
      return m;
    } else {
      ull diff = m - as[u];
      ull ans = as[u] + diff / 2;
      return ans;
    }
  };

  ull m = inf;
  for (ull v : suns[0]) {
    m = min(m, f(v));
  }

  ull ans = as[0] + m;

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu as(n), ps(n - 1);
    for (ull& a : as) {
      cin >> a;
    }
    for (ull& p : ps) {
      cin >> p;
      p--;
    }

    auto ans = solve(as, ps);
    cout << ans << '\n';
  }

}
