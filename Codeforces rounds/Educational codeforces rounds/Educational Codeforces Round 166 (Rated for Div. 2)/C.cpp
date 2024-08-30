// https://codeforces.com/contest/1976/problem/C

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


vu solve(ull n, ull m, vu& as, vu& bs) {

  ull a_sum = 0, a_count = 0, b_sum = 0, b_count = 0;
  ull a_lim = inf, b_lim = inf;
  fore(i, 0, n + m) {
    ull a = as[i], b = bs[i];
    if (a > b) {
      if (a_count < n) {
        a_sum += a;
        a_count++;
      } else {
        b_sum += b;
        b_count++;
        if (a_lim == inf) {
          a_lim = i;
        }
      }
    } else {
      if (b_count < m) {
        b_sum += b;
        b_count++;
      } else {
        a_sum += a;
        a_count++;
        if (b_lim == inf) {
          b_lim = i;
        }
      }
    }
  }

  assert(a_count == n && b_count == m);
  assert(a_lim == inf || b_lim == inf);

  ull def_ans = a_sum + b_sum;

  vu ans(n + m + 1);
  fore(i, 0, n + m) {
    ull a = as[i], b = bs[i];
    ull this_ans;
    if (a > b) {
      if (a_lim != inf) {
        if (i < a_lim) {
          this_ans = def_ans - as[i] - bs[a_lim] + as[a_lim] + bs.back();
        } else {
          this_ans = def_ans - bs[i] + bs.back();
        }
      } else {
        this_ans = def_ans - as[i] + as.back();
      }
    } else {
      if (b_lim != inf) {
        if (i < b_lim) {
          this_ans = def_ans - bs[i] - as[b_lim] + bs[b_lim] + as.back();
        } else {
          this_ans = def_ans - as[i] + as.back();
        }
      } else {
        this_ans = def_ans - bs[i] + bs.back();
      }
    }
    ans[i] = this_ans;
  }
  ans[n + m] = def_ans;

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
    vu as(n+m+1), bs(n + m + 1);
    for (ull& a : as) {
      cin >> a;
    }
    for (ull& a : bs) {
      cin >> a;
    }

    auto ans = solve(n, m, as, bs);
    for (ull a : ans) {
      cout << a << ' ';
    }
    cout << '\n';
  }

}
