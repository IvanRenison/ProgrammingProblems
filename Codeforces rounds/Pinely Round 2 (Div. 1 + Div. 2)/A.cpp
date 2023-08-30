// https://codeforces.com/contest/1863/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

ull solve1(ull n, ull a, string s) {
  ull now = a, total = a, M = a;
  for (char c : s) {
    if (c == '+') {
      now++;
      total++;
      M = max(M, now);
    } else {
      now--;
    }
  }

  if (M == n) {
    return 2;
  } else if (total >= n) {
    return 1;
  } else {
    return 0;
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, a, q;
    cin >> n >> a >> q;
    string s;
    cin >> s;

    auto ans = solve1(n, a, s);
    if (ans == 0) {
      cout << "NO\n";
    } else if (ans == 1) {
      cout << "MAYBE\n";
    } else {
      cout << "YES\n";
    }
  }

  return EXIT_SUCCESS;
}
