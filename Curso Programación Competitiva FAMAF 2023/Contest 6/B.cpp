// https://codeforces.com/group/id8eYTCwzg/contest/447738/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

tuple<ull, ull, ull> parse1(void) {
  ull a, b, n;
  cin >> a >> b >> n;
  return {a, b, n};
}

/*
0 → a
1 → b
2 → a + b
3 → a + 2b
4 →   + 3b
5 → 3a + 5b
6 → 5a + 8b
7 →   + 13b
8 → a
9 → a

*/



ull solve1(ull a, ull b, ull n) {
  return (n % 3 == 1 ? 0ull : a) ^ (n % 3 == 0 ? 0ull : b);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [a, b, n] = parse1();
    auto ans = solve1(a, b, n);
    cout << ans << "\n";
  }

  return EXIT_SUCCESS;
}
