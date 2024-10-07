//

#ifdef PRAGMAS
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

/*
distance = speed * time
time = distance / speed
speed = distance / time

*/

optional<ld> solve(vuu& ABs) {
  ull N = ABs.size();

  ld m = 0;
  ld M = 1e30;
  fore(i, 0, N) {
    ld a = ABs[i].first;
    ld b = ABs[i].second;


    ld tm = (ld)(i + 1) / (ld) b;
    ld tM = (ld)(i + 1) / (ld) a;

    m = max(m, tm);
    M = min(M, tM);
  }

  if (m > M) {
    return {};
  }

  return m;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  cout << setprecision(10);

  fore(testCase, 0, t) {
    ull N;
    cin >> N;
    vuu ABs(N);
    for (auto& [a, b] : ABs) {
      cin >> a >> b;
    }

    auto ans = solve(ABs);

    cout << "Case #" << testCase + 1 << ": ";
    if (ans.has_value()) {
      cout << *ans << '\n';
    } else {
      cout << "-1\n";
    }
  }

}
