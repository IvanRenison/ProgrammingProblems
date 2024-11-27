// https://codeforces.com/gym/103934/problem/J
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
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;

const ll inf = 1ll << 60;

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

/** Author: Iván Renison
 * Date: 2024-03-05
 * License: CC0
 * Source: notebook el vasito
 * Description: Segment tree with ability to add values of large intervals, and compute the sum of intervals.
 * Ranges are [s, e).
 * Can be changed to other things.
 * Time: O(\log N).
 * Usage: Tree st(n);
 *  st.init(x);
 *  st.upd(s, e, v);
 *  st.query(s, e);
 * Status: Tested on SPOJ HORRIBLE, stress-tested a bit
 */
typedef ll T; typedef ll L; // T: data type, L: lazy type
const T tneut = inf; const L lneut = -1; // neutrals
T f(T a, T b) { return min(a, b); } // associative
T apply(T v, L l, ll s, ll e) { // new st according to lazy
  return l != -1 ? l : v;
}
L comb(L a, L b) { return b != -1 ? b : a; } // cumulative effect of lazy

struct Tree { // example: range sum with range addition
  ll n;
  vector<T> st;
  vector<L> lazy;
  Tree(ll n) : n(n), st(4*n, tneut), lazy(4*n, lneut) {}
  Tree(vector<T> &a) : n(SZ(a)), st(4*n), lazy(4*n, lneut) {
    init(1, 0, n, a);
  }
  void init(ll k, ll s, ll e, vector<T> &a) {
    lazy[k] = lneut;
    if (s + 1 == e) { st[k] = a[s]; return; }
    ll m = (s + e) / 2;
    init(2*k, s, m, a), init(2*k+1, m, e, a);
    st[k] = f(st[2*k], st[2*k+1]);
  }
  void push(ll k, ll s, ll e) {
    if (lazy[k] == lneut) return; // if neutral, nothing to do
    st[k] = apply(st[k], lazy[k], s, e);
    if (s + 1 < e) { // propagate to children
      lazy[2*k] = comb(lazy[2*k], lazy[k]);
      lazy[2*k+1] = comb(lazy[2*k+1], lazy[k]);
    }
    lazy[k] = lneut; // clear node lazy
  }
  void upd(ll k, ll s, ll e, ll a, ll b, L v) {
    push(k, s, e);
    if (s >= b || e <= a) return;
    if (s >= a && e <= b) {
      lazy[k] = comb(lazy[k], v); // accumulate lazy
      push(k, s, e);
      return;
    }
    ll m = (s + e) / 2;
    upd(2*k, s, m, a, b, v), upd(2*k+1, m, e, a, b, v);
    st[k] = f(st[2*k], st[2*k+1]);
  }
  T query(ll k, ll s, ll e, ll a, ll b) {
    if (s >= b || e <= a) return tneut;
    push(k, s, e);
    if (s >= a && e <= b) return st[k];
    ll m = (s + e) / 2;
    return f(query(2*k, s, m, a, b),query(2*k+1, m, e, a, b));
  }
  void upd(ll a, ll b, L v) { upd(1, 0, n, a, b, v); }
  T query(ll a, ll b) { return query(1, 0, n, a, b); }
};

/** Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code does additive modifications and sum queries, but can
 * support commutative segtree modifications/queries on paths and subtrees.
 * For a non-commutative operation see LinkCutTree.
 * Takes as input the full adjacency list. VALS\_ED being true means that
 * values are stored in the edges, as opposed to the nodes, and updates
 * have to be done on child nodes. All values initialized to the segtree default.
 * Root must be 0. If you only have point updates you can use normal segment tree instead of lazy.
 * Time: O((\log N)^2)
 * Status: stress-tested a bit
 */
template <bool VALS_ED> struct HLD {
  ll N, tim = 0;
  vector<vi> adj;
  vi par, siz, rt, pos;
  Tree t;
  HLD(vector<vi> adj_)
    : N(SZ(adj_)), adj(adj_), par(N, -1), siz(N, 1),
      rt(N), pos(N), t(N) { dfsSz(0), dfsHld(0); }
  void dfsSz(ll v) {
    if (par[v] != -1) adj[v].erase(find(ALL(adj[v]), par[v]));
    for (ll& u : adj[v]) {
      par[u] = v;
      dfsSz(u);
      siz[v] += siz[u];
      if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
    }
  }
  void dfsHld(ll v) {
    pos[v] = tim++;
    for (ll u : adj[v]) {
      rt[u] = (u == adj[v][0] ? rt[v] : u);
      dfsHld(u);
    }
  }
  void process(ll u, ll v, auto op) {
    for (; rt[u] != rt[v]; v = par[rt[v]]) {
      if (pos[rt[u]] > pos[rt[v]]) swap(u, v);
      op(pos[rt[v]], pos[v] + 1);
    }
    if (pos[u] > pos[v]) swap(u, v);
    op(pos[u] + VALS_ED, pos[v] + 1);
  }
  void updPath(ll u, ll v, L val) {
    process(u, v, [&](ll l, ll r) { t.upd(l, r, val); });
  }
  T queryPath(ll u, ll v) {
    T res = tneut;
    process(u, v, [&](ll l, ll r) {
        res = f(res, t.query(l, r));
    });
    return res;
  }
  T querySubtree(ll v) { // updSubtree is similar
    return t.query(pos[v] + VALS_ED, pos[v] + siz[v]);
  }
  // void updPoint(ll v, T val) { // For normal segment tree
  // 	t.upd(pos[v], val); // queryPoint is similar
  // }
};

vi solveTree(ll N, viii& edges, viii& upds) {
  ll q = upds.size();

  vector<vi> adj(N);
  for (auto [u, v, w] : edges) {
    adj[u].push_back(v), adj[v].push_back(u);
  }

  HLD<true> hld(adj);

  for (auto [u, v, w] : edges) {
    hld.updPath(u, v, w);
  }

  vi ans(q);

  fore(i, 0, q) {
    auto [u, v, w] = upds[i];
    if (u != v) {
      hld.updPath(u, v, inf);
    }
    ll this_ans = hld.querySubtree(0);
    ans[i] = this_ans == inf ? -1 : this_ans;
  }

  return ans;
}

vi solve(ll n, viii& edges, viii& upds) {
  ll m = edges.size();
  vii edges_(m);
  fore(i, 0, m) {
    auto [u, v, w] = edges[i];
    edges_[i] = {u, v};
  }

  auto [nComps, edgesComp, nodesComp] = BCC(n, edges_);

  UF uf(n);
  fore(i, 0, m) {
    if (edgesComp[i] != -1) {
      auto [u, v, w] = edges[i];
      uf.join(u, v);
    }
  }

  vi reps;
  fore(i, 0, n) {
    if (uf.find(i) == i) {
      reps.push_back(i);
    }
  }

  vi new_nodes(n);
  fore(i, 0, n) {
    new_nodes[i] = lower_bound(ALL(reps), uf.find(i)) - reps.begin();
  }

  viii new_edges;
  for (auto [u, v, w] : edges) {
    if (new_nodes[u] != new_nodes[v]) {
      new_edges.push_back({new_nodes[u], new_nodes[v], w});
    }
  }
  viii new_upds;
  for (auto [u, v, w] : upds) {
    new_upds.push_back({new_nodes[u], new_nodes[v], w});
  }

  vi ans = solveTree(reps.size(), new_edges, new_upds);
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll n, m;
  cin >> n >> m;
  viii edges(m);
  for (auto& [u, v, w] : edges) {
    cin >> u >> v >> w;
    u--, v--;
  }
  ll q;
  cin >> q;
  viii upds(q);
  for (auto& [u, v, w] : upds) {
    cin >> u >> v >> w;
    u--, v--;
  }
  vi ans = solve(n, edges, upds);
  for (ll a : ans) {
    cout << a << '\n';
  }
}
