// https://codeforces.com/contest/1771/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int uint;


static inline tuple<uint, vector<pair<uint, uint>>> parse1(void) {
  uint n, m;
  cin >> n >> m;

  vector<pair<uint, uint>> edges(m);
  for (uint i = 0; i < m; ++i) {
    uint x, y;
    cin >> x >> y;
    edges[i] = {x, y};
  }

  return {n, edges};
}

static inline uint solve1(uint n, vector<pair<uint, uint>> edges) {
  map<uint, uint> adjacent_backwards = {};
  vector<bool> have_backwards_neighbour(n);
  for (uint i = 0; i < n; i ++) {
    have_backwards_neighbour[i] = false;
  }

  for (pair<uint, uint> edge : edges) {
    uint x = edge.first - 1;
    uint y = edge.second - 1;
    uint max_xy = max(x, y);
    uint min_xy = min(x, y);

    if (adjacent_backwards.find(max_xy) == adjacent_backwards.end()) {
      adjacent_backwards[max_xy] = min_xy;
    } else {
      adjacent_backwards[max_xy] = max(adjacent_backwards[max_xy], min_xy);
    }
    // adjacent_backwards[max_xy] = max(adjacent_backwards[max_xy], min_xy);
    have_backwards_neighbour[max_xy] = true;
  }

  uint res = 0;

  uint good_from = 0;
  for (uint i = 0; i < n; i ++) {
    if (have_backwards_neighbour[i]) {
      good_from = max(good_from, adjacent_backwards[i] + 1);
    }
    res += i - good_from + 1;
  }

  return res;
  /*
  sum i = 1 to n : n - i + 1

  */
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  uint t;
  cin >> t;
  for (uint i = 0; i < t; ++i) {

    uint n;
    vector<pair<uint, uint>> edges;
    tie(n, edges) = parse1();
    cout << solve1(n, edges) << endl;
  }

  return EXIT_SUCCESS;
}
