// https://atcoder.jp/contests/abc369/tasks/abc369_a

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
void floydWarshall(vector<vu>& m) {
  ll n = SZ(m);
  fore(i,0,n) m[i][i] = min(m[i][i], 0ULL);
  fore(k,0,n) fore(i,0,n) fore(j,0,n)
    if (m[i][k] != inf && m[k][j] != inf) {
      auto newDist = m[i][k] + m[k][j];
      m[i][j] = min(m[i][j], newDist);
    }
}

vu solve(ull N, vuuu& edges, vector<vu>& queries) {
  ull Q = SZ(queries);

  vector<vu> dist(N, vu(N, inf));
  for (auto [U, V, T] : edges) {
    dist[U][V] = min(dist[U][V], T);
    dist[V][U] = min(dist[V][U], T);
  }

  floydWarshall(dist);


  vu ans(Q, inf);
  fore(q, 0, Q) {
    vu query = queries[q];
    sort(ALL(query));

    do {
      ull K = SZ(query);
      ull base_ans = 0;
      vuu ed_;
      fore(i, 0, K) {
        auto [u, v, T] = edges[query[i]];
        base_ans += T;
        ed_.push_back({u, v});
      }

      fore(x, 0, 1 << K) {
        vuu ed = ed_;
        fore(i, 0, K) if (x & (1 << i)) {
          auto [u, v] = ed[i];
          ed[i] = {v, u};
        }

        ull this_ans = base_ans;
        this_ans += dist[0][ed[0].first] + dist[ed.back().second][N - 1];
        fore(i, 0, K - 1) {
          this_ans += dist[ed[i].second][ed[i + 1].first];
        }

        ans[q] = min(ans[q], this_ans);
      }

    } while (next_permutation(ALL(query)));

  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N, M;
  cin >> N >> M;
  vuuu edges(M);
  for (auto& [U, V, T] : edges) {
    cin >> U >> V >> T;
    U--, V--;
  }
  ull Q;
  cin >> Q;
  vector<vu> queries(Q);
  for (vu& query : queries) {
    ull K;
    cin >> K;
    query.resize(K);
    for (ull& B : query) {
      cin >> B;
      B--;
    }
  }

  auto ans = solve(N, edges, queries);
  for (ull A : ans) {
    cout << A << '\n';
  }

}
