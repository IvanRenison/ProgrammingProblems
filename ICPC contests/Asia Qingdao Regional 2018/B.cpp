// https://codeforces.com/gym/104270/problem/B

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

//#pragma GCC optimize("O3")

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;
typedef vector<uu> vuu;
typedef vector<int> vi;
typedef vector<unsigned long long> vb;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()

const uint inf = 1 << 30;

vb BCC(uint n, const vuu& edges) { // Return bridges
  uint m = edges.size();
  vu num(n), st;
  vector<vector<uu>> ed(n);
  uint Time = 0;

  uint eid = 0;
  for (auto [a, b] : edges) {
    ed[a].emplace_back(b, eid);
    ed[b].emplace_back(a, eid++);
  }

  vb ans(m, true);

  function<uint(uint, uint)> dfs = [&](uint at, uint par){
    uint me = num[at] = ++Time, top = me;
    for (auto [y, e] : ed[at]) if (e != par) {
      if (y == at) {
        ans[e] = false;
      } else if (num[y]) {
        top = min(top, num[y]);
        if (num[y] < me)
          st.push_back(e);
      } else {
        uint si = st.size();
        uint up = dfs(y, e);
        top = min(top, up);
        if (up == me) {
          st.push_back(e);
          {
            //vu comp(st.begin() + si, st.end());
            //for (uint e : comp) {
            fore(i, si, st.size()) {
              uint e = st[i];
              ans[e] = false;
            }
          }
          st.resize(si);
        }
        else if (up < me) st.push_back(e);
        else { /* e is a bridge */ }
      }
    }
    return top;
  };

  fore(i, 0, n) if (!num[i]) {
    dfs(i, inf);
  }

  return ans;
};

/** Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: O(\alpha(N))$
 */
struct UF {
  vi e;
  UF(int n) : e(n, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  int quickFind(int x) { return e[x] < 0 ? x : e[x]; }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b]; e[b] = a;
    return true;
  }
};

struct ModeCounter { // Count how many times the mode appears
  vu appears; // how many times each number appears
  vu count; // how many numbers appear i times
  uint modeCount;

  ModeCounter(uint a_lim, uint n_lim) : appears(a_lim), count(n_lim), modeCount(0) {}
  void insert(uint a) {
    if (appears[a] > 0) {
      count[appears[a]]--;
    }
    appears[a]++;
    count[appears[a]]++;

    modeCount = max(modeCount, appears[a]);
  }
  void erase(uint a) {
    assert(appears[a] > 0);
    if (count[appears[a]] == 1 && appears[a] == modeCount) {
      count[appears[a]] = 0;
      appears[a]--;
      if (appears[a] > 0) {
        count[appears[a]]++;
      }

      modeCount--;
    } else {
      count[appears[a]]--;
      appears[a]--;
      count[appears[a]]++;
    }
  }
};

pair<uint, vu> compress(const vu& xs) {
  uint n = xs.size();

  map<uint, vu> xs_map;
  fore(i, 0, n) {
    xs_map[xs[i]].push_back(i);
  }

  vu compressed_xs(n);

  uint i = 0;
  for (auto [x, ks] : xs_map) {
    for (uint k : ks) {
      compressed_xs[k] = i;
    }
    i++;
  }

  return {i - 1, compressed_xs};
}

uint max_a = 0;

pair<uint, vu> solveTree(const vector<vu>& as, const vuu& edges) {
  // Solve for a tree
  // Return ans with all edges and ans deleting each edge
  uint n = as.size(), m = edges.size();

  vector<vuu> adj(n);
  fore(e, 0, m) {
    auto [u, v] = edges[e];
    adj[u].push_back({v, e}), adj[v].push_back({u, e});
  }

  vu sub_tree_sizes(n);
  vu parent_edge(n);

  function<uint(uint, uint)> dfs_sub_tree_sizes = [&](uint u, uint p) {
    sub_tree_sizes[u] = as[u].size();
    for (auto [v, e] : adj[u]) if (v != p) {
      parent_edge[v] = e;
      sub_tree_sizes[u] += dfs_sub_tree_sizes(v, u);
    }
    return sub_tree_sizes[u];
  };

  uint total_sizes = dfs_sub_tree_sizes(0, inf);

/*   uint max_a = 0;
  for (auto& as_ : as) {
    for (uint a : as_) {
      max_a = max(max_a, a);
    }
  } */

  function<void(uint, uint, ModeCounter&)> fill = [&](uint u, uint p, ModeCounter& mc) {
    for (auto [v, _] : adj[u]) if (v != p) {
      fill(v, u, mc);
    }
    for (uint a : as[u]) {
      mc.insert(a);
    }
    /* vuu s = {{u, p}};
    while (!s.empty()) {
      auto [u, p] = s.back();
      s.pop_back();
      for (uint a : as[u]) {
        mc.insert(a);
      }
      for (auto [v, _] : adj[u]) if (v != p) {
        s.push_back({v, u});
      }
    } */
  };
  function<void(uint, uint, ModeCounter&)> empty = [&](uint u, uint p, ModeCounter& mc) {
    for (auto [v, _] : adj[u]) if (v != p) {
      empty(v, u, mc);
    }
    for (uint a : as[u]) {
      mc.erase(a);
    }
    /* vuu s = {{u, p}};
    while (!s.empty()) {
      auto [u, p] = s.back();
      s.pop_back();
      for (uint a : as[u]) {
        mc.erase(a);
      }
      for (auto [v, _] : adj[u]) if (v != p) {
        s.push_back({v, u});
      }
    } */
  };

  ModeCounter mc_outside(max_a + 1, total_sizes + 1);
  ModeCounter mc_inside(max_a + 1, total_sizes + 1);

  fore(u, 0, n) {
    for (uint a : as[u]) {
      mc_outside.insert(a);
    }
  }

  uint total_ans = mc_outside.modeCount;

  vu ans_edges(m);

  function<void(uint, uint)> dfs = [&](uint u, uint p) {

    vuu sizes_suns;

    for (auto [v, _] : adj[u]) if (v != p) {
      sizes_suns.push_back({sub_tree_sizes[v], v});
    }

    if (!sizes_suns.empty()) {
      sort(ALL(sizes_suns));

      fore(i, 0, sizes_suns.size()) {
        auto [_, v] = sizes_suns[i];

        dfs(v, u);

        if (i + 1 != sizes_suns.size()) {
          fill(v, u, mc_outside);
          empty(v, u, mc_inside);
        }
      }

      fore(i, 0, sizes_suns.size() - 1) {
        auto [_, v] = sizes_suns[i];

        if (i + 1 != sizes_suns.size()) {
          fill(v, u, mc_inside);
          empty(v, u, mc_outside);
        }
      }
    }

    for (uint a : as[u]) {
      mc_outside.erase(a);
      mc_inside.insert(a);
    }

    if (u != 0) {
      ans_edges[parent_edge[u]] = mc_outside.modeCount + mc_inside.modeCount;
    }
  };

  dfs(0, inf);

  return {total_ans, ans_edges};
}

pair<uint, vu> solveCon(vu& as, const vuu& edges) {
  // Solve for a connected graph
  // Return ans with all edges and ans deleting each edge
  uint n = as.size(), m = edges.size();

  tie(max_a, as) = compress(as);

  vb bridges = BCC(n, edges);

  UF uf(n);

  fore(e, 0, m) {
    if (!bridges[e]) {
      auto [u, v] = edges[e];
      uf.join(u, v);
    }
  }

  vu comps_ids(n, inf);
  uint n_ = 0;
  vector<vu> as_;
  as_.reserve(4096);
  fore(i, 0, n) {
    uint u = uf.find(i);
    if (comps_ids[u] == inf) {
      comps_ids[u] = n_;
      n_++;
      as_.push_back({as[i]});
    } else {
      as_[comps_ids[u]].push_back(as[i]);
    }
  }

  vuu edges_;
  vu edges_original_id;

  fore(e, 0, m) {
    if (bridges[e]) {
      auto [u, v] = edges[e];
      edges_.push_back({comps_ids[uf.quickFind(u)], comps_ids[uf.quickFind(v)]});
      edges_original_id.push_back(e);
    }
  }

  auto [ans_total, ans_edges_] = solveTree(as_, edges_);

  vu ans(m, ans_total);
  fore(e_, 0, edges_.size()) {
    ans[edges_original_id[e_]] = ans_edges_[e_];
  }

  return {ans_total, ans};
}


vu solve1(const vu& as, const vuu& edges) {
  uint n = as.size(), m = edges.size();

  vector<vuu> adj(n);
  fore(e, 0, m) {
    auto [u, v] = edges[e];
    adj[u].push_back({v, e}), adj[v].push_back({u, e});
  }

  vector<map<uint, uint>> new_nodess;

  vu comp(n, inf);
  fore(u, 0, n) if (comp[u] == inf) {
    uint comp_id = new_nodess.size();

    comp[u] = comp_id;

    map<uint, uint> new_nodes = {{u, 0}};

    vu stack = {u};

    while (!stack.empty()) {
      uint v = stack.back();
      stack.pop_back();

      for (auto [w, e] : adj[v]) {
        if (comp[w] == inf) {
          new_nodes[w] = new_nodes.size();
          comp[w] = comp_id;
          stack.push_back(w);
        }
      }
    }

    new_nodess.push_back(new_nodes);
  }

  uint n_comps = new_nodess.size();

  vector<vu> ass(n_comps);
  fore(i, 0, n_comps) {
    ass[i] = vu(new_nodess[i].size());
    for (auto [u, u_] : new_nodess[i]) {
      ass[i][u_] = as[u];
    }
  }

  vector<vuu> edgess(n_comps);
  vector<vu> edges_original_ids(n_comps);

  fore(e, 0, m) {
    auto [u, v] = edges[e];
    assert(comp[u] == comp[v]);
    edgess[comp[u]].push_back({new_nodess[comp[u]][u], new_nodess[comp[u]][v]});
    edges_original_ids[comp[u]].push_back(e);
  }

  uint total_base_ans = 0;
  vector<pair<uint, vu>> comps_ans(n_comps);
  fore(i, 0, n_comps) {
    comps_ans[i] = solveCon(ass[i], edgess[i]);

    total_base_ans += comps_ans[i].first;
  }

  vu ans(m);

  fore(i, 0, n_comps) {
    uint this_base_ans = total_base_ans - comps_ans[i].first;

    fore(e_, 0, edgess[i].size()) {
      ans[edges_original_ids[i][e_]] = this_base_ans + comps_ans[i].second[e_];
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  fore(i, 0, t) {
    uint n, m;
    cin >> n >> m;
    vu as(n);
    max_a = 0;
    for (uint& a : as) {
      cin >> a;
      max_a = max(max_a, a);
    }
    vuu edges(m);
    for (auto& [u, v] : edges) {
      cin >> u >> v;
      u--, v--;
    }

    vu ans = solve1(as, edges);
    fore(i, 0, m) {
      cout << ans[i] << (i + 1 == m ? '\n' : ' ');
    }
  }

  return EXIT_SUCCESS;
}
