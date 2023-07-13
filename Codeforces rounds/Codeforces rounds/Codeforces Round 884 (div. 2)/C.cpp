// https://codeforces.com/contest/1844/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ll> parse1(void) {
  ull n;
  cin >> n;
  vector<ll> cs(n);
  fore(i, 0, n) {
    cin >> cs[i];
  }
  return cs;
}

ll solve1(vector<ll> cs) {
  ull n = cs.size();
  ll max_c = cs[0];
  ll sum_evens = 0, sum_odds = 0;
  fore(i, 0, n) {
    if (cs[i] > 0) {
      if (i % 2 == 0) {
        sum_evens += cs[i];
      } else {
        sum_odds += cs[i];
      }
    }
    max_c = max(max_c, cs[i]);
  }

  if (max_c < 0) {
    return max_c;
  } else {
    return max(sum_evens, sum_odds);
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto x = parse1();
    auto ans = solve1(x);
    cout << ans << "\n";
  }

  return EXIT_SUCCESS;
}
