// https://codeforces.com/contest/1829/problem/G

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#define N 1000000

ull parse1(void) {
  ull n;
  cin >> n;
  return n;
}

ull coords[N + 1][2];
ull values[N + 1];

void init(void) {
  // Initialize coords
  coords[0][0] = 0;
  coords[0][1] = 0;
  coords[1][0] = 0;
  coords[1][1] = 0;
  {
    ull i = 2;
    fore(y, 1, N + 1) {
      fore(x, 0, y + 1) {
        coords[i][0] = x;
        coords[i][1] = y;
        i++;
        if (i == N + 1) {
          break;
        }
      }
      if (i == N + 1) {
        break;
      }
    }
  }
  // Initialize values
  values[1] = 1;

  fore(i, 2, N + 1) {
    ull x = coords[i][0];
    ull y = coords[i][1];

    // Calculate parents
    vector<ull> parents;
    if (x < y) {
      parents.push_back(i - y);
    }
    if (x > 0) {
      parents.push_back(i - y - 1);
    }

    // Calculate central grandparent
    optional<ull> central_grandparent;
    if (0 < x && x < y) {
      central_grandparent = {i - 2 * y};
    }

    // Count value
    values[i] = i * i;

    for (ull p : parents) {
      values[i] += values[p];
    }
    if (central_grandparent.has_value()) {
      values[i] -= values[central_grandparent.value()];
    }
  }
}

ull solve1(ull n) {
  return values[n];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  init();

  ull t;

  cin >> t;

  fore(i, 0, t) {
    cout << solve1(parse1()) << "\n";
  }

  return EXIT_SUCCESS;
}
