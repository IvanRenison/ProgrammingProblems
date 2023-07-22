// https://codeforces.com/contest/1646/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve1(ull n, ull s) {
  return s / (n*n);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, s;
    cin >> n >> s;

    auto ans = solve1(n, s);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
