// https://codeforces.com/gym/103934/problem/M
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, efunca = b; i < efunca; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<pair<ll, ll>> vii;
typedef tuple<ll,ll,ll> iii;
typedef vector<iii> viii;

/** Author: Simon Lindholm
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: Finds all biconnected components in an undirected graph, and
 *  runs a callback for the edges in each. In a biconnected component there
 *  are at least two distinct paths between any two nodes. Note that a node can
 *  be in several components. An edge which is not in a component is a bridge,
 *  i.e., not part of any cycle.
 * Time: O(E + V)
 * Status: tested with library checker and with SPOJ EC_P
 */
auto BCC(ll n, const vector<ii>& edges) {
  ll Time = 0, eid = 0;
  vi num(n), st;
  vector<vector<ii>> adj(n);
  for (auto [a, b] : edges)
    adj[a].pb({b, eid}), adj[b].pb({a, eid++});

  ll nComps = 0; // number of biconnected components
  vi edgesComp(eid, -1); // comp of each edge or -1 if bridge
  vector<set<ll>> nodesComp(n); // comps of each node

  function<ll(ll, ll)> dfs = [&](ll at, ll par) {
    ll me = num[at] = ++Time, top = me;
    for (auto [y, e] : adj[at]) if (e != par) {
      if (y == at) { // self loop
        nodesComp[at].insert(edgesComp[e] = nComps++);
      } else if (num[y]) {
        top = min(top, num[y]);
        if (num[y] < me) st.pb(e);
      } else {
        ll si = SZ(st), up = dfs(y, e);
        top = min(top, up);
        if (up == me) {
          st.pb(e); // from si to SZ(st) we have a comp
          fore(i, si, SZ(st)) {
            edgesComp[st[i]] = nComps;
            auto [u, v] = edges[st[i]];
            nodesComp[u].insert(nComps);
            nodesComp[v].insert(nComps);
          }
          nComps++, st.resize(si);
        } else if (up < me) st.pb(e); // else e is bridge
      }
    }
    return top;
  };

  fore(u, 0, n) if (!num[u]) dfs(u, -1);
  fore(u, 0, n) if (nodesComp[u].empty())
    nodesComp[u].insert(nComps++);

  return tuple(nComps, edgesComp, nodesComp);
};

/** Author: Pietro Palombini
 * Date: 2024-07-06
 * License: CC0
 * Source: https://codeforces.com/blog/entry/124286
 * Description: define \texttt{Data}, \texttt{finalize},
 * \texttt{acc} (as explained below), adding any
 * necessary fields to \texttt{Reroot}. Then instantiate, add
 * the data, and call \texttt{reroot()}.
 *
 * \texttt{finalize} is applied before returning
 * answer for \texttt{p} if \texttt{g[p][ei]} was its
 * parent; usually identity function. When \texttt{p} is the
 * root, \texttt{ei} is -1.
 *
 * Let accumulated$(p, S) = a$ such that \texttt{finalize(a,
 * ...)} is the answer for p$ if S$ were its only children.
 * \texttt{acc} should, given accumulated$(p, S)$ and the
 * answer for \texttt{g[p][ei]}, compute
 * accumulated$(p,S\cup\{\texttt{g[p][ei]}})$ in
 * \texttt{p\_ans}.
 *
 * \texttt{neuts[p]} should be accumulated$(p, \varnothing)$.
 *
 * \texttt{root\_dp[v]} is the answer for the whole tree with
 * \texttt{v} as root, \texttt{fdp[v][ei]} is the answer for
 * \texttt{g[v][ei]} if \texttt{v} is the root and
 * \texttt{bdp[v][ei]} is the answer for \texttt{v} if
 * \texttt{g[v][ei]} is the root.
 *
 * Equivalent to the following code, but for all roots:
 *
 * \texttt{Data dfs(ll u, ll p) \{}
 *
 * \ \ \texttt{Data res = neuts[u];}
 *
 * \ \ \texttt{fore(ei, 0, SZ(g[u])) if (g[u][ei] != p)}
 *
 * \ \ \ \ \texttt{acc(res, dfs(g[u][ei], u), u, ei);}
 *
 * \ \ \texttt{ll pid = p == -1 ? -1 : find(ALL(g[u]), p) - begin(g[u]);}
 *
 * \ \ \texttt{return dp[u] = finalize(res, u, pid);}
 *
 * \texttt{}}
 * Time: Fast O(n \log n) assuming O(1) operations.
 * Status: stress-tested
 */
typedef iii Data; // Odd, even, my
typedef vector<Data> vd;

struct Reroot {
  ll n; vector<vi>& g; vd& neuts;
  vi vals;

  Data finalize(Data a, ll p, ll ei) {
    get<2>(a) = vals[p];
    return a;
  }
  void acc(Data& p_ans, const Data& child_ans, ll p, ll ei) {
    get<0>(p_ans) += get<1>(child_ans) + get<2>(child_ans);
    get<1>(p_ans) += get<0>(child_ans);
  }

  vd root_dp; vector<vd> fdp, bdp;
  Reroot(vector<vi>& g, vd& neuts, vi& vals_) : n(SZ(g)), g(g),
      neuts(neuts), vals(vals_), root_dp(n), fdp(n), bdp(n) {}
  void reroot() {
    if (n==1) { root_dp[0]=finalize(neuts[0], 0, -1); return; }
    vd dp = neuts, e(n); vi o = {0}, p(n); o.reserve(n);
    fore(i, 0, n) for (ll v : g[o[i]]) if (v != p[o[i]])
      p[v] = o[i], o.pb(v);
    for (ll u : views::reverse(o)) {
      ll pei = -1;
      fore(ei, 0, SZ(g[u]))
        if (g[u][ei] == p[u]) pei = ei;
        else acc(dp[u], dp[g[u][ei]], u, ei);
      dp[u] = finalize(dp[u], u, pei);
    }
    for (ll u : o) {
      dp[p[u]] = dp[u];
      fdp[u].reserve(SZ(g[u])), bdp[u].reserve(SZ(g[u]));
      for (ll v : g[u]) fdp[u].pb(dp[v]);
      ex(e, fdp[u], neuts[u], u);
      fore(i, 0, SZ(fdp[u])) bdp[u].pb(finalize(e[i], u, i));
      acc(e[0], fdp[u][0], u, 0);
      root_dp[u] = finalize(n > 1 ? e[0] : neuts[u], u, -1);
      fore(i, 0, SZ(g[u])) dp[g[u][i]] = bdp[u][i];
    }
  }
  void ex(vd& e, vd& a, Data& ne, ll v) {
    ll d = SZ(a); fill(begin(e), begin(e) + d, ne);
    for (ll b = bit_width((unsigned)d); b--;) {
      for (ll i = d; i--;) e[i] = e[i >> 1];
      fore(i, 0, d - (d & !b)) acc(e[(i >> b)^1], a[i], v, i);
    }
  }
};

ii solveTree(vi& vals, vii& edges) {
  ll N = vals.size();
  vector<vi> adj(N);
  for (auto [u, v] : edges) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vd neuts(N);
  fore(i, 0, N) {
    neuts[i] = {0, 0, 0};
  }

  Reroot rr(adj, neuts, vals);
  rr.reroot();

  ll ans_odd = 0, ans_even = 0;
  fore(i, 0, N) {
    auto [odd, even, my] = rr.root_dp[i];
    ans_odd += odd * my;
    ans_even += even * my;
  }

  assert(ans_odd % 2 == 0);
  assert(ans_even % 2 == 0);

  ans_odd /= 2;
  ans_even /= 2;

  return {ans_odd, ans_even};
}

ii solveForest(vi& vals, vii& edges) {
  ll N = vals.size();

  vector<vi> adj(N);
  for (auto [u, v] : edges) {
    adj[u].push_back(v), adj[v].push_back(u);
  }

  ll ans_odd = 0, ans_even = 0;

  vector<bool> vis(N, false);
  vi new_nodes(N);

  fore(u, 0, N) if (!vis[u]) {
    vi comp;
    vii comp_edges;
    vi s = {u};
    vis[u] = true;
    while (!s.empty()) {
      ll v = s.back();
      s.pop_back();
      comp.push_back(v);
      for (ll w : adj[v]) if (!vis[w]) {
        comp_edges.push_back({v, w});
        vis[w] = true;
        s.push_back(w);
      }
    }

    vi new_vals(comp.size());
    fore(i, 0, comp.size()) {
      new_nodes[comp[i]] = i;
      new_vals[i] = vals[comp[i]];
    }

    vii new_edges;
    for (auto [u, v] : comp_edges) {
      new_edges.push_back({new_nodes[u], new_nodes[v]});
    }

    auto [comp_odd, comp_even] = solveTree(new_vals, new_edges);

    ans_odd += comp_odd;
    ans_even += comp_even;
  }

  return {ans_odd, ans_even};
}

vector<optional<pair<vi,vi>>>
bipartiteComps(ll N, const vii& edges, ll nComps, const vi& edgesComp, const vector<set<ll>>& nodesComp) {
  vector<vii> adj(N);
  fore(e, 0, edges.size()) {
    auto [u, v] = edges[e];
    adj[u].push_back({v, edgesComp[e]});
    adj[v].push_back({u, edgesComp[e]});
  }


  vector<optional<pair<vi, vi>>> ans(nComps);
  vector<bool> revised(nComps, false);
  vector<bool> color(N);

  fore(u, 0, N) for (ll c : nodesComp[u]) if (!revised[c]) {
    revised[c] = true;
    set<ll> vis;
    vis.insert(u);
    vi s = {u};
    bool bipartite = true;
    while (!s.empty()) {
      auto v = s.back();
      s.pop_back();

      for (auto [w, d] : adj[v]) if (d == c) {
        if (vis.count(w)) {
          if (color[w] == color[v]) {
            bipartite = false;
          }
        } else {
          color[w] = !color[v];
          vis.insert(w);
          s.push_back(w);
        }
      }
    }

    if (bipartite && vis.size() > 1) {
      ans[c] = {{}, {}};
      for (ll v : vis) {
        if (!color[v]) {
          ans[c]->first.push_back(v);
        } else {
          ans[c]->second.push_back(v);
        }
      }
    }
  }

  return ans;
}

/** Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: O(\alpha(N))$
 */
struct UF {
  vi e;
  UF(ll n) : e(n, -1) {}
  bool sameSet(ll a, ll b) { return find(a) == find(b); }
  ll size(ll x) { return -e[find(x)]; }
  ll find(ll x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(ll a, ll b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b], e[b] = a;
    return true;
  }
};

ii solve(ll N, const vii& edges) {
  ll M = edges.size();

  auto [nComps, edgesComp, nodesComp] = BCC(N, edges);

  vector<optional<pair<vi,vi>>> bipartite_comps = bipartiteComps(N, edges, nComps, edgesComp, nodesComp);

  UF uf(N);
  for (auto bip_comp : bipartite_comps) {
    if (bip_comp.has_value()) {
      fore(i, 1, bip_comp->first.size()) {
        uf.join(bip_comp->first[0], bip_comp->first[i]);
      }
      fore(i, 1, bip_comp->second.size()) {
        uf.join(bip_comp->second[0], bip_comp->second[i]);
      }
    }
  }

  vi reps;
  fore(i, 0, N) {
    if (uf.find(i) == i) {
      reps.push_back(i);
    }
  }

  ll new_N = reps.size();
  vi new_nodes(N);
  fore(i, 0, new_N) {
    new_nodes[reps[i]] = i;
  }
  fore(i, 0, N) {
    new_nodes[i] = new_nodes[uf.find(i)];
  }

  ll ans_even = 0, ans_odd = 0;
  vii new_edges;
  vi new_vals(new_N);
  for (auto bip_comp : bipartite_comps) {
    if (bip_comp.has_value()) {
      ll u = bip_comp->first[0], v = bip_comp->second[0];
      new_edges.push_back({new_nodes[u], new_nodes[v]});
      assert(!uf.sameSet(u, v));
      ll uf_size_u = uf.size(u), uf_size_v = uf.size(v);
      ans_even += uf_size_u * (uf_size_u - 1) / 2;
      ans_even += uf_size_v * (uf_size_v - 1) / 2;
      new_vals[new_nodes[u]] += uf_size_u;
      new_vals[new_nodes[v]] += uf_size_v;
    }
  }

  fore(i, 0, new_N) {
    if (new_vals[i] == 0) {
      new_vals[i] = 1;
    }
  }

  fore(e, 0, M) {
    if (edgesComp[e] == -1) {
      auto [u, v] = edges[e];
      new_edges.push_back({new_nodes[u], new_nodes[v]});
    }
  }

  for (auto [u, v] : new_edges) {
    assert(u != v);
    if (u > v) {
      swap(u, v);
    }
  }

  sort(ALL(new_edges));
  new_edges.erase(unique(ALL(new_edges)), new_edges.end());

  auto [tree_odd, tree_even] = solveForest(new_vals, new_edges);

  ans_odd += tree_odd;
  ans_even += tree_even;

  return {ans_odd, ans_even};
}

optional<ii> isPath(const vii& path) {
  if (path.size() == 1) {
    return minmax(path[0].first, path[0].second);
  }

  for (ll start : {path[0].first, path[0].second}) {
    ll last = start;
    set<ll> nodes = {start};
    for (auto [u, v] : path) {
      if (u != last && v != last) {
        goto end;
      }
      last = u == last ? v : u;
      if (nodes.count(last)) {
        goto end;
      }
      nodes.insert(last);
    }
    return minmax(start, last);

    end:;
  }
  return {};
}

ii force(ll N, const vii& edges) {
  ll M = edges.size();

  vector<vector<vi>> paths(N, vector<vi>(N));

  fore(x, 1, 1 << M) {
    vii path;
    fore(e, 0, M) if (x & (1 << e)) {
      path.push_back(edges[e]);
    }
    sort(ALL(path));
    do {
      auto ends = isPath(path);
      if (ends.has_value()) {
        auto [u, v] = *ends;
        paths[u][v].push_back(x);
        break;
      }
    } while (next_permutation(ALL(path)));
  }

  ll ans_odd = 0, ans_even = 0;

  fore(u, 0, N) fore(v, u + 1, N) {
    bool found_odd = false, found_even = false;
    for (ll x : paths[u][v]) {
      if (__builtin_popcount(x) % 2 == 0) {
        found_even = true;
      } else {
        found_odd = true;
      }
    }
    if (found_odd && !found_even) {
      ans_odd++;
    } else if (found_even && !found_odd) {
      ans_even++;
    }
  }

  return {ans_odd, ans_even};
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
#ifndef TEST
  ll N, M;
  cin >> N >> M;
  vii edges(M);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }
  auto [D, R] = solve(N, edges);
  cout << R << ' ' << D << '\n';
#else
  fore(_, 0, 1000) {
    ll N = rand() % 10 + 1;
    ll M = rand() % 10 + 1;
    set<ii> edges_set;
    fore(_, 0, M) {
      ll u = rand() % N;
      ll v = rand() % N;
      if (u == v) {
        continue;
      }
      if (u > v) {
        swap(u, v);
      }
      edges_set.insert({u, v});
    }
    vii edges(ALL(edges_set));
    M = edges.size();

    ii ans = solve(N, edges);
    ii ansf = force(N, edges);

    if (ans != ansf) {
      cerr << N << ' ' << M << '\n';
      for (auto [u, v] : edges) {
        cerr << u + 1 << ' ' << v + 1 << '\n';
      }
      cerr << endl;
      cerr << ans.first << ' ' << ans.second << '\n';
      cerr << ansf.first << ' ' << ansf.second << '\n';
      cerr << endl;
      return 1;
    }
  }
#endif
}
