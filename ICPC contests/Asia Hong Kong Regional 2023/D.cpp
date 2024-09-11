// https://codeforces.com/gym/104172/problem/D
#include <bits/stdc++.h>
#define ALL(x) x.begin(), x.end()
#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; ++i)
using namespace std;
typedef unsigned int uint;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;
typedef vector<uu> vuu;
typedef pair<uint, bool> ub;
typedef vector<ub> vib;
typedef tuple<uint, uint, uint> uuu;
typedef vector<uuu> vuuu;
typedef tuple<uint, uint, bool> uub;
typedef vector<uub> vuub;
typedef vector<bool> vb;

const uint inf = 1 << 30;

vu topoSort(const vector<vib>& gr) {
  vu indeg(gr.size()), ret;
  ret.reserve(gr.size());
  for (auto& li : gr) for (auto [x, _] : li) indeg[x]++;
  queue<uint> q; // use priority_queue for lexic. largest ans.
  fore(i,0,gr.size()) if (indeg[i] == 0) q.push(i);
  while (!q.empty()) {
    uint i = q.front(); // top() for priority queue
    ret.push_back(i);
    q.pop();
    for (auto [x, _] : gr[i])
      if (--indeg[x] == 0) q.push(x);
  }
  return ret;
}

/*
Line that passes through (x0, y0) and (x2, y2):
y = y0 + (y2 - y0) / (x2 - x0) * (x - x0)
*/

bool out(uint x0, uint y0, uint x1, uint y1, uint x2, uint y2) {
  uint y_num = y0 * (x2 - x0) + (y2 - y0) * (x1 - x0);
  uint y_den = x2 - x0;
  return y_num > y1 * y_den;
}


void add(map<uint, uint>& m, uint x, uint y) {
  auto it = m.lower_bound(x);
  bool m_count = it != m.end() && it->first == x;
  if (m_count && it->second <= y) {
    return;
  }

  bool added = false;
  if (!m_count) {
    if (it == m.end() || it == m.begin()) {
      it = m.insert_or_assign(x, y).first;
      added = true;
    } else {
      auto [x0, y0] = *prev(it);
      auto [x2, y2] = *it;
      if (out(x0, y0, x, y, x2, y2)) {
        it = m.insert_or_assign(x, y).first;
        added = true;
      }
    }
  } else {
    it = m.insert_or_assign(x, y).first;
    added = true;
  }

  if (added) {
    if (it != m.end()) {
      auto it1 = next(it);
      if (it1 != m.end()) {
        auto it2 = next(it1);
        while (it2 != m.end()) {
          auto [x0, y0] = *it;
          auto [x1, y1] = *it1;
          auto [x2, y2] = *it2;

          if (!out(x0, y0, x1, y1, x2, y2)) {
            it1 = m.erase(it1);
            it2 = next(it1);
          } else {
            break;
          }
        }
      }
    }

    if (it != m.begin()) {
      auto it1 = prev(it);
      while (it1 != m.begin()) {
        auto it0 = prev(it1);
        auto [x0, y0] = *it0;
        auto [x1, y1] = *it1;
        auto [x2, y2] = *it;
        if (!out(x0, y0, x1, y1, x2, y2)) {
          it1 = prev(m.erase(it1));
        } else {
          break;
        }
      }
    }

    while (m.size() > 2) {
      auto it1 = prev(m.end());
      auto it0 = prev(it1);

      auto [x0, y0] = *it0;
      auto [x1, y1] = *it1;

      if (y0 <= y1) {
        m.erase(it1);
      } else {
        break;
      }
    }
  }

}

vu solve(uint n, const vuub& edges, const vuuu& queries) {
  uint q = queries.size();

  vector<vib> adj(n);
  for (auto [u, v, c] : edges) {
    adj[u].push_back({v, c});
  }

  vu ord = topoSort(adj);
  assert(ord[0] == 0);

  vector<map<uint, uint>> dp(n);
  // dp[u][x] = min amount of ones with x zeros

  dp[0][0] = 0;

  for (uint u : ord) {
    for (auto [v, c] : adj[u]) {
      for (auto [x, y] : dp[u]) {
        if (c) {
          add(dp[v], x, y + 1);
        } else {
          add(dp[v], x + 1, y);
        }
      }
    }
  }

  vu ans;
  ans.reserve(q);
  for (auto [a, b, u] : queries) {
    uint this_ans = inf;
    for (auto [x, y] : dp[u]) {
      uint cost = x * a + y * b;
      if (cost < this_ans) {
        this_ans = cost;
      } else {
        break;
      }
    }
    ans.push_back(this_ans);
  }

  return ans;
}

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

vu force(uint n, const vuub& edges, const vuuu& queries) {
  vector<vib> adj(n);
  for (auto [u, v, c] : edges) {
    adj[u].push_back({v, c});
  }

  vu ans;
  for (auto [a, b, u] : queries) {
    rpriority_queue<uu> pq;
    pq.push({0, 0});
    vb vis(n);

    uint this_ans = inf;

    while (!pq.empty()) {
      auto [d, v] = pq.top();
      pq.pop();

      if (vis[v]) {
        continue;
      }
      vis[v] = true;

      if (v == u) {
        this_ans = d;
        break;
      }

      for (auto [w, c] : adj[v]) {
        if (!vis[w]) {
          pq.push({d + (c ? b : a), w});
        }
      }
    }

    assert(this_ans != inf);

    ans.push_back(this_ans);
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

#ifndef TEST
  uint n, m;
  cin >> n >> m;

  vuub edges(m);
  for (auto& [u, v, c] : edges) {
    cin >> u >> v >> c;
    u--, v--;
  }

  uint q;
  cin >> q;
  vuuu queries(q);
  for (auto& [a, b, x] : queries) {
    cin >> a >> b >> x;
    x--;
  }

  vu ans = solve(n, edges, queries);
  for (uint x : ans) {
    cout << x << '\n';
  }
#else
  fore(_, 0, 100000) {
    uint n = rand() % 5 + 2;
    uint m = rand() % 5 + 1;
    set<uu> edges;
    fore(i, 0, n - 1) {
      edges.insert({i, i + 1});
    }
    fore(_, 0, m) {
      uint u = rand() % (n - 1) + 1;
      uint v = rand() % u;
      edges.insert({v, u});
    }

    vuub edges_;
    for (auto [u, v] : edges) {
      edges_.push_back({u, v, rand() % 2});
    }

    uint q = 1;
    vuuu queries;
    fore(_, 0, q) {
      queries.push_back({rand() % 10 + 1, rand() % 10 + 1, rand() % n});
    }

    vu ans = solve(n, edges_, queries);
    vu ans2 = force(n, edges_, queries);

    if (ans != ans2) {
      cout << "FAIL" << endl;
      cout << n << ' ' << edges_.size() << endl;
      for (auto [u, v, c] : edges_) {
        cout << u + 1 << ' ' << v + 1 << ' ' << c << endl;
      }
      cout << q << endl;
      for (auto [a, b, x] : queries) {
        cout << a << ' ' << b << ' ' << x + 1 << endl;
      }
      cout << "GOT" << endl;
      for (uint x : ans) {
        cout << x << ' ';
      }
      cout << endl;
      cout << "EXPECTED" << endl;
      for (uint x : ans2) {
        cout << x << ' ';
      }
      cout << endl;
      return 1;
    }
  }
#endif
}
