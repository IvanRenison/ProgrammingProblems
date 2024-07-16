// https://codeforces.com/group/5GNF7zti59/contest/534709/problem/G
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((ll)x.size())
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
using namespace std;
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

//#include <bits/extc++.h>
//#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/priority_queue.hpp"

const ll INF = numeric_limits<ll>::max() / 4;

struct MCMF {
  struct edge {
    ll from, to, rev;
    ll cap, cost, flow;
  };
  ll N;
  vector<vector<edge>> ed;
  vi seen;
  vi dist, pi;
  vector<edge*> par;

  MCMF(ll N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}

  void addEdge(ll from, ll to, ll cap, ll cost) {
    if (from == to)
      return;
    ed[from].pb(edge{from, to, SZ(ed[to]), cap, cost, 0});
    ed[to].pb(edge{to, from, SZ(ed[from]) - 1, 0, -cost, 0});
  }

  void path(ll s) {
    fill(ALL(seen), 0);
    fill(ALL(dist), INF);
    dist[s] = 0;
    ll di;

    __gnu_pbds::priority_queue<ii> q;
    vector<decltype(q)::point_iterator> its(N);
    q.push({0, s});

    while (!q.empty()) {
      s = q.top().snd;
      q.pop();
      seen[s] = 1;
      di = dist[s] + pi[s];
      for (edge& e : ed[s])
        if (!seen[e.to]) {
          ll val = di - pi[e.to] + e.cost;
          if (e.cap - e.flow > 0 && val < dist[e.to]) {
            dist[e.to] = val;
            par[e.to] = &e;
            if (its[e.to] == q.end())
              its[e.to] = q.push({-dist[e.to], e.to});
            else
              q.modify(its[e.to], {-dist[e.to], e.to});
          }
        }
    }
    fore(i, 0, N) pi[i] = min(pi[i] + dist[i], INF);
  }

  ii maxflow(ll s, ll t) {
    ll totflow = 0, totcost = 0;
    while (path(s), seen[t]) {
      ll fl = INF;
      for (edge* x = par[t]; x; x = par[x->from])
        fl = min(fl, x->cap - x->flow);

      totflow += fl;
      for (edge* x = par[t]; x; x = par[x->from]) {
        x->flow += fl;
        ed[x->to][x->rev].flow -= fl;
      }
    }
    fore(i, 0, N) for (edge& e : ed[i]) totcost += e.cost * e.flow;
    return {totflow, totcost / 2};
  }
};

int main(){
  ios::sync_with_stdio(0), cin.tie(0);

  string t;
  cin >> t;
  vi t_cnt(26);
  for(char c : t) t_cnt[c - 'a']++;

  ll n;
  cin >> n;
  vector<string> ss(n);
  vi a(n);
  vector<vi> cnt(n, vi(26));
  fore(i, 0, n) {
    cin >> ss[i] >> a[i];
    for(char c : ss[i]) cnt[i][c - 'a']++;
  }

  MCMF mcmf(27 * n + 28);

  auto id_si = [&](ll i) {
    assert(0 <= i && i < n);
    return i;
  };

  auto id_sic =
      [&](ll i, char c) {
        ll ans = n + 26 * i + (c - 'a');
        assert(n <= ans && ans < 27 * n);
        return ans;
      };

  auto id_tc =
      [&](char c) {
        ll ans = 27 * n + (c - 'a');
        assert(27 * n <= ans && ans < 27 * n + 26);
        return ans;
      };

  ll source = 27 * n + 26,
       sink = 27 * n + 27;

  fore(i, 0, n) {
    mcmf.addEdge(source, id_si(i), a[i], 0);
    fore(c, 'a', 'z' + 1) {
      mcmf.addEdge(id_si(i), id_sic(i, c), cnt[i][c - 'a'],  0);
      mcmf.addEdge(id_sic(i, c), id_tc(c), (ll)1e9, i + 1);
    }
  }
  fore(c, 'a', 'z' + 1) {
    mcmf.addEdge(id_tc(c), sink, t_cnt[c - 'a'], 0);
  }

  auto [flow, cost] = mcmf.maxflow(source, sink);

  if (flow != SZ(t)) {
    cout << -1 << "\n";
    return 0;
  }

  cout << cost << "\n";
}