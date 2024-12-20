// https://codeforces.com/gym/100851

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

vector<vu> findCycles(const vector<vu>& adj) {
  ull n = adj.size();

  vector<vu> ans;

  vb vis(n, false);
  vector<set<ull>> cycle_added(n);
  vu par(n, inf);

  function<void(ull)> dfs = [&](ull u) {
    vis[u] = true;
    for (ull v : adj[u]) if (!cycle_added[u].count(v)) {
      if (!vis[v]) {
        par[v] = u;
        dfs(v);
      } else if (v != par[u]) {
        vu cycle;
        for (ull x = u; x != v; x = par[x]) {
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

struct Cactus {
  ull head; // Id of head node
  vector<Cactus> children;
  vector<vector<Cactus>> cycles;
};

pair<Cactus, vector<vu>> constructCactus(vector<vu>& adj) {
  ull n = adj.size();

  vector<vu> cycles = findCycles(adj);
  vector<vu> cycles_per_node(n);
  fore(i, 0, cycles.size()) {
    for (ull u : cycles[i]) {
      cycles_per_node[u].push_back(i);
    }
  }

  vb vis(n, false);
  vb cycle_vis(cycles.size(), false);

  function<void(Cactus&)> dfs = [&](Cactus& t) {
    ull u = t.head;
    //assert(vis[u]);

    for (ull i : cycles_per_node[u]) if (!cycle_vis[i]) {
      cycle_vis[i] = true;
      t.cycles.push_back({});
      //assert(!cycles[i].empty());
      ull j = 0;
      while (cycles[i][j] != u) j++;
      //assert(cycles[i][j] == u);
      ull sz = cycles[i].size();
      fore(k, 1, sz) {
        ull v = cycles[i][(j + k) % sz];
        //assert(!vis[v]);
        vis[v] = true;
      }
      fore(k, 1, sz) {
        ull v = cycles[i][(j + k) % sz];
        t.cycles.back().push_back({v, {}, {}});
        dfs(t.cycles.back().back());
      }
    }

    for (ull v : adj[u]) {
      if (!vis[v]) {
        vis[v] = true;
        t.children.push_back({v, {}, {}});
        dfs(t.children.back());
      }
    }
  };

  Cactus ans = {0, {}, {}};
  vis[0] = true;
  dfs(ans);

  return {ans, cycles};
}

// {ans, number of nodes, tree size}
uu solve(Cactus& cactus, const vu& tree_szs, ull total_trees_ans) {
  ull n = tree_szs.size();

  ull n_children = cactus.children.size();
  ull n_cycles = cactus.cycles.size();

  vuu childrens_ans(n_children);
  vector<vuu> cycles_ans(n_cycles);

  ull ans = 0, tam =  1;

  fore(i, 0, n_children) {
    childrens_ans[i] = solve(cactus.children[i], tree_szs, total_trees_ans);
    ans += childrens_ans[i].first;
    tam += childrens_ans[i].second;
  }
  fore(i, 0, n_cycles) {
    ull k = cactus.cycles[i].size();
    cycles_ans[i] = vuu(k);
    fore(j, 0, k) {
      cycles_ans[i][j] = solve(cactus.cycles[i][j], tree_szs, total_trees_ans);
      ans += cycles_ans[i][j].first;
      tam += cycles_ans[i][j].second;
    }
  }

  fore(i, 0, n_children) {
    ull in_tam = childrens_ans[i].second;
    ull out_tam = n - in_tam;
    ans += in_tam * out_tam;
  }

  fore(i, 0, n_cycles) {
    ull k = cycles_ans[i].size();

    ull this_ans = total_trees_ans;

    ull total_tree_szs = tree_szs[cactus.head];
    this_ans -= total_tree_szs * (total_tree_szs - 1) / 2 - (total_tree_szs - 1);
    fore(j, 0, k) {
      ull this_sz = tree_szs[cactus.cycles[i][j].head];
      this_ans -= this_sz * (this_sz - 1) / 2 - (this_sz - 1);
      total_tree_szs += this_sz;
    }

    this_ans += total_tree_szs * (total_tree_szs - 1) / 2 - (total_tree_szs - 1);

    ans += this_ans * (k + 1);
  }

  return {ans, tam};
}

ull solve(ull n, vuu& edges) {
  vector<vu> adj(n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v), adj[v].push_back(u);
  }

  auto [cactus, cycles] = constructCactus(adj);

  set<uu> cycles_edges;
  for (vu& cycle : cycles) {
    ull k = cycle.size();
    fore(i, 0, k) {
      cycles_edges.insert(minmax(cycle[i], cycle[(i + 1) % k]));
    }
  }

  vu tree_szs(n, inf);
  ull trees_ans = 0;
  fore(u, 0, n) if (tree_szs[u] == inf) {
    tree_szs[u] = 0;
    vu q = {u};
    for (ull i = 0; i < q.size(); i++) {
      ull v = q[i];
      for (ull w : adj[v]) if (tree_szs[w] == inf && !cycles_edges.count(minmax(v, w))) {
        tree_szs[w] = 0;
        q.push_back(w);
      }
    }
    for (ull v : q) {
      tree_szs[v] = q.size();
    }
    trees_ans += q.size() * (q.size() - 1) / 2 - (q.size() - 1);
  }

  auto [ans, _] = solve(cactus, tree_szs, trees_ans);

  ans -= edges.size();

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef ONLINE_JUDGE
    freopen("cactus.in", "r",stdin);
    freopen("cactus.out","w",stdout);
#endif

  ull n, paths;
  cin >> n >> paths;
  vuu edges;
  while (paths--) {
    ull k;
    cin >> k;
    vu path(k);
    for (ull& u : path) {
      cin >> u;
      u--;
    }
    fore(i, 0, k - 1) {
      edges.push_back({path[i], path[i + 1]});
    }
  }

  ull ans = solve(n, edges);
  cout << ans << '\n';
}
