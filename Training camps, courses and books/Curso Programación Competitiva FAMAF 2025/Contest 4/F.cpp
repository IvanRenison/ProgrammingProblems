// https://codeforces.com/group/Xaa6lwRoge/contest/635590/problem/F

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
    for (ll pw = 1, k = 1; pw * 2 <= SZ(V); pw *= 2, ++k) {
      jmp.emplace_back(SZ(V) - pw * 2 + 1);
      fore(j,0,SZ(jmp[k]))
        jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(ll a, ll b) {
    assert(a < b); // or return inf if a == b
    ll dep = 63 - __builtin_clzll(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
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

  LCA(vector<vuu>& C) : time(SZ(C)), rmq((dfs(C,0,-1), ret)) {}
  void dfs(vector<vuu>& C, ll v, ll par) {
    time[v] = T++;
    for (auto [y, _] : C[v]) if (y != par) {
      path.push_back(v), ret.push_back(time[v]);
      dfs(C, y, v);
    }
  }

  ll lca(ll a, ll b) {
    if (a == b) return a;
    tie(a, b) = minmax(time[a], time[b]);
    return path[rmq.query(a, b)];
  }
};



bool solve(vector<vu>& ans) {
  ull n = ans.size();

  vuuu ds;
  fore(u, 0, n) {
    if (ans[u][u] != 0) {
      return false;
    }
    fore(v, 0, u) {
      if (ans[u][v] != ans[v][u] || ans[u][v] == 0) {
        return false;
      }
      ds.push_back({ans[u][v], u, v});
    }
  }

  sort(ALL(ds));

  UF comps(n);
  vuuu edges;

  for (auto [d, u, v] : ds) {
    if (comps.join(u, v)) {
      edges.push_back({u, v, d});
    }
  }

  vector<vuu> adj(n);
  for (auto [u, v, d] : edges) {
    adj[u].push_back({v, d}), adj[v].push_back({u, d});
  }

  LCA lca(adj);

  vu depth(n, inf);
  depth[0] = 0;
  vu s = {0};
  for (ull i = 0; i < s.size(); i++) {
    ull u = s[i];
    for (auto [v, d] : adj[u]) if (depth[v] == inf) {
      depth[v] = depth[u] + d;
    }
  }

  vector<vu> dists(n, vu(n));

  fore(u, 0, n) fore(v, 0, u) {
    ull dist = depth[u] + depth[v] - 2 * depth[lca.lca(u, v)];
    dists[u][v] = dists[v][u] = dist;
  }

  return ans == dists;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;
  vector<vu> dists(n, vu(n));
  fore(i, 0, n) {
    fore(j, 0, n) {
      cin >> dists[i][j];
    }
  }

  bool ans = solve(dists);
  if (ans) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }

}
