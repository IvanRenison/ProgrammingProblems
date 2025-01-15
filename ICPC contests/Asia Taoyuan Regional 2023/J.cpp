// https://codeforces.com/gym/105544
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define ALL(x) x.begin(),x.end()
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll,ll,ll> iii;
typedef vector<iii> viii;

pair<ll, optional<vi>> solve(vi& nodes, viii& edges) {
  ll n = nodes.size();

  vector<vii> adj_back(n);
  vi deg_ford(n, 0);
  for (auto [u, v, w] : edges) {
    adj_back[v].push_back({u, w});
    deg_ford[u]++;
  }

  viii dp(n, {-1, -1, -1});

  auto f = [&](ll u, auto&& f) -> iii {
    auto& [ans, ans_count, ans_prev] = dp[u];

    if (ans != -1) {
      return dp[u];
    }

    if (adj_back[u].size() == 0) {
      ans = nodes[u];
      ans_count = 1;
    } else {
      ans = -1;
      for (auto [v, w] : adj_back[u]) {
        auto [vans, vans_count, vans_prev] = f(v, f);
        if (vans + w + nodes[u] > ans) {
          ans = vans + w + nodes[u];
          ans_count = vans_count;
          ans_prev = v;
        } else if (vans + w + nodes[u] == ans) {
          ans_count += vans_count;
          if (ans_count > 2) ans_count = 2;
        }
      }
    }

    return {ans, ans_count, ans_prev};
  };

  fore(u, 0, n) {
    if (deg_ford[u] == 0) {
      auto [ans, ans_count, ans_prev] = f(u, f);
      if (ans_count != 1) {
        return {ans, {}};
      }

      vi path = {u};
      while (ans_prev != -1) {
        path.push_back(ans_prev);
        ans_prev = get<2>(dp[ans_prev]);
      }

      reverse(ALL(path));

      return {ans, {path}};
    }
  }

  assert(false);
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  while (!cin.eof()) {
    ll n, m;
    cin >> n >> m;
    if (cin.eof()) break;
    vi nodes(n);
    string s;
    cin >> s;
    fore(i, 0, s.size()) {
      if (s[i] == ',') {
        s[i] = ' ';
      }
    }
    stringstream ss(s);
    for (ll& x : nodes) {
      ss >> x;
    }

    viii edges(m);
    for (auto& [u, v, w] : edges) {
      cin >> u >> v >> w;
    }

    auto [val, path] = solve(nodes, edges);
    cout << val;
    if (path.has_value()) {
      for (ll u : *path) {
        cout << ',' << u;
      }
      cout << '\n';
    } else {
      cout << ",M\n";
    }
  }

}