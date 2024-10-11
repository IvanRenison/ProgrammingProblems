// https://codeforces.com/gym/101630
#include <bits/stdc++.h>
#define ALL(x) x.begin(), x.end()
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define SZ(x) (ll(x.size()))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;

const ll inf = 1ll << 60;

template<typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

ll solve(ll n, ll k, viii& edges) {
  vector<vii> adj(n);
  ll max_w = 0;
  for (auto [u, v, w] : edges) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
    max_w = max(max_w, w);
  }

  vi dis(n, inf);
  rpriority_queue<ii> pq;
  pq.push({0, 0});
  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    if (dis[u] == inf) {
      dis[u] = d;
      for (auto [v, w] : adj[u]) {
        pq.push({d+w, v});
      }
    }
  }

  ll ans = dis[n-1];

  for (auto [_, __, W] : edges) {
    vii dis(n, {inf, inf});
    rpriority_queue<iii> pq;
    pq.push({0, 0, 0});
    while (!pq.empty()) {
      auto [d, u, c] = pq.top();
      pq.pop();

      if (dis[u].first == inf) {
        dis[u] = {d, c};
        for (auto [v, w] : adj[u]) {
          pq.push({d + max(w - W, 0ll), v, c + (w >= W)});
        }
      }
    }

    auto [d, c] = dis[n-1];
    if (c >= k) {
      ll this_ans = d + W * k;
      ans = min(ans, this_ans);
    }
  }

  return ans;
}


int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n, m, k;
  cin >> n >> m >> k;

  viii edges(m);
  for (auto& [u, v, w] : edges) {
    cin >> u >> v >> w;
    u--, v--;
  }
  cout << solve(n, k, edges) << '\n';
}
