// https://www.facebook.com/codingcompetitions/hacker-cup/2024/practice-round/problems/D1

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

ull diff(ull x, ull y) {
  return x > y ? x - y : y - x;
}

uu solve(ull G, const vu& Es) {
  ull N = Es.size();

  ull ans_i = 0, ans_d = inf;

  fore(i, 0, N) {
    ull d = diff(Es[i], G);
    if (d < ans_d || (d == ans_d && Es[i] > Es[ans_i])) {
      ans_i = i;
      ans_d = d;
    }
  }

  ull count_less = 0;
  fore(i, 0, N) {
    if (Es[i] < Es[ans_i]) {
      count_less++;
    }
  }

  return {N - 1 - count_less, ans_d};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull N, G;
    cin >> N >> G;
    vu Es(N);
    for (ull& E : Es) {
      cin >> E;
    }

    auto [j, d] = solve(G, Es);
    cout << "Case #" << i + 1 << ": " << j + 1 << ' ' << d << '\n';
  }

}
