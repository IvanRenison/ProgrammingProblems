// https://codeforces.com/group/Xaa6lwRoge/contest/609355/problem/F

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


uu solve(vu& as, vu& bs) {
  ull n = as.size(), m = bs.size();

  ull ans_a = 3 * n, ans_b = 3 * m;

  auto upd_ans = [&](ull a, ull b) {
    ll ans_diff = ans_a - ans_b;
    ll diff = a - b;
    if (diff > ans_diff) {
      ans_a = a;
      ans_b = b;
    }
  };

  vuu abss(n + m);
  fore(i, 0, n) {
    abss[i] = {as[i], 0};
  }
  fore(i, 0, m) {
    abss[n + i] = {bs[i], 1};
  }
  sort(ALL(abss));

  ull a = ans_a, b = ans_b;
  for (auto [x, c] : abss) {
    if (c == 0) {
      a--;
    } else {
      b--;
      upd_ans(a, b);
    }
  }

  return {ans_a, ans_b};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;
  vu as(n);
  for (ull& a : as) {
    cin >> a;
  }
  ull m;
  cin >> m;
  vu bs(m);
  for (ull& b : bs) {
    cin >> b;
  }

  auto [a, b] = solve(as, bs);
  cout << a << ':' << b << '\n';

}
