// https://codeforces.com/contest/2069/problem/F

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

/** Author: Pietro Palombini and Iván Renison
 * Date: 2024-07-25
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure, with undo and support for
 * storing additional data in each component and global data.
 * Default operations and data are for sum in each component and count of components.
 * Time: O(\log(N))$
 * Status: stress tested a bit
 */
typedef ll T; // Global data
typedef ll D; // Component data
struct RSUF {
  T ans; // Global data initial value, set in constructor
  void merge(D& large, const D& small) {
    large = large + small, ans--;
  }

  ll n;
  vi e; vector<D> d;
  vector<tuple<ll,ll,ll,D,T>> st;
  RSUF(ll n) : ans(n), n(n), e(n, -1), d(n) {}
  RSUF(vector<D>& d) : ans(SZ(d)), n(SZ(d)), e(n,-1), d(d) {}
  ll size(ll x) { return -e[find(x)]; }
  ll find(ll x) { return e[x] < 0 ? x : find(e[x]); }
  ll time() { return SZ(st); }
  D get(ll x) { return d[find(x)]; }
  void rollback(ll t) {
    while (SZ(st) > t) {
      auto [a, b, s, v, t] = st.back();
      st.pop_back();
      d[a] = v, e[a] -= e[b] = s, ans = t;
    }
  }
  bool join(ll a, ll b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    st.push_back({a, b, e[b], d[a], ans});
    merge(d[a], d[b]);
    e[a] += e[b], e[b] = a;
    return true;
  }
};

/** Author: Iván Renison
 * Date: 2024-07-25
 * License: CC0
 * Source: notebook el vasito
 * Description: Offline disjoint-set data structure with remove of arbitrary edges.
 * Uses UnionFindRollbackStore so it also supports queries of global value of RSUF.
 * First use add, remove and query to make operations and then call process to get
 * the answers of the queries in the variable ans.
 * Does not support multiple edges.
 * Time: O(Q \log^2 N)
 * Status: stress tested a bit and tested in codeforces
 */
enum { ADD, DEL, QUERY };
struct Query { ll type, x, y; }; // You can add stuff for QUERY
struct DynCon {
  vector<Query> q;
  RSUF uf;
  vi mt;
  map<ii, ll> last;
  vector<T> ans;
  DynCon(ll n) : uf(n) {}
  DynCon(vector<D>& d) : uf(d) {}
  void add(ll x, ll y) {
    if (x > y) swap(x, y);
    mt.push_back(-1);
    last[{x, y}] = SZ(q);
    q.push_back({ADD, x, y});
  }
  void remove(ll x, ll y) {
    if (x > y) swap(x, y);
    ll pr = last[{x, y}];
    mt[pr] = SZ(q);
    mt.push_back(pr);
    q.push_back({DEL, x, y});
  }
  void query() { // Add parameters if needed
    q.push_back({QUERY, -1, -1});
    mt.push_back(-1);
  }
  void process() { // Answers all queries in order
    if (q.empty()) return;
    fore(i, 0, SZ(q))
      if (q[i].type == ADD && mt[i] < 0) mt[i] = SZ(q);
    go(0, SZ(q));
  }
  void go(ll s, ll e) {
    if (s + 1 == e) {
      if (q[s].type == QUERY) { // Answer query using DSU
        ans.push_back(uf.ans); // Maybe you want to use uf.get(x)
      }                 // for some x stored in Query
      return;
    }
    ll k = uf.time(), m = (s + e) / 2;
    for (ll i = e; --i >= m;)
      if (0 <= mt[i] && mt[i] < s) uf.join(q[i].x, q[i].y);
    go(s, m);
    uf.rollback(k);
    for (ll i = m; --i >= s;)
      if (mt[i] >= e) uf.join(q[i].x, q[i].y);
    go(m, e);
    uf.rollback(k);
  }
};

vu solve(ull n, vector<tuple<char, ull, ull>>& quieres) {
  ull q = quieres.size();

  set<uu> A_edges, B_edges;
  map<uu, ull> AB_edges;
  DynCon A(n), AB(n);

  for (auto [c, x, y] : quieres) {
    if (c == 'A') {
      if (A_edges.count({x, y})) {
        A_edges.erase({x, y});
        A.remove(x, y);
        AB_edges[{x, y}]--;
        if (AB_edges[{x, y}] == 0) {
          AB.remove(x, y);
        }
      } else {
        A_edges.insert({x, y});
        A.add(x, y);
        AB_edges[{x, y}]++;
        if (AB_edges[{x, y}] == 1) {
          AB.add(x, y);
        }
      }
    } else {
      if (B_edges.count({x, y})) {
        B_edges.erase({x, y});
        AB_edges[{x, y}]--;
        if (AB_edges[{x, y}] == 0) {
          AB.remove(x, y);
        }
      } else {
        B_edges.insert({x, y});
        AB_edges[{x, y}]++;
        if (AB_edges[{x, y}] == 1) {
          AB.add(x, y);
        }
      }
    }

    A.query();
    AB.query();
  }

  A.process();
  AB.process();

  vu ans(q);
  fore(i, 0, q) {
    ans[i] = A.ans[i] - AB.ans[i];
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, q;
  cin >> n >> q;
  vector<tuple<char, ull, ull>> quieres(q);
  for (auto& [c, x, y] : quieres) {
    cin >> c >> x >> y;
    x--, y--;
    if (x > y) {
      swap(x, y);
    }
  }

  vu ans = solve(n, quieres);
  for (auto a : ans) {
    cout << a << '\n';
  }

}
