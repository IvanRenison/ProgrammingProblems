// https://atcoder.jp/contests/abc301/tasks/abc301_d

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

optional<ull> solve(vector<optional<bool>> ds, ull N) {
  ull n = ds.size();

  reverse(ds.begin(), ds.end());

  ull value = 0;

  fore(i, 0, n) {
    optional<bool> d = ds[i];
    if (d.has_value()) {
      value += d.value() * (1ULL << i);
    }
  }

  if (value > N) {
    return {};
  }
  if (value == N) {
    return {N};
  }

  fore(i_, 0, n) {
    ull i = n - i_ - 1;
    optional<bool> d = ds[i];
    if (!d.has_value()) {
      if (value + (1ULL << i) <= N) {
        value += (1ULL << i);
      }
    }
  }

  return value;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string ss;
  cin >> ss;
  ull N;
  cin >> N;

  ull n = ss.size();

  vector<optional<bool>> ds(n);
  fore(i, 0, n) {
    char s = ss[i];
    if (s == '?') {
      ds[i] = {};
    } else {
      ds[i] = {s == '1'};
    }
  }

  optional<ull> ans = solve(ds, N);

  if (ans.has_value()) {
    cout << ans.value() << "\n";
  } else {
    cout << "-1\n";
  }

  return EXIT_SUCCESS;
}
