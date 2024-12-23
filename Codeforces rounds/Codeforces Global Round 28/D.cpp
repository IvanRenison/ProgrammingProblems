// https://codeforces.com/contest/2048/problem/D

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


vu solveSimp(vu& counts) {
  ull m = counts.size();

  sort(ALL(counts));

  vu ans(m);

  fore(k, 1, m + 1) {
    ull& this_ans = ans[k - 1];
    this_ans += m / k;

    for (ull i = 0; i + k <= m; i += k) {
      this_ans += counts[i + k - 1];
    }
  }

  return ans;
}

vu solve(vu& as, vu& bs) {
  ull n = as.size(), m = bs.size();

  ull a0 = as[0];
  vu as_;
  for (ull a : as) {
    if (a > a0) {
      as_.push_back(a);
    }
  }

  sort(ALL(as_));

  vu counts(m, 0);

  fore(i, 0, m) {
    ull b = bs[i];
    if (b > a0) {
      counts[i] = as_.end() - lower_bound(ALL(as_), b);
    }
  }

  vu ans = solveSimp(counts);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m;
    cin >> n >> m;
    vu as(n), bs(m);
    fore(i, 0, n) {
      cin >> as[i];
    }
    fore(i, 0, m) {
      cin >> bs[i];
    }

    auto ans = solve(as, bs);
    fore(i, 0, m) {
      cout << ans[i] << " ";
    }
    cout << "\n";
  }

}
