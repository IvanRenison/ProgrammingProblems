// https://codeforces.com/contest/1976/problem/F

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

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
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

vu solve(vuu& edges) {
  ull n = edges.size() + 1;

  vector<vu> adj(n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vu faths(n, inf); // fathers
  function<void(ull, ull)> dfs0 = [&](ull u, ull p) {
    faths[u] = p;
    for (ull v : adj[u]) if (v != p) {
      dfs0(v, u);
    }
  };
  dfs0(0, inf);


  vu depth(n), depth_rec(n, inf);

  function<ull(ull, ull)> dfs1 = [&](ull u, ull p) -> ull {
    depth[u] = 0;
    for (ull v : adj[u]) if (v != p) {
      ull d = dfs1(v, u) + 1;
      if (d > depth[u]) {
        depth[u] = d;
        depth_rec[u] = v;
      }
    }
    return depth[u];
  };
  dfs1(0, 0);

  priority_queue<uu> pq;
  pq.push({depth[0], 0});

  vu ans = {0};
  bool start = true;
  while (!pq.empty()) {
    if (start) {
      start = false;
      vu news;
      fore(i, 0, 2) if (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (i == 0) {
          ans.push_back(ans.back() + d + (u != 0));
        } else {
          ans.back() += d + 1;
        }

        news.push_back(u);
      }
      for (ull u : news) {
        while (u != inf) {
          for (ull v : adj[u]) if (v != faths[u] && v != depth_rec[u]) {
            pq.push({depth[v], v});
          }
          u = depth_rec[u];
        }
      }
    } else {
      auto [d, u] = pq.top();
      pq.pop();
      ans.push_back(ans.back() + d + (u != 0));
      while (u != inf) {
        for (ull v : adj[u]) if (v != faths[u] && v != depth_rec[u]) {
          pq.push({depth[v], v});
        }
        u = depth_rec[u];
      }
      if (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        ans.back() += d + 1;
        while (u != inf) {
          for (ull v : adj[u]) if (v != faths[u] && v != depth_rec[u]) {
            pq.push({depth[v], v});
          }
          u = depth_rec[u];
        }
      }
    }
  }

  assert(ans.back() == n - 1);

  vu real_ans(n - 1);
  fore(i, 1, ans.size() - 1) {
    real_ans[i - 1] = n - 1 - ans[i];
  }

  return real_ans;
}



int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vuu edges(n - 1);
    fore(j, 0, n - 1) {
      ull u, v;
      cin >> u >> v;
      u--, v--;
      edges[j] = {u, v};
    }

    auto ans = solve(edges);
    for (ull x : ans) {
      cout << x << " ";
    }
    cout << '\n';
  }

}
