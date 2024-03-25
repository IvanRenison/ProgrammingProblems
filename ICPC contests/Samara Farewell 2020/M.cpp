// https://codeforces.com/gym/102916/problem/M

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;


vu solve(const vuu& edges) {
  ull n = edges.size() + 1;
  if (n == 1) {
    return {0};
  }

  vector<vuu> adj(n);

  fore(e, 0, n - 1) {
    auto [u, v] = edges[e];
    adj[u].push_back({v, e}), adj[v].push_back({u, e});
  }

  fore(i, 0, n) {
    if (adj[i].size() > 3) {
      return {};
    }
  }

  vector<vuu> dp_mM(n - 1, vuu(2, {inf, 0}));
  // min, max

  function<uu(ull, bool)> mM = [&](ull e, bool s) {
    auto& [m, M] = dp_mM[e][s];
    if (m != inf) {
      return uu{m, M};
    }

    auto [u, v] = edges[e];

    if (s) {
      swap(u, v);
    }

    m = min(m, u), M = max(M, u);

    for (auto [w, f] : adj[u]) {
      if (w != v) {
        auto [m_, M_] = mM(f, edges[f].second != u);
        m = min(m, m_), M = max(M, M_);
      }
    }

    return uu{m, M};
  };

  vector<vu> dp_anse(n - 1, vu(2, inf));

  function<bool(ull, bool)> ans_e = [&](ull e, bool s) {
    ull& ans = dp_anse[e][s];

    if (ans != inf) {
      return (bool)ans;
    }

    ans = false;

    auto [u, v] = edges[e];

    if (s) {
      swap(u, v);
    }

    if (adj[u].size() > 3) {
      ans = false;
    } else if (adj[u].size() == 3) {
      ull w, x, ew, ex;
      fore(i, 0, 3) {
        if (v == adj[u][i].first) {
          tie(w, ew) = adj[u][(i + 1) % 3];
          tie(x, ex) = adj[u][(i + 2) % 3];
          break;
        }
      }

      if (x < u && u < w) {
        swap(x, w), swap(ex, ew);
      }
      if (w < u && u < x) {
        if (ans_e(ew, edges[ew].first == u) && ans_e(ex, edges[ex].first == u)) {
          auto [wm, wM] = mM(ew, edges[ew].first == u);
          auto [xm, xM] = mM(ex, edges[ex].first == u);

          if (v < u) {
            ans = v < wm && wM < u && u < xm;
          } else {
            ans = wM < u && u < xm && xM < v;
          }
        }
      }
    } else if (adj[u].size() == 2) {
      auto [w, ew] = adj[u][adj[u][0].first == v];
      if (ans_e(ew, edges[ew].first == u)) {
        auto [wm, wM] = mM(ew, edges[ew].first == u);
        if (v < u) {
          if (w < u) {
            ans = v < wm && wM < u;
          } else {
            ans = u < wm;
          }
        } else {
          if (w < u) {
            ans = wM < u;
          } else {
            ans = u < wm && wM < v;
          }
        }
      }
    } else if (adj[u].size() == 1) {
      ans = true;
    }

    return (bool)ans;
  };


  vu ans;

  fore(u, 0, n) {
    if (adj[u].size() == 2) {
      auto [v, ev] = adj[u][0];
      auto [w, ew] = adj[u][1];
      if (w < u && u < v) {
        swap(v, w), swap(ev, ew);
      }
      if (v < u && u < w) {
        if (ans_e(ev, edges[ev].first == u) && ans_e(ew, edges[ew].first == u)) {
          auto [vm, vM] = mM(ev, edges[ev].first == u);
          auto [wm, wM] = mM(ew, edges[ew].first == u);
          if (vM < u && u < wM) {
            ans.push_back(u);
          }
        }
      }
    } else if (adj[u].size() == 1) {
      auto [v, ev] = adj[u][0];
      if (ans_e(ev, edges[ev].first == u)) {
        auto [vm, vM] = mM(ev, edges[ev].first == u);
        if (v < u && vM < u) {
          ans.push_back(u);
        } else if (u < v && u < vm) {
          ans.push_back(u);
        }
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;
  vuu edges(n - 1);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  auto ans = solve(edges);
  if (ans.empty()) {
    cout << -1;
  } else {
    for (ull a : ans) {
      cout << a + 1 << ' ';
    }
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
