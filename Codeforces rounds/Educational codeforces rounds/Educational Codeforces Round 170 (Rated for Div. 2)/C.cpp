// https://codeforces.com/contest/2025/problem/C

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


ull solve(ull k, vu& as) {
  map<ull, ull> cnt;
  for (ull a : as) {
    cnt[a]++;
  }

  vuu list;
  for (auto [a, c] : cnt) {
    list.push_back({c, a});
  }

  ull ans = 0;
  for (ull i = 0; i < list.size();) {
    ull this_ans = list[i].first;
    ans = max(ans, this_ans);
    ull j = i + 1;
    while (j < list.size() && list[j].second == list[j - 1].second + 1) {
      if (j - i >= k) {
        this_ans -= list[i].first;
        i++;
      }
      assert(j - i < k);
      this_ans += list[j].first;
      ans = max(ans, this_ans);
      j++;
    }

    i = j;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, k;
    cin >> n >> k;
    vu as(n);
    for (ull& a : as) {
      cin >> a;
      a--;
    }

    auto ans = solve(k, as);
    cout << ans << '\n';
  }

}
