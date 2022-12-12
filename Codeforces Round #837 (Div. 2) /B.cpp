// https://codeforces.com/contest/1771/problem/B

#include <assert.h>
#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

struct edge {
  uint x, y;
};

static inline tuple<uint, vector<struct edge>> parse1(void) {
  uint n, m;
  cin >> n >> m;

  vector<struct edge> edges(m);
  for (uint i = 0; i < m; ++i) {
    uint x, y;
    cin >> x >> y;
    edges[i] = {x, y};
  }

  return {n, edges};
}

static inline uint solve1(uint n, vector<struct edge> edges) {

  map<uint, set<uint>> adj;
  for (struct edge e : edges) {
    adj[e.x].insert(e.y);
    adj[e.y].insert(e.x);
  }

  uint res = 0;
  uint racha_starts_at = 1;
  for (uint i = 1; i <= n; i++) {
    set<uint> adj_i = adj[i];

    set<uint>::iterator start = adj_i.lower_bound(racha_starts_at);
    set<uint>::iterator end = adj_i.upper_bound(i-1);

    bool breaks_racha = start != end && start != adj_i.end();

    if (breaks_racha) {
      racha_starts_at = *prev(end) + 1;
    }

    res += i - racha_starts_at + 1;
  }

  return res;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  uint t;
  cin >> t;
  for (uint i = 0; i < t; ++i) {
    uint n;
    vector<struct edge> edges;
    tie(n, edges) = parse1();
    cout << solve1(n, edges) << "\n";
  }

  return EXIT_SUCCESS;
}
