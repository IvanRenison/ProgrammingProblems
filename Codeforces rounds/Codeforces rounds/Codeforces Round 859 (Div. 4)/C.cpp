// https://codeforces.com/contest/1807/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<char> parse1(void) {
  ull n;
  cin >> n;

  vector<char> s(n);

  fore(i, 0, n) {
    cin >> s[i];
  }

  return s;
}

bool solve1(vector<char> s) {
  ull n = s.size();

  array<optional<bool>, ('z' - 'a' + 1)> asigns;
  vector<bool> ns(n);

  ns[0] = true;
  asigns[s[0] - 'a'] = true;

  fore(i, 1, n) {
    char c = s[i];
    if (asigns[c - 'a'].has_value()) {
      ns[i] = asigns[c - 'a'].value();
    } else {
      ns[i] = !ns[i - 1];
      asigns[c - 'a'] = ns[i];
    }

    if (ns[i] == ns[i - 1]) {
      return false;
    }
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

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
