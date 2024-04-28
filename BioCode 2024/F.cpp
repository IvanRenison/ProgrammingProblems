// https://codeforces.com/gym/105123/problem/F

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


vu solve(const vu& ts) {
  ull n = ts.size();

  vu dp_go(n), dp_back(n);

  dp_go[0] = 1;
  fore(i, 1, n) {
    ull t = ts[i - 1];
    ull f = dp_go[i - 1];
    assert(f > 0);

    if (t == f) {
      dp_go[i] = max(f - 1, 1ull);
    } else if (t < f) {
      dp_go[i] = f + 1;
    } else {
      dp_go[i] = max(f - 1, 1ull);
    }
  }

  dp_back[n - 1] = 1;
  for (ull i = n - 2; i < n; i--) {
    ull t = ts[i + 1];
    ull f = dp_back[i + 1];
    assert(f > 0);

    if (t == f) {
      dp_back[i] = max(f - 1, 1ull);
    } else if (t < f) {
      dp_back[i] = f + 1;
    } else {
      dp_back[i] = max(f - 1, 1ull);
    }
  }

  vu ans(n);
  fore(i, 0, n) {
    ans[i] = max(dp_go[i], dp_back[i]);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;
  vu ts(n);
  for (ull& t : ts) {
    cin >> t;
  }

  auto ans = solve(ts);
  for (ull a : ans) {
    cout << a << ' ';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
