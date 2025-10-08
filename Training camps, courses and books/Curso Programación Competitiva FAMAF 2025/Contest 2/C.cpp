// https://codeforces.com/group/Xaa6lwRoge/contest/609355/problem/C

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

ull diff(ull a, ull b) {
  return a > b ? a - b : b - a;
}

ull solve(vb& as, vb& bs)  {
  ull n = as.size();
  ull count_a = accumulate(ALL(as), 0ull);
  ull count_b = accumulate(ALL(bs), 0ull);

  ull count01 = 0, count10 = 0;
  fore(i, 0, n) {
    if (as[i] == 0 && bs[i] == 1) {
      count01++;
    } else if (as[i] == 1 && bs[i] == 0) {
      count10++;
    }
  }

  return diff(count_a, count_b) + (count01 > 0 && count10 > 0);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vb a(n), b(n);
    fore(i, 0, n) {
      char c;
      cin >> c;
      a[i] = c == '1';
    }
    fore(i, 0, n) {
      char c;
      cin >> c;
      b[i] = c == '1';
    }

    auto ans = solve(a, b);
    cout << ans << '\n';
  }

}
