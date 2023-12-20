// https://codeforces.com/gym/104736/problem/M
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ull inf = 1ull << 60;

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

vu solve(ull N, ull P, ull G, const vuuu& edges) {

  vector<vuu> adj(N);
  for (auto [U, V, D] : edges) {
    adj[U].push_back({V, D});
    adj[V].push_back({U, D});
  }

  vu Pdist(N, inf);

  rpriority_queue<uu> q;
  q.push({0, P});

  while (!q.empty()) {
    auto [d, u] = q.top();
    q.pop();

    if (Pdist[u] != inf) {
      continue;
    }

    Pdist[u] = d;
    if (u != G) {
      for (auto [v, D] : adj[u]) {
        if (Pdist[v] == inf) {
          q.push({d + D, v});
        }
      }
    }
  }

  vu Gdist(N, inf);

  q.push({0, G});

  while (!q.empty()) {
    auto [d, u] = q.top();
    q.pop();

    if (Gdist[u] != inf) {
      continue;
    }

    Gdist[u] = d;
    for (auto [v, D] : adj[u]) {
      if (Pdist[G] + d + D < Pdist[v] && Gdist[v] == inf) {
        q.push({d + D, v});
      }
    }
  }

  vu ans;
  fore(u, 0, N) {
    if (Pdist[G] == Gdist[u]) {
      ans.push_back(u);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, M, P, G;
  cin >> N >> M >> P >> G;
  P--, G--;

  vuuu edges(M);
  for (auto& [U, V, D] : edges) {
    cin >> U >> V >> D;
    U--, V--;
  }

  auto ans = solve(N, P, G, edges);
  if (ans.size() == 0) {
    cout << '*';
  } else {
    for (ull a : ans) {
      cout << a + 1 << ' ';
    }
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
