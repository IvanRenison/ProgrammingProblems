// https://codeforces.com/contest/2025/problem/D

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#pragma GCC optimize("Ofast")
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

struct presums {
  typedef ull T;
  T op(T a, T b) { return a + b; }
  T rev(T a, T b) { return a - b; }
  constexpr static T neut = 0;
  // rev(op(a, b), b) = a

  ull n;
  vector<T> as;

  presums(ull n) : n(n), as(n + 1) {}

  void update(ull i, ull j, T v) { // [i, j)
    as[i] = op(as[i], v);
    as[j] = rev(as[j], v);
  }

  vector<T> build() {
    vector<T> ans(n);
    ans[0] = as[0];
    fore(i, 1, n) {
      ans[i] = op(ans[i - 1], as[i]);
    }
    return ans;
  }
};

ull solve(ull m, const vi& rs) {
  ull n = rs.size();

  vu zeros(n + 1, 0);
  fore(i, 0, n) {
    zeros[i + 1] = zeros[i] + (rs[i] == 0);
  }

  presums dp(m + 1); // dp[i] = max with i intelligence

  fore(i, 0, n) {
    ll r = rs[i];
    if (r == 0) {
      vu dp2(m + 1);
      vu bu = dp.build();
      fore(j, 0, m + 1) {
        dp2[j] = max(bu[j > 0 ? j - 1 : j], bu[j]);
      }
      dp = presums(m + 1);
      fore(j, 0, m + 1) {
        dp.update(j, j + 1, dp2[j]);
      }
    } else if (r > 0) { // Intel
      if (r <= zeros[i]) {
        dp.update(r, zeros[i] + 1, 1);
      }
    } else if (r < 0) { // Strength
      r = -r;
      if (r <= zeros[i]) {
        dp.update(0, zeros[i] - r + 1, 1);
      }
    }
    //cerr << i << ' ' << r << '\n';
    //dp.print();
  }

  vu bu = dp.build();
  ull ans = 0;
  fore(i, 0, m + 1) {
    ans = max(ans, bu[i]);
  }
  return ans;
}

ull force(ull m, const vi& rs) {
  ull ans = 0;

  fore(x, 0, 1 << m) {
    ull this_ans = 0;
    ull intel = 0, stren = 0;
    ull i = 0;
    for (ll r : rs) {
      if (r == 0) {
        if (x & (1 << i)) {
          intel++;
        } else {
          stren++;
        }
        i++;
      } else {
        if (r > 0) {
          this_ans += intel >= r;
        } else {
          this_ans += stren >= (ull)(-r);
        }
      }
    }
    ans = max(ans, this_ans);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef TEST
  ull n, m;
  cin >> n >> m;
  vi rs(n);
  fore(i, 0, n) cin >> rs[i];
  auto ans = solve(m, rs);
  cout << ans << '\n';
#else

  fore(_, 0, 1000) {
    ull n = rand() % 10 + 1;
    vi rs(n);
    for (ll& r : rs) {
      r = rand() % 6 - 3;
    }

    ull m = 0;
    for (ll r : rs) {
      m += r == 0;
    }

    ull ans = solve(m, rs);
    ull ansf = force(m, rs);

    if (ans != ansf) {
      cerr << "WA\n";
      cerr << n << ' ' << m << '\n';
      for (ll r : rs) {
        cerr << r << ' ';
      }
      cerr << '\n';
      cerr << ans << ' ' << ansf << '\n';
      break;
    }
  }
#endif
}
