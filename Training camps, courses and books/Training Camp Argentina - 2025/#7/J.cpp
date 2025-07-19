#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

const ll mod = 1000000007;

struct Mod {
  ll x;
  Mod(ll x) : x(x % mod) {}
  Mod operator+(Mod o) { return Mod(x + o.x); }
  Mod operator-(Mod o) { return Mod(x - o.x); }
  Mod operator*(Mod o) { return Mod(x * o.x); }
  bool operator==(Mod o) { return x == o.x; }
};

struct UF {
  vi e;
  UF(ll n) : e(n, -1) {}
  ll find(ll x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(ll a, ll b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b], e[b] = a;
    return true;
  }
};

typedef Mod T;
typedef Mod L;
const T tneut = 0;
const L lneut = 0;
T f(T a, T b) { return a + b; }
T apply(T v, L l, ll s, ll e) {
  return v + l * (e - s);
}
L comb(L a, L b) {
  return a + b;
}
struct Tree {
  ll n;
  vector<T> st;
  vector<L> lazy;
  Tree(ll n) : n(n), st(4*n, tneut), lazy(4*n, lneut) {}
  void push(ll k, ll s, ll e) {
    if (lazy[k] == lneut) return;
    st[k] = apply(st[k], lazy[k], s, e);
    if (s + 1 < e) {
      lazy[2 * k] = comb(lazy[2*k], lazy[k]);
      lazy[2*k+1] = comb(lazy[2*k+1], lazy[k]);
    }
    lazy[k] = lneut;
  }
  void upd(ll k, ll s, ll e, ll a, ll b, L v) {
    push(k, s, e);
    if (s >= b || e <= a) return;
    if (s >= a && e <= b) {
      lazy[k] = comb(lazy[k], v);
      push(k, s, e);
      return;
    }
    ll m = (s + e)/ 2;
    upd(2*k, s, m, a, b, v), upd(2*k+1, m, e, a, b, v);
    st[k] = f(st[2*k], st[2*k+1]);
  }
  T query(ll k, ll s, ll e, ll a, ll b) {
    if (s >= b || e <= a) return tneut;
    push(k, s, e);
    if (s >= a && e <= b) return st[k];
    ll m = (s + e) / 2;
    return f(query(2*k, s, m, a, b), query(2*k+1, m, e, a, b));
  }
  void upd(ll a, ll b, L v) { upd(1, 0, n, a, b, v); }
  T query(ll a, ll b) { return query(1, 0, n, a, b); }
};

Mod solve(vector<vii>& ops) {
  ll n = ops.size();

  vii edges;

  UF uf(n);
  vi roots(n);
  iota(ALL(roots), 0ll);

  fore(u, 0, n) {
    // ll k = ops[u].size();
    for (auto [v, x] : ops[u]) {
      edges.push_back({u, roots[uf.find(v)]});
      uf.join(u, v);
    }
    roots[uf.find(u)] = u;
  }


  vector<vi> suns(n);
  vi ps(n, -1);
  for (auto [u, v] : edges) {
    //cerr << u << ' ' << v << '\n';
    assert(ps[v] == -1);
    ps[v] = u;
    suns[u].push_back(v);
  }

  vi dfs_ord;
  vi in(n), out(n);

  //cerr << "dfs_ord: ";

  auto dfs = [&](ll u, auto&& dfs) -> void {
    in[u] = dfs_ord.size();
    dfs_ord.push_back(u);
    //cerr << u << ' ';
    for (ll v : suns[u]) {
      dfs(v, dfs);
    }
    out[u] = dfs_ord.size();
  };
  //cerr << '\n';

  fore(u, 0, n) if (ps[u] == -1) {
    dfs(u, dfs);
  }

  assert(dfs_ord.size() == n);

  Tree tree(n);
  uf = UF(n);
  roots = vi(n);
  iota(ALL(roots), 0ll);

  Mod ans = 0;

  fore(u, 0, n) {
    //cerr << "u: " << u << '\n';
    for (auto [v, x] : ops[u]) {
      //cerr << "v: " << v << '\n';
      //cerr << "x: " << x << '\n';
      ll root_v = roots[uf.find(v)];
      //cerr << "root_v: " << root_v << '\n';

      Mod w = Mod(x) + tree.query(in[v], in[v] + 1);
      //cerr << "w: " << w.x << '\n';

      ans = ans + w;

      tree.upd(in[root_v], out[root_v], w);
      //cerr << "upd: " << in[root_v] << ' ' << out[root_v] << ' ' << w.x << '\n';

      uf.join(u, v);
    }
    roots[uf.find(u)] = u;
  }

  return ans;
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0);

  ll n;
  cin >> n;
  vector<vii> ops(n);
  fore(i, 0, n) {
    ll k;
    cin >> k;
    ops[i] = vii(k);
    for (auto& [v, x] : ops[i]) {
      cin >> v >> x;
      v--;
      if (x < 0) {
        x = mod + x;
      }
    }
  }

  Mod ans = solve(ops);
  cout << ans.x << '\n';
}