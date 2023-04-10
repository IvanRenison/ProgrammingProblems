//

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

pair<vector<ull>, vector<pair<ull, ull>>> parse1(void) {
  ull n, m;
  cin >> n >> m;
  vector<ull> a(n);
  vector<pair<ull, ull>> b(m);
  fore(i, 0, n) {
    cin >> a[i];
  }
  fore(i, 0, m) {
    ull v, w;
    cin >> v >> w;
    b[i] = {v - 1, w - 1};
  }
  return {a, b};
}

bool solve1(vector<ull> weights, vector<pair<ull, ull>> edges) {
  ull n = weights.size();

  vector<vector<ull>> neighbors(n);

  for (auto [v, w] : edges) {
    neighbors[v].push_back(w);
    neighbors[w].push_back(v);
  }

  vector<bool> visited(n, false);

  fore(i, 0, n) {
    if (visited[i] || weights[i] != 0) {
      continue;
    }

    vector<bool> visited_vertexes(n, false);
    visited_vertexes[i] = true;
    ull vertexes_count = 1;
    set<pair<ull, ull>> vertexes_to_visit;
    for (auto v : neighbors[i]) {
      vertexes_to_visit.insert({weights[v], v});
    }

    while (!vertexes_to_visit.empty()) {

      // Get min weight vertex
      auto [weight, v] = *vertexes_to_visit.begin();
      vertexes_to_visit.erase(vertexes_to_visit.begin());

      if (weight > vertexes_count) {
        break;
      }

      visited[v] = true;
      visited_vertexes[v] = true;
      vertexes_count++;

      for (auto w : neighbors[v]) {
        if (!visited_vertexes[w]) {
          vertexes_to_visit.insert({weights[w], w});
        }
      }
    }

    if (vertexes_count == n) {
      return true;
    }
  }


  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [a, b] = parse1();
    if (solve1(a, b)) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }

  return EXIT_SUCCESS;
}
