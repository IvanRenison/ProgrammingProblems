// https://codeforces.com/group/4zVk9dZl6Q/contest/390678/problem/K
#include <bits/stdc++.h>
#define fst first
#define snd second
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; ++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define mset(a, v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

#define MAX ull(1e9)

ull query(pair<ull, ull> p) {
  auto [x, y] = p;
  cout << x << ' ' << y << endl;
  string s;
  cin >> s;
  if (s[0] == 'b') {
    return 0;
  } else {
    return 1;
  }
}

pair<pair<ull, ull>, pair<ull, ull>> solve(ull n) {

  ull querys = 0;

  ull lower = 0;
  ull c_lower = query({0, 0});
  querys++;

  if (n == 1) {
    return {{MAX, 0}, {0, MAX}};
  }

  ull upper = MAX;

  while (querys < n) {
    ull m = (lower + upper) / 2;
    ull c_m = query({m, 0});
    querys++;
    if (c_m == c_lower) {
      lower = m;
    } else {
      upper = m;
    }
  }

  return {{lower + 1, 1}, {lower + 2, 3}};
}

int main() {
  FIN;

  ull n;
  cin >> n;

  auto [p1, p2] = solve(n);
  cout << p1.first << ' ' << p1.second << ' ' << p2.first << ' ' << p2.second
       << endl;

  return 0;
}
