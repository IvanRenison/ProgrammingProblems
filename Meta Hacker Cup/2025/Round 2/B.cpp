// https://www.facebook.com/codingcompetitions/hacker-cup/2025/round-2/problems/B

/* #ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif */

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

bool possible(const vu& needed, const vu& Bs) {
  ull n = needed.size(), M = Bs.size();

  ull sum_need = 0;
  ull sum_Bs = 0;
  ull Bs_lim = M;
  fore(k, 0, n) {
    sum_need += needed[k];

    while (Bs_lim > 0 && Bs[Bs_lim - 1] < k + 1) {
      Bs_lim--;
    }

    sum_Bs += Bs_lim;

    if (sum_Bs < sum_need) {
      return false;
    }
  }

  return true;
}

ull solve(vu& As, vu& Bs) {
  ull N = As.size(), M = Bs.size();

  sort(ALL(As));
  reverse(ALL(As));
  sort(ALL(Bs));
  reverse(ALL(Bs));

  vu blocks = {1};

  fore(i, 1, N) {
    if (As[i] == As[i - 1]) {
      blocks.back()++;
    } else {
      blocks.push_back(1);
    }
  }

  ull l = 0, r = blocks.size() + 1;
  while (l + 1 < r) {
    ull m = (l + r) / 2;

    vu needed;
    fore(i, 0, m) {
      fore(_, 0, blocks[i]) {
        needed.push_back(m - i);
      }
    }

    bool can = possible(needed, Bs);
    if (can) {
      l = m;
    } else {
      r = m;
    }
  }

  ull ans = 0;
  fore(i, 0, l) {
    ans += blocks[i];
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(testCase, 0, t) {
    ull N, M;
    cin >> N >> M;
    vu As(N), Bs(M);
    for (ull& A : As) {
      cin >> A;
    }
    for (ull& B : Bs) {
      cin >> B;
    }

    auto ans = solve(As, Bs);

    cout << "Case #" << testCase + 1 << ": ";
    cout << ans << '\n';
  }

}
/*

1
6 4
4 3 2 1 1 1
3 3 3 3

*/