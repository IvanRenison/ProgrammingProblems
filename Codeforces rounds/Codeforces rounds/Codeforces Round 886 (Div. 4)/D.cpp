// https://codeforces.com/contest/1850/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve1(ull k, vector<ull> as) {
  ull n = as.size();
  sort(as.begin(), as.end());

  ull max_size = 1, actual_ans = 1;
  fore(i, 1, n) {
    if (as[i] - as[i - 1] <= k) {
      actual_ans++;
    } else {
      actual_ans = 1;
    }
    max_size = max(max_size, actual_ans);
  }

  return n - max_size;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, k;
    cin >> n >> k;
    vector<ull> as(n);
    fore(j, 0, n) {
      cin >> as[j];
    }

    auto ans = solve1(k, as);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
