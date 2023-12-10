// https://codeforces.com/group/id8eYTCwzg/contest/437948/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

bool solve(vector<pair<ull, ull>> abs) {
  ull n = abs.size();
  sort(abs.begin(), abs.end());

  vector<ull> max_b_prefixes(n + 1);
  max_b_prefixes[0] = 0;
  fore(i, 1, n + 1) {
    max_b_prefixes[i] = max(max_b_prefixes[i - 1], abs[i - 1].second);
  }

  fore(i, 0, n) {
    if (abs[i].second < max_b_prefixes[i]) {
      return true;
    }
  }

  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;

  vector<pair<ull, ull>> abs(n);

  fore(i, 0, n) {
    ull a, b;
    cin >> a >> b;
    abs[i] = {a, b};
  }

  if (solve(abs)) {
    cout << "Happy Alex\n";
  } else {
    cout << "Poor Alex\n";
  }

  return EXIT_SUCCESS;
}
