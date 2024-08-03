// https://atcoder.jp/contests/abc365/tasks/abc365_d

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

bool wins(char a, char b) {
  if (a == 'R' && b == 'S') return true;
  if (a == 'S' && b == 'P') return true;
  if (a == 'P' && b == 'R') return true;
  return false;
}

ull solve(string& A) {
  ull N = SZ(A);

  vector<vi> dp(N + 1, vi(3));
  fore(i, 0, N) {
    char a = A[i];
    fore(j, 0, 3) {
      if (wins("RPS"[j], a)) {
        dp[i + 1][j] = max(dp[i][(j + 1) % 3], dp[i][(j + 2) % 3]) + 1;
      } else if ("RPS"[j] == a) {
        dp[i + 1][j] = max(dp[i][(j + 1) % 3], dp[i][(j + 2) % 3]);
      } else {
        dp[i + 1][j] = -inf;
      }
    }
  }

  ll ans = 0;
  fore(i, 0, 3) {
    ans = max(ans, (ll)dp[N][i]);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N;
  cin >> N;
  string A;
  cin >> A;

  auto ans = solve(A);
  cout << ans << '\n';

}
