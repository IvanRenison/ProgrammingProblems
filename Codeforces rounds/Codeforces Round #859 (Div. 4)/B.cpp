// https://codeforces.com/contest/1807/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> parse1(void) {
  ull n;
  cin >> n;

  vector<ull> as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }

  return as;
}

bool solve1(vector<ull> as) {

  ull sum_evens = 0, sum_odds = 0;
  fore(i, 0, as.size()) {
    if (as[i] % 2 == 0) {
      sum_evens += as[i];
    } else {
      sum_odds += as[i];
    }
  }

  return sum_evens > sum_odds;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto x = parse1();
    if (solve1(x)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
