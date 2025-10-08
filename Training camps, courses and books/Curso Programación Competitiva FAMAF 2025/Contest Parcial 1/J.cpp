// https://codeforces.com/group/Xaa6lwRoge/contest/617806/problem/J

/* #ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif
 */
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


bool solve(string s, string l, string r) {
  ull n = s.size(), m = r.size();

  vector<vu> apps(10);
  fore(i, 0, n) {
    apps[s[i] - '0'].push_back(i);
  }

  fore(d, 0, 10) {
    reverse(ALL(apps[d]));
  }

  auto next = [&](ull d, ull j) -> ull {
    ull ans = n;
    while (!apps[d].empty() && apps[d].back() < j) {
      apps[d].pop_back();
    }

    if (!apps[d].empty()) {
      ans = apps[d].back();
    }

    return ans;
  };

  ull i = 0;
  fore(j, 0, m) {
    ull ll = l[j] - '0', rr = r[j] - '0' + 1;
    ull ni = 0;
    fore(d, ll, rr) {
      ull this_ni = next(d, i);
      if (this_ni > ni) {
        ni = this_ni;
      }
    }
    if (ni == n) {
      return true;
    }
    i = ni + 1;
  }

  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    string s;
    cin >> s;
    ull m;
    cin >> m;
    string l, r;
    cin >> l >> r;

    bool ans = solve(s, l, r);
    if (ans) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }

}
