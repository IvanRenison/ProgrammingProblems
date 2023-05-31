// https://cses.fi/problemset/task/1082

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#define MAXX ull(1e6)

array<ull, MAXX + 1> divisors;
void eratosthenesSieve(void) {
  for (ull i = 1; i <= MAXX; i++) {
    divisors[i] = i;
  }

  for (ull i = 4; i <= MAXX; i += 2) {
    divisors[i] = 2;
  }

  for (ull i = 3; i * i <= MAXX; i += 2) {
    if (divisors[i] == i) {
      for (ull j = i * i; j <= MAXX; j += i * 2) {
        if (divisors[j] == j) {
          divisors[j] = i;
        }
      }
    }
  }
}

array<optional<ull>, MAXX + 1> dp;

ull number_of_divisors(ull x) {
  if (dp[x].has_value()) {
    return dp[x].value();
  }

  ull y = x;

  ull div = divisors[y];
  ull count = 0;

  while (divisors[y] == div) {
    y /= div;
    count++;
  }

  ull ans = (count + 1) * number_of_divisors(y);
  dp[x] = ans;
  return ans;
}

vector<ull> solve(vector<ull>& xs) {
  ull n = xs.size();
  vector<ull> ans(n);

  fore(i, 0, n) {
    ans[i] = number_of_divisors(xs[i]);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  eratosthenesSieve();
  dp[0] = 0;
  dp[1] = 1;

  ull n;
  cin >> n;

  vector<ull> xs(n);
  fore(i, 0, n) {
    cin >> xs[i];
  }

  vector<ull> ans = solve(xs);
  fore(i, 0, ans.size()) {
    cout << ans[i] << '\n';
  }

  return EXIT_SUCCESS;
}
