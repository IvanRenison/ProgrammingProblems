// https://codeforces.com/gym/101309

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;
typedef vector<uu> vuu;
typedef vector<bool> vb;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()

const uint inf = 1u << 30;

optional<vu> partCycle(uint k, const vu& vals) {
  uint n = vals.size();
  vu vals_sum(n + 1);
  partial_sum(ALL(vals), vals_sum.begin() + 1);

  auto sum = [&](uint i, uint j) -> uint {
    return vals_sum[j] - vals_sum[i];
  };

  if (sum(0, n) < k) {
    return {vu{}};
  }

  vu ps(n, inf); // ps[i] = j ⇔ sum(i, j) = k

  fore(i, 0, n) {
    if (sum(i, n) < k) break;
    uint l = i, r = n;
    while (l + 1 < r) {
      uint m = (l + r) / 2;
      if (sum(i, m) >= k) {
        r = m;
      } else {
        l = m;
      }
    }

    if (sum(i, r) == k) {
      ps[i] = r;
    }
  }

  vu last = ps;
  for (uint i = n; i--; ) {
    if (last[i] < n && last[last[i]] != inf) {
      last[i] = last[last[i]];
    }
  }

  fore(i, 0, n) {
    if (last[i] != inf && sum(0, i) + sum(last[i], n) < k) { // We found an answer
      vu ans;
      while (i != inf) {
        ans.push_back(i);
        if (i == n) break;
        i = ps[i];
      }
      //assert(ans.size() >= 2);
      return ans;
    }
  }

  return {};
}

vector<vu> findCycles(const vector<vu>& adj) {
  uint n = adj.size();

  vector<vu> ans;

  vb vis(n, false);
  vector<set<uint>> cycle_added(n);
  vu par(n, inf);

  function<void(uint)> dfs = [&](uint u) {
    vis[u] = true;
    for (uint v : adj[u]) if (!cycle_added[u].count(v)) {
      if (!vis[v]) {
        par[v] = u;
        dfs(v);
      } else if (v != par[u]) {
        vu cycle;
        for (uint x = u; x != v; x = par[x]) {
          //assert(x != inf);
          cycle.push_back(x);
        }
        cycle.push_back(v);
        cycle_added[v].insert(u);
        ans.push_back(move(cycle));
      }
    }
  };

  dfs(0);
  //fore(u, 0, n) {
  //  //assert(vis[u]);
  //}

  return ans;
}

struct Tree {
  uint head; // Id of head node
  vector<Tree> children;
  vector<vector<Tree>> cycles;
};

Tree constructTree(uint n, const vuu& edges) {
  vector<vu> adj(n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v), adj[v].push_back(u);
  }

  vector<vu> cycles = findCycles(adj);
  vector<vu> cycles_per_node(n);
  fore(i, 0, cycles.size()) {
    for (uint u : cycles[i]) {
      cycles_per_node[u].push_back(i);
    }
  }

  vb vis(n, false);
  vb cycle_vis(cycles.size(), false);

  function<void(Tree&)> dfs = [&](Tree& t) {
    uint u = t.head;
    //assert(vis[u]);

    for (uint i : cycles_per_node[u]) if (!cycle_vis[i]) {
      cycle_vis[i] = true;
      t.cycles.push_back({});
      //assert(!cycles[i].empty());
      uint j = 0;
      while (cycles[i][j] != u) j++;
      //assert(cycles[i][j] == u);
      uint sz = cycles[i].size();
      fore(k, 1, sz) {
        uint v = cycles[i][(j + k) % sz];
        //assert(!vis[v]);
        vis[v] = true;
      }
      fore(k, 1, sz) {
        uint v = cycles[i][(j + k) % sz];
        t.cycles.back().push_back({v, {}, {}});
        dfs(t.cycles.back().back());
      }
    }

    for (uint v : adj[u]) {
      if (!vis[v]) {
        vis[v] = true;
        t.children.push_back({v, {}, {}});
        dfs(t.children.back());
      }
    }
  };

  Tree ans = {0, {}, {}};
  vis[0] = true;
  dfs(ans);

  return ans;
}

optional<vector<vu>> solve(uint n, uint k, const vuu& edges) {

  Tree t = constructTree(n, edges);

  vector<vu> ans;

  function<optional<vu>(Tree&)> part = [&](Tree& t) -> optional<vu> {
    vu extra;

    for (vector<Tree>& cycle : t.cycles) {
      uint sz = cycle.size();
      vector<vu> rec(sz);

      fore(i, 0, sz) {
        optional<vu> res = part(cycle[i]);
        if (!res.has_value()) {
          return {};
        }
        rec[i] = *res;
        rec[i].push_back(cycle[i].head);
      }

      vu vals(sz);
      fore(i, 0, sz) {
        vals[i] = rec[i].size();
      }

      optional<vu> part_cycle = partCycle(k, vals);
      if (!part_cycle.has_value()) {
        return {};
      }
      if (part_cycle->empty()) {
        fore(i, 0, sz) {
          for (uint u : rec[i]) {
            extra.push_back(u);
          }
        }
      } else {
        uint n_part = part_cycle->size() - 1;
        fore(j, 0, n_part) {
          ans.push_back({});
          fore(i, (*part_cycle)[j], (*part_cycle)[j + 1]) {
            for (uint u : rec[i]) {
              ans.back().push_back(u);
            }
          }
        }
        fore(i, 0, (*part_cycle)[0]) {
          for (uint u : rec[i]) {
            extra.push_back(u);
          }
        }
        fore(i, part_cycle->back(), sz) {
          for (uint u : rec[i]) {
            extra.push_back(u);
          }
        }
      }
    }

    for (Tree& child : t.children) {
      optional<vu> res = part(child);
      if (!res.has_value()) {
        return {};
      }
      if (res->size() == k - 1) {
        ans.push_back({});
        for (uint u : *res) {
          ans.back().push_back(u);
        }
        ans.back().push_back(child.head);
      } else {
        for (uint u : *res) {
          extra.push_back(u);
        }
        extra.push_back(child.head);
      }
    }

    if (extra.size() >= k) {
      return {};
    }

    return extra;
  };

  optional<vu> extra = part(t);

  if (!extra.has_value()) {
    return {};
  }

  if (extra->size() >= k || extra->size() + 1 < k) {
    return {};
  }

  ans.push_back(*extra);
  ans.back().push_back(t.head);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef ONLINE_JUDGE
  freopen("cactus.in", "r", stdin);
  freopen("cactus.out", "w", stdout);
#endif

#ifndef TEST
  uint n, m, k;
  cin >> n >> m >> k;
  vuu edges;
  fore(i, 0, m) {
    uint s;
    cin >> s;
    vu path(s);
    for (uint& u : path) {
      cin >> u;
      u--;
    }
    fore(i, 0, s - 1) {
      edges.push_back({path[i], path[i + 1]});
    }
  }

/*   for (auto [u, v] : edges) {
    cerr << u << ' ' << v << '\n';
  } */

  auto ans = solve(n, n / k, edges);

  if (ans.has_value()) {
    for (vu& comp : *ans) {
      sort(ALL(comp));
      for (uint u : comp) {
        cout << u + 1 << ' ';
      }
      cout << '\n';
    }
  } else {
    cout << "-1\n";
  }

#else
  fore(_, 0, 100000) {
    uint n = 1;
    vuu edges;

    uint t = rand() % 3;
    while (t--) {
      uint u = rand() % n;

      bool ty = rand() % 2;
      if (ty) { // Colgar nodo
        edges.push_back({u, n});
        n++;
      } else { // Colgar ciclo
        uint s = rand() % 3 + 2;
        edges.push_back({u, n});
        edges.push_back({u, n + s - 1});
        fore(i, 0, s - 1) {
          edges.push_back({n + i, n + i + 1});
        }
        n += s;
      }
    }

    uint k = n / (rand() % n + 1);

    cout << n << ' ' << edges.size() << ' ' << k << '\n';
    for (auto [u, v] : edges) {
      cout << "2 " << u + 1 << ' ' << v + 1 << '\n';
    }
    cout << endl;

    solve(n, k, edges);
  }
#endif
}
