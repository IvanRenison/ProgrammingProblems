// https://atcoder.jp/contests/arc164/tasks/arc164_a

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

pair<ull, ull> parse1(void) {
  ull a, b;
  cin >> a >> b;
  return {a, b};
}

bool solve1(ull N, ull K) {
  vector<ull> base3;
  while (N > 0) {
    base3.push_back(N % 3);
    N /= 3;
  }

  ull sum = 0;
  for (auto& i : base3) {
    sum += i;
  }

  return sum <= K && (K - sum) % 2 == 0;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [N, K] = parse1();
    if (solve1(N, K)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
