// https://codeforces.com/group/Xaa6lwRoge/contest/604333/problem/F

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


string solve(string& cs, vuu& lrs, vi& ks) {
  ull n = cs.size();

  auto query = [&](ull k, auto&& query) -> char {
    if (k < n) return cs[k];

    ull m = n;

    for (auto [l, r] : lrs) {
      ull d = r - l;
      if (k < m + d) {
        assert(l + (k - m) < k);
        return query(l + (k - m), query);
      } else {
        m += d;
      }
    }

    assert(false);
  };

  string ans;
  for (auto k : ks) {
    ans += query(k, query);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, c, q;
    cin >> n >> c >> q;
    string s;
    cin >> s;
    vuu lrs(c);
    for (auto& [l, r] : lrs) {
      cin >> l >> r;
      l--;
    }
    vi ks(q);
    for (auto& k : ks) {
      cin >> k;
      k--;
    }

    auto ans = solve(s, lrs, ks);
    for (char c : ans) {
      cout << c << '\n';
    }
  }

}
