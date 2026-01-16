// https://codeforces.com/contest/2182/problem/C

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

vb calc_comp(vu& as, vu& bs) {
  ull n = as.size();

  vb comp(n, true);

  fore(i, 0, n) {
    ull a = as[i];
    fore(j, 0, n) {
      ull b = bs[j];
      if (!(a < b)) {
        comp[i <= j ? j - i : j + n - i] = false;
      }
    }
  }

  return comp;
}

ull solve(vu& as, vu& bs, vu& cs) {
  ull n = as.size();

  vb comp_ab = calc_comp(as, bs);
  vb comp_bc = calc_comp(bs, cs);

  ull count_ab = accumulate(ALL(comp_ab), 0ull);
  ull count_bc = accumulate(ALL(comp_bc), 0ull);
  ull ans = n * count_ab * count_bc;

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
    vu as(n), bs(n), cs(n);
    for (ull& a : as) {
      cin >> a;
    }
    for (ull& b : bs) {
      cin >> b;
    }
    for (ull& c : cs) {
      cin >> c;
    }

    auto ans = solve(as, bs, cs);
    cout << ans << '\n';
  }

}
