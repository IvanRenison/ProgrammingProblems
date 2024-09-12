// https://atcoder.jp/contests/abc369/tasks/abc369_g

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
typedef ii T;
typedef ii L; // T: data type, L: lazy type
// neutrals
constexpr static T tneut = {0, 0};
constexpr static L lneut = {0, inf};
T f(T a, T b) { return max(a, b); } // operation
// new st according to lazy
T apply(T v, L l, ll s, ll e) {
  return {v.first + l.first, l.second == inf ? v.second : l.second};
}
// cumulative effect of lazy
L comb(L a, L b) {
  return {a.first + b.first, b.second == inf ? a.second : b.second};
}

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
  void updSubtree(ll v, L l) { // updSubtree is similar
    t.upd(pos[v] + VALS_ED, pos[v] + siz[v], l);
  }
  void updPoint(ll v, L val) { // For normal segment tree
  	t.upd(pos[v], pos[v] + 1, val); // queryPoint is similar
  }
};

vu solve(vuuu& edges) {
  ull N = edges.size() + 1;

  vector<vi> adj(N);
  vector<vuu> adj2(N);
  for (auto [U, V, L] : edges) {
    adj[U].push_back(V);
    adj[V].push_back(U);
    adj2[U].push_back({V, L});
    adj2[V].push_back({U, L});
  }

  vu dists(N);
  vu pars(N, inf);

  function<void(ull, ull, ull)> dfs_dist = [&](ull u, ull p, ull d) {
    dists[u] = d;
    pars[u] = p;
    for (auto [v, L] : adj2[u]) {
      if (v == p) continue;
      dfs_dist(v, u, d + L);
    }
  };
  dfs_dist(0, inf, 0);


  HLD<false> hld(adj);

  fore(i, 1, N) {
    hld.updPoint(i, {dists[i], i});
  }

  vector<bool> zero(N, false);
  zero[0] = true;

  vu ans(N);
  ull sum = 0;
  fore(i, 0, N) {
    auto [d, u] = hld.querySubtree(0);
    if (d != 0) {
      sum += 2 * d;
      vu path;
      ull v = u;
      while (!zero[v]) {
        path.push_back(v);
        v = pars[v];
      }
      for (ull v : views::reverse(path)) {
        zero[v] = true;
        auto [d_, _] = hld.queryPath(v, v);
        hld.updSubtree(v, {-d_, inf});
      }
    }

    ans[i] = sum;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N;
  cin >> N;
  vuuu edges(N - 1);
  for (auto& [U, V, L] : edges) {
    cin >> U >> V >> L;
    U--, V--;
  }

  auto ans = solve(edges);
  for (ull a : ans) {
    cout << a << '\n';
  }

}
