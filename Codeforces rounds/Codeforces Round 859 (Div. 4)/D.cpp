// https://codeforces.com/contest/1807/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    ull n, q;
    cin >> n >> q;

    vector<ull> as(n);
    fore(i, 0, n) {
      cin >> as[i];
    }

    vector<ull> prefix_sums(n + 1);
    prefix_sums[0] = 0;
    fore(i, 1, n + 1) {
      prefix_sums[i] = prefix_sums[i - 1] + as[i - 1];
    }

    fore(i, 0, q) {
      ull l, r, k;
      cin >> l >> r >> k;
      l--;
      r--;

      ull sum = prefix_sums[l] + (prefix_sums[n] - prefix_sums[r + 1]) +
                (r - l + 1) * k;
      if (sum % 2 == 1) {
        cout << "Yes\n";
      } else {
        cout << "No\n";
      }
    }
  }

  return EXIT_SUCCESS;
}
