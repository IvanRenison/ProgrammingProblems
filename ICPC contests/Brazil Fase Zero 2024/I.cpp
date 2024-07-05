//

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



bool solve(ull N, ull M, const vb& bs) {
  ull K = N * M;

  vu sums(2 * K + 1);
  fore(i, 1, K + 1) {
    sums[i] = sums[i - 1] + bs[i - 1];
  }
  fore(i, K + 1, 2 * K + 1) {
    sums[i] = sums[i - 1] + bs[i - 1 - K];
  }

  fore(i, 0, M) {
    set<ull> counts;
    fore(j, 0, N) {
      ull count = sums[i + j * M + M] - sums[i + j * M];
      /* fore(k, i + j * N, i + j * N + N) {
        count += bs[k % (N * M)];
      } */
      counts.insert(count);
    }
    if (counts.size() != N) {
      return false;
    }
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N, M;
  cin >> N >> M;
  vb bs(N * M);
  fore(i, 0, N * M) {
    char c;
    cin >> c;
    bs[i] = c == '1';
  }

  auto ans = solve(N, M, bs);
  cout << (ans ? "S" : "N") << '\n';

  return EXIT_SUCCESS;
}
