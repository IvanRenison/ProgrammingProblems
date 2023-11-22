// https://matcomgrader.com/problem/9549/highway-decommission/

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ull inf = 1ull << 60;

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

ull solve(ull N, const vuuuu& edges) {
  vector<vuuu> adj(N);
  for (auto it : edges) {
    // [u, v, L, C] = it
    ull u = get<0>(it), v = get<1>(it), L = get<2>(it), C = get<3>(it);
    adj[u].push_back(uuu{v, L, C});
    adj[v].push_back(uuu{u, L, C});
  }

  ull ans = 0;
  rpriority_queue<uuu> q;
  vuu dist(N, {inf, inf});

  q.push(uuu{0, 0, 0});
  dist[0] = {0, 0};

  while (!q.empty()) {
    auto it = q.top();
    // [d, c_, u] = it
    ull d = get<0>(it), c_ = get<1>(it), u = get<2>(it);
    q.pop();

    if (dist[u] < uu{d, c_}) {
      continue;
    }

    ans += c_;

    for (auto it : adj[u]) {
      // [v, Lv, Cv] = it
      ull v = get<0>(it), Lv = get<1>(it), Cv = get<2>(it);
      if (uu{d + Lv, Cv} < dist[v]) {
        q.push(uuu{d + Lv, Cv, v});
        dist[v] = {d + Lv, Cv};
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, M;
  cin >> N >> M;
  vuuuu edges(M);
  fore(i, 0, M) {
    ull A, B, L, C;
    cin >> A >> B >> L >> C;
    A--, B--;
    edges[i] = uuuu{A, B, L, C};
  }

  auto ans = solve(N, edges);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
