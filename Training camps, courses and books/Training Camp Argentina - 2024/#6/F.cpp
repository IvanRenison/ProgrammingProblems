// https://codeforces.com/group/5GNF7zti59/contest/534709

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
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

// Based on ModularArithmetic of kactl

ll euclid(ll a, ll b, ll& x, ll& y) {
  if (!b)
    return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

constexpr ull mod = 998244353;
struct Mod {
  ull x;
  Mod(ull xx) : x(xx % mod) {}
  Mod() : x(0) {}
  Mod operator+(Mod b) const {
    return Mod((x + b.x) >= mod ? x + b.x - mod : x + b.x);
  }
  Mod operator-(Mod b) const {
    return Mod(x >= b.x ? x - b.x : x + mod - b.x);
  }
  Mod operator*(Mod b) const {
    return Mod((x * b.x) % mod);
  }
  Mod operator+=(Mod b) {
    return *this = *this + b;
  }
  Mod operator-=(Mod b) {
    return *this = *this - b;
  }
  Mod operator*=(Mod b) {
    return *this = *this * b;
  }
  Mod operator++() {
    return *this = *this + Mod(1);
  }
  Mod operator--() {
    return *this = *this - Mod(1);
  }
  bool operator==(Mod b) const {
    return x == b.x;
  }
  bool operator!=(Mod b) const {
    return x != b.x;
  }
  bool operator<(Mod b) const {
    return x < b.x;
  }
  bool operator>(Mod b) const {
    return x > b.x;
  }
  bool operator<=(Mod b) const {
    return x <= b.x;
  }
  bool operator>=(Mod b) const {
    return x >= b.x;
  }

  Mod invert(Mod a) const {
    ll x, y, g = euclid(a.x, mod, x, y);
    assert(g == 1);
    return Mod((x + mod) % mod);
  }
  Mod operator^(ull e) const {
    if (!e)
      return Mod(1);
    Mod r = *this ^ (e / 2);
    r = r * r;
    return e & 1 ? *this * r : r;
  }
  Mod operator/(Mod b) const {
    return *this * invert(b);
  }
  Mod operator/=(Mod b) {
    return *this = *this / b;
  }

  friend ostream& operator<<(ostream& os, Mod m) {
    os << m.x;
    return os;
  }
  friend istream& operator>>(istream& is, Mod& m) {
    is >> m.x;
    return is;
  }

  operator ull() const {
    return x;
  }
  operator ll() const {
    return x;
  }
};

typedef vector<Mod> vm;
typedef pair<Mod, Mod> mm;
typedef vector<mm> vmm;
typedef tuple<Mod, Mod, Mod> mmm;
typedef vector<mmm> vmmm;
typedef tuple<Mod, Mod, Mod, Mod> mmmm;
typedef vector<mmmm> vmmmm;

typedef pair<ull, Mod> um;
typedef tuple<ull, ull, Mod> uum;

/** Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
template<class T>
struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T>& V) : jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= (int)SZ(V); pw *= 2, ++k) {
      jmp.emplace_back(SZ(V) - pw * 2 + 1);
      fore(j,0,SZ(jmp[k]))
        jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(int a, int b) const {
    assert(a < b); // or return inf if a == b
    int dep = 31 - __builtin_clz(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

/** Author: Iván Renison
 * Date: 2024-05-18
 * License: CC0
 * Source: Folklore
 * Description: Data structure for computing queries on paths in a tree.
 * Works for nodes having values but can be changed to work with edges having values.
 * Time: construction O(N \log N)$, queries O(\log N)$
 * Status: stress-tested a bit
 */
struct PathQueries {
  typedef Mod T;
  const T neut = Mod(1);
  T f(const T& a, const T& b) {
    return a * b;
  } // (any associative and commutative fn)

  ll n, K;
  vector<vi> anc;
  vector<vector<T>> part;
  vi depth;
/*   PathQueries(const vector<vi>& g, vector<T>& vals) // NODES
    : n(SZ(g)), K(64 - __builtin_clzll(n)), anc(K, vi(n, -1)),
      part(K, vector<T>(n, neut)), depth(n) {
    part[0] = vals; */
PathQueries(const vector<vector<pair<ull, T>>> &g_) // EDGES
	: n(SZ(g_)), K(64 - __builtin_clzll(n)), anc(K, vi(n, -1)),
		part(K, vector<T>(n, neut)), depth(n) {
	vector<vi> g(n);
	fore(u, 0, n) for (auto [v, data] : g_[u]) {
		g[u].push_back(v);
	}
    vi s = {0};
    while (!s.empty()) {
      ll u = s.back();
      s.pop_back();
      for (ll v : g[u]) if (v != anc[0][u]) {
        anc[0][v] = u, depth[v] = depth[u] + 1, s.push_back(v);
      }
    }
	fore(u, 0, n) for (auto [v, data] : g_[u]) { // EDGES
		part[0][depth[u] > depth[v] ? u : v] = data;
	}
    fore(k, 0, K - 1) fore(v, 0, n) {
      if (anc[k][v] != -1) {
        anc[k + 1][v] = anc[k][anc[k][v]];
        part[k + 1][v] = f(part[k][v], part[k][anc[k][v]]);
      }
    }
  }
  T query(ll u, ll v) {
    if (depth[u] < depth[v]) swap(u, v);
    T ans = neut;
    fore(k, 0, K) if ((depth[u] - depth[v]) & (1 << k))
      ans = f(ans, part[k][u]), u = anc[k][u];
//    if (u == v) return f(ans, part[0][u]); // NODES
	if (u == v) return ans; // EDGES
    for (ll k = K; k--;) if (anc[k][u] != anc[k][v]) {
      ans = f(ans, f(part[k][u], part[k][v]));
      u = anc[k][u], v = anc[k][v];
    }
    ans = f(ans, f(part[0][u], part[0][v]));
//    return f(ans, part[0][anc[0][u]]); // NODES
	return ans; // EDGES
  }
};

/** Author: chilli, pajenegod
 * Date: 2020-02-20
 * License: CC0
 * Source: Folklore
 * Description: Data structure for computing lowest common ancestors in a tree
 * (with 0 as root). C should be an adjacency list of the tree, either directed
 * or undirected.
 * Time: O(N \log N + Q)$
 * Status: stress-tested
 */
struct LCA {
  ll T = 0;
  vi time, path, ret;
  RMQ<ll> rmq;

  LCA(const vector<vector<um>>& C) : time(SZ(C)), rmq((dfs(C,0,-1), ret)) {}
  void dfs(const vector<vector<um>>& C, ll v, ll par) {
    time[v] = T++;
    for (auto [y, _] : C[v]) if (y != par) {
      path.push_back(v), ret.push_back(time[v]);
      dfs(C, y, v);
    }
  }

  ll lca(ll a, ll b) const {
    if (a == b) return a;
    tie(a, b) = minmax(time[a], time[b]);
    return path[rmq.query(a, b)];
  }
  //dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}

  bool isAns(ll a, ll b) const {
    return a == lca(a, b);
  }
};

/** Author: Simon Lindholm
 * Date: 2016-01-14
 * License: CC0
 * Description: Given a tree T$ rooted at 0, and a subset of nodes X$ returns
 * tree with vertex set $\{\text{lca}(x, y) : x \in X, y \in X}$ and edges
 * between every pair of vertices in which one is an ancestor of the other in
 * T$. Size is at most |X| - 1$, including X$.
 * Returns a list of (par, orig\_index) representing a tree rooted at 0.
 * The root points to itself.
 * Time: O(|X| \log |X|)$
 * Status: Tested at CodeForces
 */
typedef vector<ii> vii;
vii compressTree(LCA& lca, const vi& subset) {
  static vi rev; rev.resize(SZ(lca.time));
  vi li = subset, &T = lca.time;
  auto cmp = [&](ll a, ll b) { return T[a] < T[b]; };
  sort(ALL(li), cmp);
  ll m = SZ(li)-1;
  fore(i,0,m) {
    ll a = li[i], b = li[i+1];
    li.push_back(lca.lca(a, b));
  }
  sort(ALL(li), cmp);
  li.erase(unique(ALL(li)), li.end());
  fore(i,0,SZ(li)) rev[li[i]] = i;
  vii ret = {{{0, li[0]}}};
  fore(i,0,SZ(li)-1) {
    ll a = li[i], b = li[i+1];
    ret.push_back({rev[lca.lca(a, b)], b});
  }
  return ret;
}


vm solve(ull n, const vector<uum>& edges) {

  vector<vector<um>> adj(n), adj_back(n);
  for (auto [u, v, w] : edges) {
    adj[u].push_back({v, w});
    adj_back[v].push_back({u, w});
  }

  vector<vector<um>> DFS_tree(n);
  vu DFS_tree_pars(n, inf);
  vu DFS_ord;
  vm DFS_prov(n);

  vb vis(n);
  function<void(ull)> dfs = [&](ull u) {
    vis[u] = true;
    DFS_ord.push_back(u);

    for (auto [v, w] : adj[u]) {
      if (!vis[v]) {
        DFS_tree[u].push_back({v, w});
        DFS_tree_pars[v] = u;
        DFS_prov[v] = DFS_prov[u] * w;
        dfs(v);
      }
    }

  };
  DFS_prov[0] = Mod(1);
  dfs(0);

  vu dfs_ord_inv(n);
  fore(i, 0, n) {
    dfs_ord_inv[DFS_ord[i]] = i;
  }

  PathQueries tpq(DFS_tree);
  LCA lca(DFS_tree);

  vm ans(n, Mod(1));
  fore(i, 1, n) {
    map<ull, Mod> vtree_nodes_p;
    vi vtree_nodes;
    for (auto [u, p] : adj_back[i]) {
      if (!lca.isAns(i, u)) {
        vtree_nodes_p[u] = p;
        vtree_nodes.push_back(u);
      }
    }

    //VTree vtree(lca, dfs_ord_inv, vtree_nodes);
    vii vtree = compressTree(lca, vtree_nodes);
    map<ull, vector<um>> vtree_adj;
    ull vtree_total_lca = inf;
    fore(j, 0, vtree.size()) {
      auto [pj, u] = vtree[j];
      if (pj != j) {
        ll v = vtree[pj].second;
        Mod m = tpq.query(u, v);
        vtree_adj[v].push_back({u, m});
        vtree_adj[u].push_back({v, m});
      } else {
        vtree_total_lca = u;
      }
    }
    assert(vtree_total_lca != inf);


    function<Mod(ull, ull)> dfs = [&](ull u, ull p) {
      Mod res = Mod(1); // Prov of not reaching
      if (vtree_nodes_p.count(u)) {
        res *= (Mod(1) - vtree_nodes_p[u]);
      }
      for (auto [v, w] : vtree_adj[u]) {
        if (v != p) {
          res *= Mod(1) - (Mod(1) - dfs(v, u)) * w;
        }
      }

      return res;
    };

    Mod prov_not_reach = dfs(vtree_total_lca, inf);
    ans[i] = DFS_prov[vtree_total_lca] * (Mod(1) - prov_not_reach);
  }


  return ans;
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ll n, m;
  cin >> n >> m;

  vector<uum> edges(m);
  for (auto& [u, v, w] : edges) {
    ll p, q;
    cin >> u >> v >> p >> q;
    u--, v--;
    w = Mod(p)/Mod(q);
  }

  auto ans = solve(n, edges);
  for (Mod a : ans) {
    cout << a << '\n';
  }

/*   fore(_, 0, 100000) {
    ll n = rand() % (100) + 3;
    ll m = min(rand() % (n * (n - 1) / 2 - n + 1) + n - 1, (ll)3e5);
    cout << n << ' ' << m << '\n';
    vector<uum> edges;
    set<uu> edges_set;
    fore(i, 1, n) {
      ll u = rand() % i;
      ll p = rand() % 100 + 1;
      ll q = rand() % 100 + 1;
      edges.push_back({u, i, Mod(p)/Mod(q)});
      edges_set.insert({u, i});
      cout << u + 1 << ' ' << i + 1 << ' ' << p << ' ' << q << '\n';
    }

    fore(i, n, m) {
      ll u = rand() % n;
      ll v = rand() % n;
      if (u == v) {
        continue;
      }
      if (edges_set.count(minmax(u, v))) {
        continue;
      }
      ll p = rand() % 100 + 1;
      ll q = rand() % 100 + 1;
      edges.push_back({u, v, Mod(p)/Mod(q)});
      edges_set.insert(minmax(u, v));
      cout << u + 1 << ' ' << v + 1 << ' ' << p << ' ' << q << '\n';
    }
    cout << endl;

    auto ans = solve(n, edges);

  } */

  return EXIT_SUCCESS;
}
