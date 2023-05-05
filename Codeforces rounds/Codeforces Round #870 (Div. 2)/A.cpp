// https://codeforces.com/contest/1826/problem/0

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> parse1(void) {
  ull n;
  cin >> n;

  vector<ull> ls(n);

  fore(i, 0, n) {
    cin >> ls[i];
  }

  return ls;
}

bool possible_to_have_x_liars(vector<ull> ls, ull x) {
  ull liars = 0;
  for(ull l : ls) {
    if (l > x) {
      liars++;
    }
  }

  return liars == x;
}

optional<ull> solve1(vector<ull> ls) {
  ull n = ls.size();

  fore(i, 0, n) {
    if (possible_to_have_x_liars(ls, i)) {
      return i;
    }
  }

  return {};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    optional<ull> ans = solve1(parse1());
    if (ans.has_value()) {
      cout << ans.value() << "\n";
    } else {
      cout << "-1\n";
    }
  }

  return EXIT_SUCCESS;
}
