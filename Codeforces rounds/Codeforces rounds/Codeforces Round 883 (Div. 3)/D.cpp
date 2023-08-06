// https://codeforces.com/contest/1846/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

double solve1(ull d, ull h, vector<ull> ys) {
  ull n = ys.size();

  double ans = (double)n * (double)d * (double)h / 2.0;

  fore(i, 0, n - 1) {
    ull y_diff = ys[i + 1] - ys[i];

    if (y_diff < h) {
      double b =
          (double)d - (double)d / ((double)h) * (double)y_diff;
      ans -= b * (double)(h - y_diff) / 2.0;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  cout << setprecision(10);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, d, h;
    cin >> n >> d >> h;
    vector<ull> ys(n);
    for (ull& y : ys) {
      cin >> y;
    }

    auto ans = solve1(d, h, ys);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
