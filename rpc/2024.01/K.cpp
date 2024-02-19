// https://redprogramacioncompetitiva.com/contests/2024/01/

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()

const ull inf = 1ull << 60;

/** Author: Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Floyd–Warshall_algorithm
 * Description: Calculates all-pairs shortest path in a directed graph that might have negative edge weights.
 * Input is an distance matrix m$, where m[i][j] = \texttt{inf}$ if i$ and j$ are not adjacent.
 * As output, m[i][j]$ is set to the shortest distance between i$ and j$, \texttt{inf} if no path,
 * or \texttt{-inf} if the path goes through a negative-weight cycle.
 * Time: O(N^3)
 * Status: slightly tested
 */
void floydWarshall(vector<vector<ull>>& m) {
  int n = sz(m);
  fore(k,0,n) fore(i,0,n) fore(j,0,n)
    m[i][j] = min(m[i][j], m[i][k] + m[k][j]);
}

/** Author: Benjamin Qi, chilli
 * Date: 2020-04-04
 * License: CC0
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Matching/Hungarian.h
 * Description: Given a weighted bipartite graph, matches every node on
 * the left with a node on the right such that no
 * nodes are in two matchings and the sum of the edge weights is minimal. Takes
 * cost[N][M], where cost[i][j] = cost for L[i] to be matched with R[j] and
 * returns (min cost, match), where L[i] is matched with
 * R[match[i]]. Negate costs for max cost. Requires N \le M$.
 * Time: O(N^2M)
 * Status: Tested on kattis:cordonbleu, stress-tested
 */
pair<ll, vi> hungarian(const vector<vi> &a) {
  if (a.empty()) return {0, {}};
  ll n = sz(a) + 1, m = sz(a[0]) + 1;
  vi u(n), v(m), p(m), ans(n - 1);
  fore(i,1,n) {
    p[0] = i;
    ll j0 = 0; // add "dummy" worker 0
    vi dist(m, inf), pre(m, -1);
    vector<bool> done(m + 1);
    do { // dijkstra
      done[j0] = true;
      ll i0 = p[j0], j1, delta = inf;
      fore(j,1,m) if (!done[j]) {
        auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
        if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
        if (dist[j] < delta) delta = dist[j], j1 = j;
      }
      fore(j,0,m) {
        if (done[j]) u[p[j]] += delta, v[j] -= delta;
        else dist[j] -= delta;
      }
      j0 = j1;
    } while (p[j0]);
    while (j0) { // update alternating path
      ll j1 = pre[j0];
      p[j0] = p[j1], j0 = j1;
    }
  }
  fore(j,1,m) if (p[j]) ans[p[j] - 1] = j - 1;
  return {-v[0], ans}; // min cost
}

ull solve(const vector<vu>& counts, vector<vu>& mat) {
  ull n = counts.size(), m = counts[0].size();

  floydWarshall(mat);

  vector<vi> costs(m, vi(n));

  fore(i, 0, m) {
    fore(j, 0, n) {
      fore(k, 0, n) {
        costs[i][j] += counts[k][i] * mat[k][j];
      }
    }
  }

  auto [ans, _] = hungarian(costs);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, m;
  cin >> n >> m;

  vector<vu> vals(n, vu(m));
  for (vu& row : vals) {
    for (ull& v : row) {
      cin >> v;
    }
  }

  vector<vu> mat(n, vu(n, inf));
  fore(i, 0, n) {
    fore(j, 0, n) {
      ll v;
      cin >> v;
      if (v >= 0) {
        mat[i][j] = v;
      }
    }
  }

  auto ans = solve(vals, mat);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
