// https://codeforces.com/problemset/problem/433/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> solve(vector<ull> vs, vector<tuple<ull, ull, ull>> qs) {
  ull n = vs.size();
  ull m = qs.size();

  vector<ull> vs_sums(n + 1);
  vs_sums[0] = 0;
  fore(i, 1, n + 1) {
    vs_sums[i] = vs_sums[i - 1] + vs[i - 1];
  }

  vector<ull> vs_sorted = vs;
  sort(vs_sorted.begin(), vs_sorted.end());

  vector<ull> vs_sorted_sums(n + 1);
  vs_sorted_sums[0] = 0;
  fore(i, 1, n + 1) {
    vs_sorted_sums[i] = vs_sorted_sums[i - 1] + vs_sorted[i - 1];
  }

  vector<ull> ans(m);

  fore(i, 0, m) {
    ull t, l, r;
    tie(t, l, r) = qs[i];

    if (t == 1) {
      ans[i] = vs_sums[r] - vs_sums[l - 1];
    } else {
      ans[i] = vs_sorted_sums[r] - vs_sorted_sums[l - 1];
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;

  vector<ull> vs(n);

  fore(i, 0, n) {
    cin >> vs[i];
  }

  ull m;
  cin >> m;

  vector<tuple<ull, ull, ull>> qs;

  fore(i, 0, m) {
    ull t, l, r;
    cin >> t >> l >> r;
    qs.push_back(make_tuple(t, l, r));
  }

  vector<ull> ans = solve(vs, qs);

  fore(i, 0, m) {
    cout << ans[i] << "\n";
  }

  return EXIT_SUCCESS;
}
