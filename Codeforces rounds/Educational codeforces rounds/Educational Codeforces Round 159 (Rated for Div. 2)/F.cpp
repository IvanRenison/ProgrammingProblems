// https://codeforces.com/contest/1902/problem/F

#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;

typedef unsigned int uint;
typedef uint8_t uint8;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;
typedef vector<uu> vuu;
typedef tuple<uint, uint, uint> uuu;
typedef vector<uuu> vuuu;
typedef vector<int> vi;
typedef vector<bool> vb;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const uint inf = 1 << 31;

typedef vu T;
inline void insert(T& bs, uint x) {
  for (uint a : bs) {
    x = min(x, x^a);
  }
  if (x != 0) {
    bs.push_back(x);
  }
}
inline bool check(const T& bs, uint x) {
  for (uint a : bs) {
    x = min(x, x^a);
  }
  return x == 0;
}
const static T NEUT = {};
inline T op(const T& a, const T& b) {
  T ans = a;
  for (uint x : b) {
    insert(ans, x);
  }
  return ans;
} // associative and commutative
inline void join(T& a, const T& b) {
  for (uint x : b) {
    insert(a, x);
  }
}

struct PathQueries {  // O(n log n) preprocessing, O(log n) query
  int n, K;
  vector<vi> anc;  // remove & for edge queries or if instance lives longer
  vector<vector<T>> part; vi dep;
  // NODES
  PathQueries(const vector<vu> &_g, vector<T> &vals) : n(sz(_g)), K(64 - __builtin_clzll(n)), anc(K, vi(n)), part(K, vector<T>(n, NEUT)), dep(n) {
    anc[0][0] = -1, dfs(0, _g), part[0] = vals;
    init();
  }
  // EDGES
  // PathQueries(vector<vector<pair<int, T>>> &_g) : n(sz(_g)), K(64 - __builtin_clzll(n)), g(n), anc(K, vi(n)), part(K, vector<T>(n, NEUT)), dep(n) {
  //   fore(u, 0, n) for (auto [v, data] : _g[u]) g[u].pb(v);
  //   anc[0][0] = -1, dfs(0);
  //   fore(u, 0, n) for (auto [v, data] : _g[u]) part[0][dep[u] > dep[v] ? u : v] = data;
  //   init();
  // }
  void init() {
    fore(k, 1, K) fore(v, 0, n) if (anc[k - 1][v] != -1)
      anc[k][v] = anc[k - 1][anc[k - 1][v]],
      part[k][v] = op(part[k - 1][v], part[k - 1][anc[k - 1][v]]);
    else anc[k][v] = -1;
  }
  void dfs(int u, const vector<vu> &_g) {
    for (uint v : _g[u]) {
      if (v == anc[0][u]) continue;
      anc[0][v] = u, dep[v] = dep[u] + 1, dfs(v, _g);
    }
  }
  T query(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    T ans = NEUT;
    for (int k = K - 1; k >= 0; --k)
      if (dep[u] - (1 << k) >= dep[v]) join(ans, part[k][u]), u = anc[k][u];
    // if (u == v) return ans; // edge queries
    if (u == v) {
      join(ans, part[0][u]);
      return ans;  // node queries
    }
    for (int k = K - 1; k >= 0; --k)
      if (anc[k][u] != anc[k][v]) {
        join(ans, part[k][u]), join(ans, part[k][v]);
        u = anc[k][u], v = anc[k][v];
      }
    join(ans, part[0][u]), join(ans, part[0][v]);
    // return ans; // edge queries
    join(ans, part[0][anc[0][u]]);
    return ans;  // node queries
  }
};

vb solve(const vu& as, const vuu& edges, const vuuu& querys) {
  uint n = as.size(), q = querys.size();

  vector<vu> adj(n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<T> vals(n);
  fore(i, 0, n) {
    vals[i] = {as[i]};
  }

  PathQueries pq(adj, vals);

  vb ans(q);
  fore(i, 0, q) {
    auto [x, y, k] = querys[i];

    T bs = pq.query(x, y);

    ans[i] = check(bs, k);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  uint n;
  cin >> n;
  vu as(n);
  for (uint& a : as) {
    cin >> a;
  }
  vuu edges(n - 1);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }
  uint q;
  cin >> q;
  vuuu querys(q);
  for (auto& [x, y, k] : querys) {
    cin >> x >> y >> k;
    x--, y--;
  }

  auto ans = solve(as, edges, querys);
  for (auto a : ans) {
    cout << (a ? "YES" : "NO") << '\n';
  }

  return EXIT_SUCCESS;
}
