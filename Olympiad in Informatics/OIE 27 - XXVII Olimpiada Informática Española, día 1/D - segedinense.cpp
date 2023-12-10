// https://codeforces.com/gym/104604

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

bool solve1(ull a, ull b) {

  if (a == b) {
    return a % 2 == 0;
  }

  if (b > a) {
    swap(a, b);
  }

  // b min, a max

  if (b % (a - b) != 0) {
    return false;
  }

  for(ull x : vu{a/2, a/3, a/4}) {
    ull y = b - x;
    if (x != 0 && y != 0 && a % x == 0 && a % y == 0) {
      return true;
    }
  }

  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull T;
  cin >> T;

  fore(i, 0, T) {
    ull a, b;
    cin >> a >> b;

    if (solve1(a, b)) {
      cout << "SI\n";
    } else {
      cout << "NO\n";
    }
  }

  return EXIT_SUCCESS;
}
