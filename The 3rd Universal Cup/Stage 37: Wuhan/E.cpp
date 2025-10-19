// https://contest.ucup.ac/contest/2025/problem/10740
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;


vi eulerWalk(vector<vii>& gr, ll nedges, ll src=0) {
  ll n = SZ(gr);
  vi D(n), its(n), eu(nedges), ret, s = {src};
  D[src]++; //
  while (!s.empty()) {
    ll x = s.back(), &it = its[x], end = SZ(gr[x]);
    if (it == end) { ret.pb(x), s.pop_back(); continue; }
    auto [y, e] = gr[x][it++];
    if (!eu[e]) D[x]--, D[y]++, eu[e] = 1, s.pb(y);
  }
  for (ll x : D) if (x < 0 || SZ(ret) != nedges + 1) return {};
  return {ret.rbegin(), ret.rend()};
}



vi solveComp(ll n, vii edges) {
  ll m = edges.size();

  vi deg(n);
  for (auto [u, v] : edges) {
    deg[u]++, deg[v]++;
  }

  vi odd;
  fore(u, 0, n) {
    if (deg[u] % 2 == 1) {
      odd.push_back(u);
    }
  }

  assert(odd.size() % 2 == 0);

  for (ll i = 0; i < odd.size(); i += 2) {
    edges.push_back({odd[i], odd[i + 1]});
  }

  map<ii, vi> e_map;
  vector<vii> gr(n);
  fore(e, 0, edges.size()) {
    auto [u, v] = edges[e];
    gr[u].push_back({v, e}), gr[v].push_back({u, e});
    e_map[minmax(u, v)].push_back(e);
  }

  vi euler = eulerWalk(gr, edges.size());

  ll c = 0;
  vi ans(edges.size(), -1);
  vii current = {{euler[0], -1}};;
  vector<bool> in_current(n, false);
  in_current[euler[0]] = true;

  fore(i, 1, euler.size()) {
    ll u = euler[i - 1], v = euler[i];

    if (in_current[v]) {
      ans[e_map[minmax(u, v)].back()] = c;
      e_map[minmax(u, v)].pop_back();
      while (v != current.back().first) {
        assert(current.size() > 1);
        ans[current.back().second] = c;
        in_current[current.back().first] = false;
        current.pop_back();
      }

      c++;
    } else {
      current.push_back({v, e_map[minmax(u, v)].back()});
      e_map[minmax(u, v)].pop_back();
      in_current[v] = true;
    }
  }

  assert(current.size() == 1);

  while (ans.size() > m) {
    ans.pop_back();
  }

  return ans;
}


vi solve(ll n, vii& edges) {
  ll m = edges.size();

  vector<vii> adj(n);
  fore(e, 0, m) {
    auto [u, v] = edges[e];
    adj[u].push_back({v, e}), adj[v].push_back({u, e});
  }


  vector<bool> vis(n, false);
  vector<vi> comps;
  vector<vi> comps_e;
  fore(u, 0, n) if (!vis[u]) {
    comps.push_back({u});
    comps_e.push_back({});
    vis[u] = true;

    vi s = {u};
    while (!s.empty()) {
      ll v = s.back();
      s.pop_back();

      for (auto [w, e] : adj[v]) {
        {
          if (v < w) {
            comps_e.back().push_back(e);
          }
        }
        if (!vis[w]) {
          comps.back().push_back(w);
          s.push_back(w);
          vis[w] = true;
        }
      }
    }
  }

  vi ans(m, -1);
  fore(i_comp, 0, comps.size()) if (comps[i_comp].size() > 1) {
    vi& comp = comps[i_comp];

    ll new_n = comp.size();

    vi& es = comps_e[i_comp];

    if (new_n == 2) {
      assert(es.size() == 1);
      ans[es[0]] = 0;
    } else {

      sort(ALL(comp));

      vii new_edges;
      for (ll e : es) {
        auto [u, v] = edges[e];

        ll new_u = lower_bound(ALL(comp), u) - comp.begin();
        ll new_v = lower_bound(ALL(comp), v) - comp.begin();

        new_edges.push_back({new_u, new_v});
      }

      vi new_ans = solveComp(new_n, new_edges);

      fore(new_e, 0, new_edges.size()) {
        ans[es[new_e]] = new_ans[new_e];
      }
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll T;
  cin >> T;
  while (T--) {
    ll n, m;
    cin >> n >> m;
    vii edges(m);
    for (auto& [u, v] : edges) {
      cin >> u >> v;
      u--, v--;
    }

    vi ans = solve(n, edges);
    for (ll c : ans) {
      cout << c + 1 << ' ';
    }
    cout << '\n';
  }



}