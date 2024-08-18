#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef pair<ll,ll> vii;
typedef tuple<ll,ll,ll> iii;
typedef vector<iii> viii;
typedef tuple<ll,ll,ll,ll> iiii;
typedef vector<iiii> viiii;

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

ll solve(ll N, viiii& edges, ll t) {

  vector<viii> adj(N);

  for (auto [a, b, x, y] : edges) {
    adj[a].push_back({b, x, y});
    adj[b].push_back({a, x, y});
  }

  vector<bool> vis(N, false);

  rpriority_queue<ii> pq;
  pq.push({t, 0});

  while (!pq.empty()) {
    auto [t, u] = pq.top();
    pq.pop();

    if (u + 1 == N) {
      return t;
    }
    if (vis[u]) {
      continue;
    }
    vis[u] = true;


    for (auto [v, x, y] : adj[u]) {
      if (!vis[v]) {
        ll xy = x + y;
        ll t_ = (t / xy) * xy;
        if (t < t_ + x) {
          pq.push({t, v});
        } else {
          pq.push({t_ + xy, v});
        }
      }
    }
  }

  assert(false);
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll N, M, t;
  cin >> N >> M >> t;
  viiii edges(M);
  for (auto& [a, b, x, y] : edges) {
    cin >> a >> b >> x >> y;
    a--, b--;
  }

  ll ans = solve(N, edges, t);

  cout << ans << '\n';

}