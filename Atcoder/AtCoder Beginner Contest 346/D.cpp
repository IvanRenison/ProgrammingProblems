// https://atcoder.jp/contests/abc346/tasks/abc346_d

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


ull solve(const vb& Ss, const vu& Cs) {
  ull N = Ss.size();

  vector<vu> left_dp(N + 1, vu(2)), right_dp(N + 1, vu(2));

  fore(i, 0, N) {
    bool S = Ss[i];
    ull C = Cs[i];

    left_dp[i + 1][S] = left_dp[i][!S];
    left_dp[i + 1][!S] = left_dp[i][S] + C;
  }

  fore(i, 0, N) {
    bool S = Ss[N - 1 - i];
    ull C = Cs[N - 1 - i];

    right_dp[i + 1][S] = right_dp[i][!S];
    right_dp[i + 1][!S] = right_dp[i][S] + C;
  }

  ull ans = inf;

  fore(i, 0, N - 1) {
    ull this_ans = min(left_dp[i + 1][0] + right_dp[N - i - 1][0], left_dp[i + 1][1] + right_dp[N - i - 1][1]);
    ans = min(ans, this_ans);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N;
  cin >> N;
  vb S(N);
  fore(i, 0, N) {
    char c;
    cin >> c;
    S[i] = c == '1';
  }
  vu Cs(N);
  for (ull& C : Cs) {
    cin >> C;
  }

  auto ans = solve(S, Cs);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
