// https://codeforces.com/gym/105925/problem/I

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


ll solve(vector<vu>& css, ull L, ull U) {
  ull N = css.size();
  ull T = css[0].size();

  // dp_prev[t][i] = máximo en el tiempo t (sin contar t) usando por última vez uno anterior al i-ésimo
  // dp_post[t][i] = máximo en el tiempo t (sin contar t) usando por última vez uno posterior al i-ésimo

  vector<vi> dp_prev(T + 1, vi(N + 1, -inf));
  vector<vi> dp_post(T + 1, vi(N, -inf));
  dp_prev[0] = vi(N + 1, 0);
  dp_post[0] = vi(N, 0);

  if (U > T) {
    return -1;
  }

  fore(t, L, T + 1) {
    vi i_anss(N, -inf);
    fore(i, 0, N) {
      // Ahora pruebo usar i
      ll i_acc = 0;
      for (ull t2 = t - 1; t2 > t - L; t2--) {
        i_acc += css[i][t2];
      }
      ll i_ans = -inf;
      for (ull t2 = t - L; (t2 + 1 != 0) && (t < U || t2 >= t - U); t2--) {
        i_acc += css[i][t2];
        ll this_ans = i_acc + max(dp_prev[t2][i], dp_post[t2][i]);
        i_ans = max(i_ans, this_ans);
      }
      i_anss[i] = i_ans;
    }
    fore(i, 0, N) {
      dp_prev[t][i+1] = max(dp_prev[t][i], i_anss[i]);
    }
    for (ull i = N - 1; i--; ) {
      dp_post[t][i] = max(dp_post[t][i + 1], i_anss[i + 1]);
    }
  }

  ll ans = max(dp_prev[T][N], dp_post[T][0]);
  if (ans < 0) {
    return -1;
  }
  return ans;

}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N, T;
  cin >> N >> T;
  vector<vu> css(N, vu(T));
  fore(i, 0, N) {
    fore(j, 0, T) {
      cin >> css[i][j];
    }
  }
  ull L, U;
  cin >> L >> U;

  auto ans = solve(css, L, U);
  cout << ans << '\n';

}
