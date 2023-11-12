// https://codeforces.com/gym/104252/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

typedef ull Vertex;
typedef tuple<Vertex, Vertex> Edge;

struct DirectedGraph {
  ull n;
  ull m;
  vector<Edge> edges;
  vector<vector<Vertex>> adj_fordward;
  vector<vector<Vertex>> adj_backward;

  DirectedGraph(ull n, vector<Edge> edges)
      : n(n), m(edges.size()), edges(edges), adj_fordward(n), adj_backward(n) {
    for (auto [u, v] : edges) {
      adj_fordward[u].push_back(v);
      adj_backward[v].push_back(u);
    }
  }
};

vector<bool> backwards_dfs(DirectedGraph& G, ull s, ull p) {
  vector<bool> visited(G.n, false);
  visited[s] = true;

  vector<ull> stack = {s};
  while (!stack.empty()) {
    ull u = stack.back();
    stack.pop_back();

    for (auto v : G.adj_backward[u]) {
      if (v != p && !visited[v]) {
        visited[v] = true;
        stack.push_back(v);
      }
    }
  }

  return visited;
}

bool have_common(vector<bool>& a, vector<bool>& b, vector<bool>& c) {
  ull N = a.size();
  fore(i, 0, N) {
    if (a[i] && b[i] && c[i]) {
      return true;
    }
  }

  return false;
}

vector<bool> solve(vector<pair<ull, ull>> XYs) {
  ull N = XYs.size();

  vector<Edge> edges;
  fore(i, 0, N) {
    auto [X, Y] = XYs[i];
    edges.push_back({i, X});
    edges.push_back({i, Y});
  }

  DirectedGraph G(N, edges);

  vector<bool> ans(N);
  fore(i, 0, N) {
    auto [X, Y] = XYs[i];
    vector<bool> back_i = backwards_dfs(G, i, i),
                 back_X = backwards_dfs(G, X, i),
                 back_Y = backwards_dfs(G, Y, i);
    ans[i] = have_common(back_i, back_X, back_Y);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vector<pair<ull, ull>> XYs(N);
  for (auto& [X, Y] : XYs) {
    cin >> X >> Y;
    X--, Y--;
  }

  vector<bool> ans = solve(XYs);

  fore(i, 0, N) {
    cout << (ans[i] ? "Y" : "N");
  }

  cout << '\n';

  return EXIT_SUCCESS;
}
