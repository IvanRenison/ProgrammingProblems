// https://codeforces.com/gym/104441/problem/1

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef pair<uint, uint> uu;

uu solve(uint N, uint M, uint S, uint P) {
  uint m = N * M;
  uint s = N * S + (N - 1) * P;

  m += s / 60;
  s %= 60;

  return {m, s};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  uint N, M, S, P;
  cin >> N >> M >> S >> P;

  auto [m, s] = solve(N, M, S, P);
  cout << m << '\n' << s << '\n';

  return EXIT_SUCCESS;
}
