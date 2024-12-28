// https://codeforces.com/contest/2053/problem/B

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

vb solve(vuu& lrs) {
  ull n = lrs.size();

  vu uniqes(2 * n + 1);

  for (auto [l, r] : lrs) {
    if (l + 1 == r) {
      uniqes[l]++;
    }
  }

  vu nonUniqesSums(2 * n + 2);
  fore(i, 0, 2 * n + 1) {
    nonUniqesSums[i + 1] = nonUniqesSums[i] + (uniqes[i] == 0);
  }

  vb ans(n, false);
  fore(i, 0, n) {
    auto [l, r] = lrs[i];
    if (l + 1 == r) {
      ans[i] = uniqes[l] == 1;
    } else {
      if (nonUniqesSums[r] - nonUniqesSums[l] > 0) {
        ans[i] = true;
      }
    }
  }

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
    vuu lrs(n);
    fore(j, 0, n) {
      cin >> lrs[j].first >> lrs[j].second;
      lrs[j].first--;
    }

    auto ans = solve(lrs);
    for (auto a : ans) {
      cout << (a ? "1" : "0");
    }
    cout << '\n';
  }

}
