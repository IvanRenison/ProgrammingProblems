// https://codeforces.com/contest/1538/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve1(ull l, ull r, vector<ull> as) {
  ull n = as.size();

  sort(as.begin(), as.end());

  ull min_j = n;
  ull top_j = n;

  ull ans = 0;

  fore(i, 0, n) {
    if (top_j + 1 <= i) {
      break;
    }

    if (min_j < i + 1) {
      min_j = i + 1;
    }

    ull a_i = as[i];

    while (min_j > i + 1 && a_i + as[min_j - 1] >= l) {
      min_j--;
    }

    while (top_j > 0 && a_i + as[top_j - 1] > r) {
      top_j--;
    }

    if (top_j > min_j) {
      ans += top_j - min_j;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    ull n, l, r;
    cin >> n >> l >> r;

    vector<ull> as(n);
    fore(i, 0, n) {
      cin >> as[i];
    }
    cout << solve1(l, r, as) << "\n";
  }

  return EXIT_SUCCESS;
}
