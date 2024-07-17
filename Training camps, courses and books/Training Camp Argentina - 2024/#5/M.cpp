// https://codeforces.com/group/5GNF7zti59/contest/536252/problem/M
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(X) X.begin(), X.end()
#define SZ(x) ((ll)x.size())
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;



struct UnionFind {
  typedef ll T;
  T ans;
  typedef ii D;
  void merge(D& large, const D& small) {
    ans -= large.first * large.second + small.first * small.second;
    large.first += small.first;
    large.second += small.second;
    ans += large.first * large.second;
  }
  ll n, comp;
  vi uf, si;
  vector<tuple<ll,D,T>> c;
  vector<D> d;
  UnionFind(ll n = 0) : n(n), comp(n), uf(n), si(n, 1), ans(0), d(n) {
    fore(i, 0, n) uf[i] = i;
  }
  ll find(ll x) {
    return x == uf[x] ? x : find(uf[x]);
  }
  bool join(ll x, ll y) {
    if ((x = find(x)) == (y = find(y)))
      return false;
    if (si[x] < si[y])
      swap(x, y);
    si[x] += si[y];
    c.pb({y, d[x], ans});
    merge(d[x], d[y]);
    uf[y] = x;
    comp--;
    return true;
  }
  ll snap() {
    return c.size();
  }
  void rollback(ll snap) {
    while (c.size() > snap) {
      auto [x, v, t] = c.back();
      c.pop_back();
      si[uf[x]] -= si[x];
      d[uf[x]] = v;
      uf[x] = x;
      comp++;
      ans = t;
    }
  }
};
enum { ADD, DEL, QUERY };
struct Query {
  ll type, x, y;
};
struct DynCon {
  vector<Query> q;
  UnionFind dsu;
  vector<ll> mt;
  map<pair<ll, ll>, ll> last;
  vi ans;
  DynCon(ll n) : dsu(n) {}
  void add(ll x, ll y) {
    if (x > y)
      swap(x, y);
    q.pb((Query){ADD, x, y});
    mt.pb(-1);
    last[{x, y}] = q.size() - 1;
  }
  void remove(ll x, ll y) {
    if (x > y)
      swap(x, y);
    q.pb((Query){DEL, x, y});
    ll pr = last[{x, y}];
    mt[pr] = q.size() - 1;
    mt.pb(pr);
  }
  void query() {
    q.pb((Query){QUERY, -1, -1});
    mt.pb(-1);
  }
  void process() { // answers all queries in order
    if (!q.size())
      return;
    fore(i, 0, q.size()) if (q[i].type == ADD && mt[i] < 0) mt[i] = q.size();
    go(0, q.size());
  }
  void go(ll s, ll e) {
    if (s + 1 == e) {
      if (q[s].type == QUERY) {// answer query using DSU
        ans.push_back(dsu.ans);
        // printf("%d\n", dsu.comp);
      }
      return;
    }
    ll k = dsu.snap(), m = (s + e) / 2;
    for (ll i = e - 1; i >= m; --i)
      if (mt[i] >= 0 && mt[i] < s)
        dsu.join(q[i].x, q[i].y);
    go(s, m);
    dsu.rollback(k);
    for (ll i = m - 1; i >= s; --i)
      if (mt[i] >= e)
        dsu.join(q[i].x, q[i].y);
    go(m, e);
    dsu.rollback(k);
  }
};

vi solve(const vii& queries) {
  ll q = queries.size();

  map<ll, ll> xmap, ymap;
  {
    vi xs(q), ys(q);
    fore(i, 0, q) {
      auto [x, y] = queries[i];
      xs[i] = x;
      ys[i] = y;
    }

    sort(ALL(xs));
    sort(ALL(ys));

    fore(i, 0, q) {
      xmap[xs[i]] = i;
      ymap[ys[i]] = q + i;
    }
  }

  set<ii> ps;

  DynCon dc(2 * q);

  fore(i, 0, q) {
    dc.dsu.d[i] = {1, 0};
    dc.dsu.d[q + i] = {0, 1};
  }

  for (auto [x, y] : queries) {
    if (ps.count({x, y})) {
      ps.erase({x, y});
      dc.remove(xmap[x], ymap[y]);
    } else {
      ps.insert({x, y});
      dc.add(xmap[x], ymap[y]);
    }
    dc.query();
  }

  dc.process();

  return dc.ans;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  ll q;
  cin >> q;
  vii queries(q);
  for (auto& [x, y] : queries) {
    cin >> x >> y;
  }

  vi ans = solve(queries);
  for (ll x : ans) {
    cout << x << ' ';
  }
  cout << '\n';

}