// https://codeforces.com/contest/2026/problem/B

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


ull solve(vu& as) {
  ull n = SZ(as);

  if (n % 2 == 0) {
    ull ans = 0;
    for (ull i = 0; i < n; i += 2) {
      ans = max(ans, as[i + 1] - as[i]);
    }
    return ans;
  } else {
    ull ans = inf;
    for (ull i = 0; i < n; i += 2) {
      ull this_ans = 1;
      for (ull j = 0; j < i; j += 2) {
        this_ans = max(this_ans, as[j + 1] - as[j]);
      }
      for (ull j = i + 1; j < n; j += 2) {
        this_ans = max(this_ans, as[j + 1] - as[j]);
      }
      ans = min(ans, this_ans);
    }
    return ans;
  }

}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu as(n);
    fore(j, 0, n) {
      cin >> as[j];
    }

    auto ans = solve(as);
    cout << ans << '\n';
  }

}
