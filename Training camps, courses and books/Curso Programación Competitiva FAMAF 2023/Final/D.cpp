// https://codeforces.com/group/id8eYTCwzg/contest/447739/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> parse1(void) {
  ull n;
  cin >> n;
  vector<ull> as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }

  return as;
}

optional<ull> solve1(vector<ull> as) {
  ull n = as.size();
  ull count = 0;
  for (ull i = n - 2; i < n; i--) {
    while (as[i] >= as[i + 1]) {
      if (as[i] == 0) {
        return {};
      }
      as[i] /= 2;
      count++;
    }
  }
  return count;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    vector<ull> x = parse1();
    optional<ull> ans = solve1(x);
    if (ans.has_value()) {
      cout << *ans << "\n";
    } else {
      cout << "-1\n";
    }
  }

  return EXIT_SUCCESS;
}
