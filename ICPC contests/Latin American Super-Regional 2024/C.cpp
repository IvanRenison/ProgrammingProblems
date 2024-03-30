// https://codeforces.com/gym/105053/problem/C

/* #ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif */

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
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

/** Author: Chen Xing
 * Date: 2009-10-13
 * License: CC0
 * Source: N/A
 * Description: Fast bipartite matching algorithm. Graph g$ should be a list
 * of neighbors of the left partition, and btoa$ should be a vector full of
 * -1's of the same size as the right partition. Returns the size of
 * the matching. btoa[i]$ will be the match for vertex i$ on the right side,
 * or $-1$ if it's not matched.
 * Usage: vi btoa(m, -1); hopcroftKarp(g, btoa);
 * Time: O(\sqrt{V}E)
 * Status: stress-tested by MinimumVertexCover, and tested on oldkattis.adkbipmatch and SPOJ:MATCHING
 */
bool dfs(ll a, ll L, vector<vu>& g, vi& btoa, vi& A, vi& B) {
  if (A[a] != L) return 0;
  A[a] = -1;
  for (ll b : g[a]) if (B[b] == L + 1) {
    B[b] = 0;
    if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
      return btoa[b] = a, 1;
  }
  return 0;
}

ll hopcroftKarp(vector<vu>& g, vi& btoa) {
  ll res = 0;
  vi A(g.size()), B(btoa.size()), cur, next;
  for (;;) {
    fill(ALL(A), 0);
    fill(ALL(B), 0);
    cur.clear();
    for (ll a : btoa) if(a != -1) A[a] = -1;
    fore(a,0,SZ(g)) if(A[a] == 0) cur.push_back(a);
    for (ll lay = 1;; lay++) {
      bool islast = 0;
      next.clear();
      for (ll a : cur) for (ll b : g[a]) {
        if (btoa[b] == -1) {
          B[b] = lay;
          islast = 1;
        }
        else if (btoa[b] != a && !B[b]) {
          B[b] = lay;
          next.push_back(btoa[b]);
        }
      }
      if (islast) break;
      if (next.empty()) return res;
      for (ll a : next) A[a] = lay;
      cur.swap(next);
    }
    fore(a,0,SZ(g))
      res += dfs(a, 0, g, btoa, A, B);
  }
}


ull solveGraph(const vector<vu>& adj) {
  ull n = adj.size();

  ull ans = 0;

  vu vis(n, inf);

  fore(u, 0, n) {
    if (vis[u] == inf) {
      vector<map<ull, ull>> comp_vals = {{{u, 0}}, {}};

      vis[u] = 0;
      vu s = {u};

      while (!s.empty()) {
        ull v = s.back();
        s.pop_back();

        for (ull w : adj[v]) {
          if (vis[w] == inf) {
            vis[w] = !vis[v];
            comp_vals[vis[w]][w] = comp_vals[vis[w]].size();
            s.push_back(w);
          }
          assert(vis[w] == !vis[v]);
        }
      }

      ull k0 = comp_vals[0].size();
      ull k1 = comp_vals[1].size();



      vector<vu> comp(k0);

      for (auto [v, i] : comp_vals[0]) {
        for (ull w : adj[v]) {
          assert(vis[w] == 1);
          comp[i].push_back(comp_vals[1][w]);
        }
      }

      vi btoa(k1, -1);

      ull max_matching = hopcroftKarp(comp, btoa);

      if (max_matching < max(k0, k1)) {
        { // 0 colored vertexes
          fore(i, 0, k0) {
            vector<vu> comp_ = comp;
            comp_[i].clear();

            vi btoa_(k1, -1);

            ull this_matching = hopcroftKarp(comp_, btoa_);

            if (this_matching == max_matching) {
              ans++;
            }
          }
        }
        { // 1 colored vertexes
          fore(i, 0, k1) {
            vector<vu> comp_(k0);
            fore(j, 0, k0) {
              for (ull w : comp[j]) {
                if (w != i) {
                  comp_[j].push_back(w);
                }
              }
            }

            vi btoa(k1, -1);

            ull this_matching = hopcroftKarp(comp_, btoa);

            if (this_matching == max_matching) {
              ans++;
            }
          }

        }
      }
    }
  }

  return ans;
}

ull solve(const vector<string>& grid) {
  ull N = grid.size(), M = grid[0].size();

  vector<vu> adj(N * M);

  ull count = 0;

  fore(i, 0, N) {
    fore(j, 0, M) {
      if (grid[i][j] == '.') {
        if (i > 0 && grid[i - 1][j] == '.') {
          adj[i * M + j].push_back((i - 1) * M + j);
        }
        if (j > 0 && grid[i][j - 1] == '.') {
          adj[i * M + j].push_back(i * M + j - 1);
        }
        if (i < N - 1 && grid[i + 1][j] == '.') {
          adj[i * M + j].push_back((i + 1) * M + j);
        }
        if (j < M - 1 && grid[i][j + 1] == '.') {
          adj[i * M + j].push_back(i * M + j + 1);
        }
      } else {
        count++;
      }
    }
  }

  ull ans = solveGraph(adj) - count;

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N, M;
  cin >> N >> M;
  vector<string> grid(N);
  for (string& row : grid) {
    cin >> row;
  }

  auto ans = solve(grid);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
