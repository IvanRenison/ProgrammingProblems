// https://codeforces.com/contest/1844/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#define MAXN ull(2 * 1e5 + 1)

ull parse1(void) {
  ull n;
  cin >> n;
  return n;
}

vector<ull> solve1(ull n) {
  vector<ull> ans(n);

  if (n == 1) {
    ans[0] = 1;
  } else if (n == 2) {
    ans[0] = 1, ans[1] = 2;
  } else {
    ans[0] = 2, ans[n - 1] = 3, ans[n / 2] = 1;
    for (ull i = 1, x = 4; i < n - 1; i++) {
      if (i != n / 2) {
        ans[i] = x;
        x++;
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto x = parse1();
    auto ans = solve1(x);
    for (auto y : ans) {
      cout << y << " ";
    }
    cout << "\n";
  }

  return EXIT_SUCCESS;
}
