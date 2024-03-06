// https://codeforces.com/gym/104441/problem/4

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

pair<bool, ull> solve(ull N, ull K) {
  ull steps = 0;
  while (true) {
    if (K % 3 == 0) {
      steps += K;
      return {true, steps};
    } else if (K % 3 == 1) {
      steps += K;
      return {false, steps};
    } else {
      steps += (N / 3) * 3;
      K = K / 3 + N % 3;
      N = N / 3 + N % 3;
    }
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N, K;
  cin >> N >> K;
  K--; // Index from 0

  auto [b, i] = solve(N, K);
  if (b) {
    cout << "Yes\n" << i + 1 << '\n';
  } else {
    cout << "No\n" << i + 1 << '\n';
  }

  return EXIT_SUCCESS;
}
