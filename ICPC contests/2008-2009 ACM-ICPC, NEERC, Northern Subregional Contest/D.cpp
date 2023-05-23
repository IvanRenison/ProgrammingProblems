#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve(vector<ull> as, vector<ull> bs) {

  map<ull, ull> bs_amounts;

  for (ull b : bs) {
    bs_amounts[b]++;
  }

  vector<ull> divisors(1e6 + 1);

  for (auto it : bs_amounts) {
    ull b = it.first;
    ull i = it.second;

    for (ull db = b; db <= 1e6; db += b) {
      divisors[db] += i;
    }
  }

  ull ans = 0;
  for (ull a : as) {
    ans += divisors[a];
  }

  return ans;
}

int main(void) {

  // Open file deposits.in
  freopen("deposits.in", "r", stdin);

  ull n;
  cin >> n;

  vector<ull> as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }

  ull m;
  cin >> m;

  vector<ull> bs(m);

  fore(i, 0, m) {
    cin >> bs[i];
  }

  // Open file deposits.out
  freopen("deposits.out", "w", stdout);

  cout << solve(as, bs) << '\n';

  return EXIT_SUCCESS;
}
