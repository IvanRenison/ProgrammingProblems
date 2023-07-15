// https://atcoder.jp/contests/abc310/tasks/abc310_e

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve(vector<bool> as) {
  ull N = as.size();
  ull ans = as[0] ? 1 : 0;

  ull amount_1 = as[0] ? 1 : 0;

  fore(i, 1, N) {
    if (!as[i]) {
      ans += i;
      amount_1 = i;
    } else {
      ans++;
      ans += i - amount_1;
      amount_1 = i - amount_1 + 1;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vector<bool> as(N);
  fore(i, 0, N) {
    char a;
    cin >> a;
    as[i] = a == '1';
  }

  auto ans = solve(as);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
