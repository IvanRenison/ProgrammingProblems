// https://codeforces.com/group/5GNF7zti59/contest/534272/problem/B
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

const ll inf = 1ll << 60;

/** Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with complexity O(VE\log U)$ where U = \max |\text{cap}|$.
 * O(\min(E^{1/2}, V^{2/3})E)$ if U = 1$; O(\sqrt{V}E)$ for bipartite matching.
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */
struct Dinic {
  struct Edge {
    ll to, rev;
    ll c, oc;
    ll flow() { return max(oc - c, 0LL); } // if you need flows
  };
  vi lvl, ptr, q;
  vector<vector<Edge>> adj;
  Dinic(ll n) : lvl(n), ptr(n), q(n), adj(n) {}
  void addEdge(ll a, ll b, ll c, ll rcap = 0) {
    adj[a].push_back({b, (ll)SZ(adj[b]), c, c});
    adj[b].push_back({a, (ll)SZ(adj[a]) - 1, rcap, rcap});
    //cerr << a << ' ' << b << ' ' << c << '\n';
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
    fore(L,0,31) do { // 'll L=30' maybe faster for random data
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

vi dijkstra(const vector<vii>& adj, ll s) {
  ll n = adj.size();

  vi dist(n, inf);
  rpriority_queue<ii> pq;

  pq.push({0, s});

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    if (dist[u] <= d) {
      continue;
    }

    dist[u] = d;

    for (auto [v, e] : adj[u]) {
      if (d + e <= dist[v]) {
        pq.push({d + e, v});
      }
    }
  }

  return dist;
}

ll solve(const vi& ps, const viii& edges, const vii& shelters) {
  ll n = ps.size(), s = shelters.size();

  ll total_ps = accumulate(ALL(ps), 0ll);

  vector<vii> adj(n);
  for (auto [u, v, w] : edges) {
    adj[u].push_back({v, w}), adj[v].push_back({u, w});
  }

  viii new_edges;
  fore(j, 0, s) {
    auto [u, c] = shelters[j];
    vi dist = dijkstra(adj, u);
    fore(i, 0, n) {
      new_edges.push_back({dist[i], i, j});
    }
  }

  sort(ALL(new_edges));

  ll l = -1, r = new_edges.size() - 1;
  while (l + 1 < r) {
    ll m = (l + r) / 2;

    Dinic D((1 << s) + s + 2);


    vi left_neights(n);
    fore(k, 0, m + 1) {
      auto [_, i, j] = new_edges[k];
      left_neights[i] |= (1 << j);
    }

    vi new_left_caps(1 << s);
    fore(i, 0, n) {
      new_left_caps[left_neights[i]] += ps[i];
    }

    //cerr << "dinic\n";
    fore(x, 0, 1 << s) {
      D.addEdge(0, x + 1, new_left_caps[x]);
    }
    fore(j, 0, s) {
      D.addEdge((1 << s) + 1 + j, (1 << s) + s + 1, shelters[j].second);
    }

    fore(x, 0, 1 << s) {
      fore(j, 0, s) {
        if (x & (1 << j)) {
          D.addEdge(1 + x, 1 + (1 << s) + j, inf);
        }
      }
    }

    ll v = D.calc(0, 1 + (1 << s) + s);
    if (v == total_ps) {
      r = m;
    } else {
      l = m;
    }
  }

  return get<0>(new_edges[l + 1]);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, m, s;
  cin >> n >> m >> s;
  vi ps(n);
  for (ll& p : ps) {
    cin >> p;
  }
  viii edges(m);
  for (auto& [u, v, w] : edges) {
    cin >> u >> v >> w;
    u--, v--;
  }
  vii shelters(s);
  for (auto& [u, c] : shelters) {
    cin >> u >> c;
    u--;
  }

  auto ans = solve(ps, edges, shelters);
  cout << ans << '\n';

}
