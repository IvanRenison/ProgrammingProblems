// https://codeforces.com/gym/104848/problem/L
#include <bits/stdtr1c++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;i++)
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;


struct Dinic {
  struct Edge {
    ll to, rev;
    ll c, oc;
//    ll flow()
  };
  vi lvl, ptr, q;
  vector<vector<Edge>> adj;
  Dinic(ll n) : lvl(n), ptr(n), q(n), adj(n) {}
  void addEdge(ll a, ll b, ll c, ll rcap = 0) {
    //cerr << a << ' ' << b << ' ' << c << endl;
    adj[a].push_back({b, SZ(adj[b]), c, c});
    adj[b].push_back({a, SZ(adj[a]) - 1, rcap, rcap});
  }
  ll dfs(ll v, ll t, ll f) {
    if (v == t || !f) return f;
    for (ll& i = ptr[v]; i < SZ(adj[v]); i++) {
      Edge& e = adj[v][i];
      if (lvl[e.to] == lvl[v] + 1)
        if (ll p = dfs(e.to, t, min(f, e.c))) {
          e.c -= p, adj[e.to][e.rev].c += p;
          return p;
        }
    }
    return 0;
  }
  ll calc(ll s, ll t) {
    ll flow = 0; q[0] = s;
    fore(L, 0, 31) do {
      lvl = ptr = vi(SZ(q));
      ll qi = 0, qe = lvl[s] = 1;
      while (qi < qe && !lvl[t]) {
        ll v = q[qi++];
        for (Edge e : adj[v])
          if (!lvl[e.to] && e.c >> (30 - L))
            q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
      }
      while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
    } while (lvl[t]);
    return flow;
  }
  bool leftOfMinCut(ll a) { return lvl[a] != 0; }
};

bool possibleWith(ll a, ll b, ll c, ll d, const vii& stores, const vii& houses, ll k) {
  ll n = stores.size();

  ll N = 2 * n + k + 2;
  /*
  0..2*n son stores
  2*n..2*n + j son casas
  2*n + k es s
  2*n + k + 1 es t
  */

  Dinic dinic(N);

  fore(i, 0, n) {
    //cerr << "----" << endl;
    dinic.addEdge(2*n + k, 2 * i, min(c - d, k));
    dinic.addEdge(2*n + k, 2 * i + 1, min(d, k));

    auto [xi, yi] = stores[i];


    fore(j, 0, k) {
      auto [xj, yj] = houses[j];


      ll dist2 = (xi - xj)*(xi - xj) + (yi - yj)*(yi - yj);

      if (dist2 <= a*a) {
        dinic.addEdge(2 * i, 2*n + j, 1);

      }
      if (dist2 <= b*b) {
        dinic.addEdge(2 * i + 1, 2*n + j, 1);

      }
    }
  }

  fore(j, 0, k) {
    dinic.addEdge(2*n + j, 2*n + k + 1, 1);
  }

  ll val = dinic.calc(2*n + k, 2*n + k + 1);

  return val == k;
}

ll solve(ll a, ll b, ll c, ll d, const vii& stores, const vii& houses) {
  ll n = stores.size(), m = houses.size();

  ll l = 0, r = m + 1;
  while (l + 1 < r) {
    ll middle = (l + r) / 2;
    if (!possibleWith(a, b, c, d, stores, houses, middle)) {
      r = middle;
    } else {
      l = middle;
    }
    //exit(EXIT_FAILURE);
  }

  return l == m ? -1 : l + 1;
}


int main(){FIN;

  ll n, m, a, b, c, d;
  cin >> n >> m >> a >> b >> c >> d;

  vii stores(n), houses(m);
  for (auto& [x, y] : stores) {
    cin >> x >> y;
  }
  for (auto& [x, y] : houses) {
    cin >> x >> y;
  }

  cout << solve(a, b, c, d, stores, houses) << '\n';

  return 0;
}