// https://codeforces.com/group/hzSLIARNBN/contest/464702/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define INF (1ull << 60)

vector<ull> topoSort(const vector<vector<ull>>& gr) {
	vector<ull> indeg(gr.size()), ret;
	for (auto& li : gr) for (ull x : li) indeg[x]++;
	queue<ull> q; // use priority_queue for lexic. largest ans.
	fore(i,0,gr.size()) if (indeg[i] == 0) q.push(i);
	while (!q.empty()) {
		ull i = q.front(); // top() for priority queue
		ret.push_back(i);
		q.pop();
		for (ull x : gr[i])
			if (--indeg[x] == 0) q.push(x);
	}
	return ret;
}

typedef tuple<ull, ull, ull> Edge;

/* Returns toposort */
optional<vector<ull>> try_for(ull k, ull n, const vector<Edge>& edges) {

  vector<vector<ull>> adj(n);
  for(auto [u, v, c] : edges) {
    if (c > k) {
      adj[u].push_back(v);
    }
  }

  vector<ull> order = topoSort(adj);
  if (order.size() < n) {
    return {};
  } else {
    return order;
  }
}

pair<ull, vector<ull>> find_k(ull n, const vector<Edge>& edges) {
  ull lower = 0, upper = 0;
  for(auto [u, v, c] : edges) {
    upper = max(upper, c);
  }

  auto _order = try_for(lower, n, edges);
  if (_order.has_value()) {
    return {lower, *_order};
  }

  _order = try_for(upper, n, edges);
  assert(_order.has_value());

  while (lower + 1 < upper) {
    ull m = (lower + upper) / 2;
    auto m_order = try_for(m, n, edges);
    if (m_order.has_value()) {
      upper = m;
      _order = m_order;
    } else {
      lower = m;
    }
  }

  return {upper, *_order};
}

pair<ull, vector<ull>> solve(ull n, const vector<Edge>& edges) {
  auto [k, order] = find_k(n, edges);

  vector<ull> inv_order(n);

  for(ull i = 0; i < n; i++) {
    inv_order[order[i]] = i;
  }

  vector<ull> ans;

  ull m = edges.size();

  fore(i, 0, m) {
    auto [u, v, c] = edges[i];

    if (inv_order[v] < inv_order[u]) {
      ans.push_back(i);
    }
  }

  return {k, ans};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, m;
  cin >> n >> m;

  vector<Edge> edges(m);
  for(auto& [u, v, c] : edges) {
    cin >> u >> v >> c;
    u--, v--;
  }

  auto [c, xs] = solve(n, edges);
  cout << c << ' ' << xs.size() << '\n';
  for(auto x : xs) {
    cout << x + 1 << ' ';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
