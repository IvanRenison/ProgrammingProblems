// https://codeforces.com/gym/104869/problem/H

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()

const ull inf = 1ull << 60;

pair<ull, vuu> L(ull n, const vuu& edges) {
  ull m = edges.size();

  vector<vuu> adj(n);
  fore(e, 0, m) {
    auto [u, v] = edges[e];
    adj[u].push_back({v, e}), adj[v].push_back({u, e});
  }

  set<uu> ans;
  fore(e, 0, m) {
    auto [ue, ve] = edges[e];

    vu us = {ue, ve};

    for (ull u : us) {
      for (auto [v, f] : adj[u]) {
        if (f != e) {
          ans.insert(minmax(e, f));
        }
      }
    }
  }

  vuu ans_v(ALL(ans));

  return {m, ans_v};
}

ull nextM(ull n, const vuu& edges) {
  vu deg(n);
  for (auto [u, v] : edges) {
    deg[u]++, deg[v]++;
  }

  ull ans = 0;

  fore(i, 0, n) {
    ans += deg[i] * (deg[i] - 1) / 2;
  }

  return ans;
}

ull force(ull n, vuu edges, ull k) {
  ull ans = n;
  bool inc = false;
  fore(_, 0, k - 1) {
    ull new_n;
    tie(new_n, edges) = L(n, edges);
    if (new_n < n) {
      assert(!inc);
    } else if (new_n > n) {
      inc = true;
    }
    ans = min(ans, new_n);
    n = new_n;
    if (n > 1000) {
      return inf;
    }

 /*    cout << "_ = " << _ << endl;
    cout << n << edges.size() << endl;
    for (auto [u, v] : edges) {
      cout << u << ' ' << v << endl;
    } */
  }

  return ans;
}


optional<ull> borderCase(ull n, const vuu& edges, ull k) {
  vector<vu> adj(n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v), adj[v].push_back(u);
  }

  vb vis(n, false);
  ull ans = n;

  fore(u, 0, n) {
    if (adj[u].size() > 2) {
      if (adj[u].size() == 3) {
        vis[u] = true;
        for (ull v : adj[u]) {
          if (adj[v].size() != 1) {
            return {};
          }
          vis[v] = true;
        }
        ans -= 1;
      } else {
        return {};
      }
    }
  }

  vu chains;


  fore(i, 0, n) {
    if (!vis[i]) {
      vis[i] = true;

      vuu s;
      for (ull u : adj[i]) {
        s.push_back({u, i});
        vis[u] = true;
      }

      bool is_chain = true;
      ull sz = 1;

      while (!s.empty()) {
        auto [u, p] = s.back();
        s.pop_back();

        sz++;

        for (ull v : adj[u]) {
          if (v != p) {
            if (vis[v]) {
              is_chain = false;
            } else {
              s.push_back({v, u});
              vis[v] = true;
            }
          }
        }
      }

      if (is_chain) {
        chains.push_back(sz);
      }
    }
  }


  for (ull sz : chains) {
    if (sz > k - 1) {
      ans -= k - 1;
    } else {
      ans -= sz;
    }
  }

  //cerr << "borderCase\n";

  return ans;
}

ull solve(ull n, vuu edges, ull k) {
  if (k == 1) {
    return n;
  }

  auto ans_o = borderCase(n, edges, k);
  if (ans_o.has_value()) {
    return *ans_o;
  }

  ull ans = n;
  if (edges.size() > ans) {
    return ans;
  } else {
    ans = edges.size();
    if (nextM(n, edges) > ans) {
      return ans;
    }
  }
  fore(i, 0, k - 1) {
    tie(n, edges) = L(n, edges);
    if (n > ans) {
      return ans;
    }
    ans = n;
    if (edges.size() > ans) {
      return ans;
    } else if (i + 1 < k - 1) {
      ans = edges.size();
      if (nextM(n, edges) > ans) {
        return ans;
      }
    }
    //assert(i < 4);
  }
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef TEST
  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m, k;
    cin >> n >> m >> k;
    vuu edges(m);
    for (auto &[u, v] : edges) {
      cin >> u >> v;
      u--, v--;
    }

    auto ans = solve(n, edges, k);
    cout << ans << '\n';
  }

#else

  fore(_, 0, 10000) {
    ull n = rand() % 1000 + 1;
    ull m = rand() % 1001;
    set<uu> edges_set;

    while (m--) {
      ull u = rand() % n;
      ull v = rand() % n;
      if (u == v) {
        continue;
      }
      if (u > v) {
        swap(u, v);
      }
      edges_set.insert({u, v});
    }

    vuu edges(ALL(edges_set));

    ull k = rand() % 1000 + 1;
    cerr << "Test " << _ << endl;
    /* cout << "Test " << _ << '\n';
    cout << n << ' ' << edges.size() << ' ' << k << '\n';
    for (auto [u, v] : edges) {
      cout << u << ' ' << v << '\n';
    }
    cout << endl; */
    ull anss = solve(n, edges, k);
    // ull ansf = force(n, edges, k);
    // if (ansf != inf) {
    //   ull anss = solve(n, edges, k);
    //   if (ansf != anss) {
    //     cerr << "n = " << n << " " << edges.size() << " " << k << endl;
    //     for (auto [u, v] : edges) {
    //       cerr << u << ' ' << v << endl;
    //     }
    //     cerr << ansf << ' ' << anss << endl;
    //     return EXIT_FAILURE;
    //   }
    // }

  }
#endif

  return EXIT_SUCCESS;
}
/*




*/