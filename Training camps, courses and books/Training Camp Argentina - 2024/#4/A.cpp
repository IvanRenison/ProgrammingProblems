// https://codeforces.com/group/5GNF7zti59/contest/535722/problem/A
#include <bits/stdc++.h>
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

const ll inf = 1ll << 60;

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

ll diff(ll x, ll y) {
  return abs(x - y);
}

ll solve(ll sx, ll sy, ll fx, ll fy, const vii& xys) {
  ll m = xys.size();

  viii xys_i(m), yxs_i(m);
  fore(i, 0, m) {
    auto [x, y] = xys[i];
    xys_i[i] = {x, y, i};
    yxs_i[i] = {y, x, i};
  }
  sort(ALL(xys_i));
  sort(ALL(yxs_i));

  ll N = m + 2;
  viii edges;
  edges.push_back({0, m + 1, diff(sx, fx) + diff(sy, fy)});

  fore(i, 0, m) {
    auto [x, y] = xys[i];
    edges.push_back({0, i + 1, min(diff(sx, x), diff(sy, y))});
    edges.push_back({i + 1, m + 1, diff(fx, x) + diff(fy, y)});
  }

  fore(i, 0, m - 1) {
    auto [xi, yi, i_] = xys_i[i];
    auto [xj, yj, j_] = xys_i[i + 1];
    edges.push_back({i_ + 1, j_ + 1, xj - xi});
  }

  fore(i, 0, m - 1) {
    auto [yi, xi, i_] = yxs_i[i];
    auto [yj, xj, j_] = yxs_i[i + 1];
    edges.push_back({i_ + 1, j_ + 1, yj - yi});
  }

  vector<vii> adj(N);
  for (auto [u, v, w] : edges) {
    adj[u].push_back({v, w}), adj[v].push_back({u, w});
  }

  vi dist(N, inf);
  rpriority_queue<ii> pq;
  pq.push({0, 0});

  while (!pq.empty()) {
    auto [u, d] = pq.top();
    pq.pop();

    if (dist[u] < d) {
      continue;
    }

    if (u == m + 1) {
      return d;
    }

    for (auto [v, w] : adj[u]) {
      if (dist[v] > d + w) {
        dist[v] = d + w;
        pq.push({v, d + w});
      }
    }
  }

  assert(false);
}

ll force(ll sx, ll sy, ll fx, ll fy, const vii& xys) {
  ll m = xys.size();
  ll N = m + 2;
  viii edges;
  edges.push_back({0, m + 1, diff(sx, fx) + diff(sy, fy)});

  fore(i, 0, m) {
    auto [x, y] = xys[i];
    edges.push_back({0, i + 1, min(diff(sx, x), diff(sy, y))});
    edges.push_back({i + 1, m + 1, diff(fx, x) + diff(fy, y)});
  }

  fore(i, 0, m) {
    auto [xi, yi] = xys[i];
    fore(j, i + 1, m) {
      auto [xj, yj] = xys[j];
      edges.push_back({i + 1, j + 1, min(diff(xi, xj), diff(yi, yj))});
    }
  }

  vector<vii> adj(N);
  for (auto [u, v, w] : edges) {
    adj[u].push_back({v, w}), adj[v].push_back({u, w});
  }

  vector<bool> vis(N, false);
  rpriority_queue<ii> pq;
  pq.push({0, 0});

  while (!pq.empty()) {
    auto [u, d] = pq.top();
    pq.pop();

    if (vis[u]) {
      continue;
    }

    vis[u] = true;

    if (u == m + 1) {
      return d;
    }

    for (auto [v, w] : adj[u]) {
      if (!vis[v]) {
        pq.push({v, d + w});
      }
    }
  }

  assert(false);
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

#ifndef TEST
  ll n, m;
  cin >> n >> m;
  ll sx, sy, fx, fy;
  cin >> sx >> sy >> fx >> fy;
  vii xys(m);
  for (auto& [x, y] : xys) {
    cin >> x >> y;
  }

  cout << solve(sx, sy, fx, fy, xys) << '\n';

#else
  fore(_, 0, 100000) {
    ll m = rand() % 10;
    ll sx = rand() % 20, sy = rand() % 20, fx = rand() % 20, fy = rand() % 20;
    vii xys(m);
    for (auto [x, y] : xys) {
      x = rand() % 20;
      y = rand() % 20;
    }

    ll ans = solve(sx, sy, fx, fy, xys);
    ll ansf = force(sx, sy, fx, fy, xys);
    assert(ans == ansf);
  }
#endif

}