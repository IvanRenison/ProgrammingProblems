// https://codeforces.com/group/id8eYTCwzg/contest/442745/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

typedef ull Vertex;
typedef tuple<Vertex, Vertex> Edge;

class Graph {
public:
  ull n;
  ull m;
  vector<Edge> edges;
  vector<vector<Vertex>> adj;

  Graph(ull n, vector<Edge> edges) {
    this->n = n;
    this->m = edges.size();
    this->edges = edges;
    this->adj = vector<vector<Vertex>>(n);
    for (auto [u, v] : edges) {
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }
};



ull solve(vector<optional<ull>> ps) {
  ull n = ps.size();

  vector<vector<ull>> hs(n);
  vector<ull> next_level;

  fore(i, 0, n) {
    optional<ull> p = ps[i];
    if (p.has_value()) {
      hs[p.value()].push_back(i);
    } else {
      next_level.push_back(i);
    }
  }

  ull ans = 0;
  while (!next_level.empty()) {
    vector<ull> this_level = next_level;
    next_level = {};

    for(ull p : this_level) {
      for(ull q : hs[p]) {
        next_level.push_back(q);
      }
    }

    ans++;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;

  vector<optional<ull>> ps(n);

  fore(i, 0, n) {
    ll p;
    cin >> p;
    if (p == -1) {
      ps[i] = {};
    } else {
      ps[i] = (ull)(p-1);
    }
  }

  cout << solve(ps) << endl;

  return EXIT_SUCCESS;
}
