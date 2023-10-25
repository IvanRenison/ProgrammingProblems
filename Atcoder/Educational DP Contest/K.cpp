// https://atcoder.jp/contests/dp/tasks/dp_k

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)


bool solve(ull K, vu as) {
  vector<bool> dp(K + 1);

  dp[0] = false;
  fore(i, 1, K + 1) {
    bool found_loser = false;

    for(ull a : as) {
      if (a <= i && !dp[i - a]) {
        found_loser = true;
        break;
      }
    }

    dp[i] = found_loser;
  }

  return dp[K];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, K;
  cin >> N >> K;
  vu as(N);
  for(ull& a : as) {
    cin >> a;
  }

  if (solve(K, as)) {
    cout << "First\n";
  } else {
    cout << "Second\n";
  }

  return EXIT_SUCCESS;
}
