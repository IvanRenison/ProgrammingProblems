// https://codeforces.com/contest/1833/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> parse1(void) {
  ull n;
  cin >> n;

  vector<ull> as(n);
  fore(i, 0, n) {
    ull a;
    cin >> a;
    as[i] = a - 1;
  }

  return as;
}

typedef ull Vertex;
typedef tuple<Vertex, Vertex> Edge;

struct Graph {
  ull n;
  vector<vector<Vertex>> adj;

  Graph(vector<ull> as) {
    this->n = as.size();
    this->adj = vector<vector<Vertex>>(n);
    fore(i, 0, n) {
      adj[i].push_back(as[i]);
      adj[as[i]].push_back(i);
    }
  }
};

vector<vector<Vertex>> dfs(Graph g) {
  vector<vector<Vertex>> ans;
  vector<bool> visited(g.n, false);

  fore(i, 0, g.n) {
    if (!visited[i]) {
      vector<Vertex> component = {i};
      vector<Vertex> stack = {i};
      visited[i] = true;

      while (!stack.empty()) {
        Vertex u = stack.back();
        stack.pop_back();

        for (Vertex v : g.adj[u]) {
          if (!visited[v]) {
            visited[v] = true;
            component.push_back(v);
            stack.push_back(v);
          }
        }
      }

      ans.push_back(component);
    }
  }

  return ans;
}

pair<ull, ull> solve1(vector<ull> as) {
  Graph g(as);

  vector<vector<Vertex>> components = dfs(g);

  ull max_amount = components.size();

  ull min_amount = 0;
  bool passed_by_uncomplete = false;

  for (vector<Vertex> component : components) {
    if (component.size() == 2) {
      passed_by_uncomplete = true;
      continue;
    }

    bool is_complete = true;
    for (Vertex u : component) {
      if (g.adj[u].size() != 2) {
        is_complete = false;
        break;
      }
    }

    if (is_complete) {
      min_amount += 1;
    } else {
      passed_by_uncomplete = true;
    }
  }

  if (passed_by_uncomplete) {
    min_amount += 1;
  }

  return {min_amount, max_amount};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto x = parse1();
    auto ans = solve1(x);
    cout << ans.first << ' ' << ans.second << '\n';
  }

  return EXIT_SUCCESS;
}
