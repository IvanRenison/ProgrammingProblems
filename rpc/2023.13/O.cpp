// https://redprogramacioncompetitiva.com/contests/2023/13

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef tuple<ull, ull, ull> uuu;
typedef tuple<ll, ll, ll> iii;
typedef vector<uuu> vuuu;
typedef vector<iii> viii;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<uuuu> vuuuu;
typedef vector<iiii> viiii;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<uuuuu> vuuuuu;
typedef vector<iiiii> viiiii;
typedef long double ld;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

ull solve(ull N, const vuuu& edges, const vuuuu& blocks) {

  map<uu, pair<ull, vuu>> edges_map;

  vector<vu> adj(N);
  for(auto [u, v, t] : edges) {
    adj[u].push_back({v});
    adj[v].push_back({u});

    uu ed = {min(u, v), max(u, v)};

    edges_map[ed] = {t, {}};
  }

  for (auto [u, v, l, r] : blocks) {
    uu ed = {min(u, v), max(u, v)};
    edges_map[ed].second.push_back({l, r});
  }

  for (auto& [k, v] : edges_map) {
    sort(all(v.second));
  }

  rpriority_queue<uu> q;
  vu dis(N, inf);

  q.push({0, 0});

  while (!q.empty()) {
    auto [t, u] = q.top();
    q.pop();

    if (dis[u] <= t) continue;

    dis[u] = t;

    for (auto v : adj[u]) {
      ull this_t = t;
      uu ed = {min(u, v), max(u, v)};
      auto& [te, blocks] = edges_map[ed];
      ull nblocks = blocks.size();

      ull i = 0;
      while (i < nblocks && blocks[i].first < this_t + te) {
        this_t = max(this_t, blocks[i].second);
        i++;
      }

      if (dis[v] > this_t + te) {
        q.push({this_t + te, v});
      }
    }
  }

  return dis[N - 1];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, m, d;
  cin >> N >> m >> d;

  vuuu edges(m);
  for(auto& [u, v, t] : edges) {
    cin >> u >> v >> t;
    u--, v--;
  }

  vuuuu blocks(d);
  for(auto& [u, v, l, r] : blocks) {
    cin >> u >> v >> l >> r;
    u--, v--;
  }

  auto ans = solve(N, edges, blocks);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
