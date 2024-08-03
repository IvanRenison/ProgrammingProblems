// https://atcoder.jp/contests/abc365/tasks/abc365_c

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


ull solve(ull M, vu& As) {
  ull N = SZ(As);

  auto f = [&](ull x) -> bool {
    ull sum = 0;
    fore(i, 0, N) {
      sum += min(As[i], x);
    }
    return sum <= M;
  };


  if (f(inf)) {
    return inf;
  }
  if (M < N) {
    return 0;
  }

  ull l = 0, r = inf;

  // l  → lower, r → upper
  while (l + 1 < r) {
    ull m = (l + r) / 2;
    if (f(m)) {
      l = m;
    } else {
      r = m;
    }
  }

  ull ans = l;

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N, M;
  cin >> N >> M;
  vu as(N);
  fore(i, 0, N) {
    cin >> as[i];
  }

  auto ans = solve(M, as);
  if (ans == inf) {
    cout << "infinite" << "\n";
  } else {
    cout << ans << "\n";
  }

}
