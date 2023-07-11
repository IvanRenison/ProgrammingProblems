// https://codeforces.com/contest/1844/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

pair<ull, ull> parse1(void) {
  ull n, m;
  cin >> n >> m;
  return {n, m};
}

ull solve1(ull a, ull b) {
  return a + b;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [a,b] = parse1();
    auto ans = solve1(a,b);
    cout << ans << "\n";
  }

  return EXIT_SUCCESS;
}
