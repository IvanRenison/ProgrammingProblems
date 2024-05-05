// https://redprogramacioncompetitiva.com/contests/2024/04

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

vuu solve(ull k, const vu& as) {
  ull n = as.size();

  vu sums(n + 1);
  fore(i, 0, n) {
    sums[i + 1] = sums[i] + as[i];
  }

  vuu ans(n - k + 1);

  ull sum = 0;
  fore(i, 0, k) {
    sum += (i + 1) * as[i];
  }

  ans[0] = {sum, 0};

  fore(i, k, n) {
    sum += k * as[i] - sums[i] + sums[i - k];
    ans[i - k + 1] = {sum, i - k + 1};
  }

  sort(ALL(ans));

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, k;
  cin >> n >> k;
  vu as(n);
  for (auto &a : as) {
    cin >> a;
  }

  vuu ans = solve(k, as);
  for (const auto& [a, b] : ans) {
    cout << b + 1 << ' ' << a << '\n';
  }

  return EXIT_SUCCESS;
}
