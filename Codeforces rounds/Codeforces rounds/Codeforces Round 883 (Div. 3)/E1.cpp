// https://codeforces.com/contest/1846/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#define MAXN ull(1e6 + 1)

/*

  n = (c^i - 1)/(c - 1)

  nc - n = c^i - 1

  n(c - 1) + 1 = c^i


*/

vector<bool> valid(MAXN, false);

void init(void) {
  fore(i, 2, MAXN) {
    for (ull pot = i * i, x = 1 + i + i * i; x < MAXN; pot *= i, x += pot) {
      valid[x] = true;
    }
  }
}

bool solve1(ull n) {
  return valid[n];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  init();

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;

    if (solve1(n)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
