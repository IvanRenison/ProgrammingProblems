// https://codeforces.com/gym/101081/problem/I
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, pluton = b; i < pluton; i++)
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

const ull maxT = 24*60;

vu solve(const vuu& meets) {
  ull N = meets.size();

  vector<vuu> endings(maxT + 1);
  fore(i, 0, N) {
    auto [t0, t1] = meets[i];
    endings[t1].push_back({t0, i});
  }

  vu dp(maxT + 1, 0);
  fore(i, 1, maxT + 1) {
    dp[i] = dp[i - 1];
    for (auto [t0, _] : endings[i]) {
      dp[i] = max(dp[i], dp[t0] + 1);
    }
  }

  vu ans;
  ull i = maxT;
  while (i > 0) {
    if (dp[i] == dp[i - 1]) {
      i--;
    } else {
      for (auto [t0, j] : endings[i]) {
        if (dp[i] == dp[t0] + 1) {
          ans.push_back(j);
          i = t0;
          break;
        }
      }
    }
  }

  reverse(all(ans));

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vuu meets(N);
  for (auto& [t0, t1] : meets) {
    ull h0, m0, h1, m1;
    char c;
    cin >> h0 >> c >> m0 >> h1 >> c >> m1;
    t0 = h0*60 + m0;
    t1 = h1*60 + m1;
  }

  auto ans = solve(meets);
  for (ull i : ans) {
    cout << i + 1 << ' ';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
