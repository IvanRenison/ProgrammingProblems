// https://codeforces.com/contest/1870/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

ll solve1(ull n, ull k, ull x) {
  if (x + 1 < k || n < k) {
    return -1;
  }
  if (x == k) {
    x--;
  }
  ull ans = 0;

  fore(i, 0, k) {
    if (i != k) {
      ans += i;
    }
  }
  fore(i, k+1, n+1) {
    ans += x;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {

    ull n, k, x;
    cin >> n >> k >> x;

    auto ans = solve1(n, k, x);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
