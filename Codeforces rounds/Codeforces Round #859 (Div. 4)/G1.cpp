// https://codeforces.com/contest/1807/problem/G1

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)
#define CMAX 5001

vector<ull> parse1(void) {
  ull n;
  cin >> n;
  vector<ull> cs(n);
  for (ull& c : cs) {
    cin >> c;
  }
  return cs;
}

bool solve1(vector<ull>& cs) {
  ull n = cs.size();
  sort(cs.begin(), cs.end());

  if (cs[0] != 1) {
    return false;
  }

  vector<bool> available(CMAX, false);

  available[1] = true;

  fore(i, 1, n) {
    ull c = cs[i];

    if (!available[c]) {
      return false;
    }

    for (ull j = CMAX - 1 - c; j >= 1; j--) {
      if (available[j]) {
        available[j + c] = true;
      }
    }
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto x = parse1();
    if (solve1(x)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
