// https://cses.fi/problemset/task/1091/

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint n, m;
  cin >> n >> m;

  multiset<uint, greater<uint>> tickets;
  while (n--) {
    uint h;
    cin >> h;
    tickets.insert(h);
  }

  while (m--) {
    uint t;
    cin >> t;
    auto it = tickets.lower_bound(t);

    if (it == tickets.end()) {
      cout << "-1\n";
    } else {
      cout << *it << '\n';
      tickets.erase(it);
    }
  }

  return EXIT_SUCCESS;
}
