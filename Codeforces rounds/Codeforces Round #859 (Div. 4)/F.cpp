// https://codeforces.com/contest/1807/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

typedef ull D;
#define DR 0b11
#define DL 0b10
#define UR 0b01
#define UL 0b00

optional<ull> solve1(ull n, ull m, ull i0, ull j0, ull i1, ull j1, D d) {
  vector<vector<array<bool, 4>>> states_passed(n, vector<array<bool, 4>>(m));
  ull bounces_count = 0;

  while (i0 != i1 || j0 != j1) {
    if (states_passed[i0][j0][d]) {
      return {};
    }

    states_passed[i0][j0][d] = true;

    bool bounced = false;
    if (i0 == 0 && (d & 0b10) == 0) {
      d |= 0b10;
      bounced = true;
    } else if (i0 == n - 1 && (d & 0b10) != 0) {
      d &= 0b01;
      bounced = true;
    }
    if (j0 == 0 && (d & 0b01) == 0) {
      d |= 0b01;
      bounced = true;
    } else if (j0 == m - 1 && (d & 0b01) != 0) {
      d &= 0b10;
      bounced = true;
    }

    if (bounced) {
      bounces_count++;
    }

    i0 += ((d & 0b10) != 0) ? 1 : -1;
    j0 += ((d & 0b01) != 0) ? 1 : -1;
  }

  return bounces_count;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    ull n, m, i0, j0, i1, j1;
    string s;
    cin >> n >> m >> i0 >> j0 >> i1 >> j1 >> s;
    D d = s == "DR" ? DR : s == "DL" ? DL : s == "UR" ? UR : UL;
    optional<ull> ans = solve1(n, m, i0 - 1, j0 - 1, i1 - 1, j1 - 1, d);
    if (ans.has_value()) {
      cout << ans.value() << '\n';
    } else {
      cout << "-1\n";
    }
  }

  return EXIT_SUCCESS;
}
