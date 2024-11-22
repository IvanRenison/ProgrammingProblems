// https://codeforces.com/contest/2026/problem/E

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
bool dfs(ll a, ll L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
  if (A[a] != L) return 0;
  A[a] = -1;
  for (ll b : g[a]) if (B[b] == L + 1) {
    B[b] = 0;
    if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
      return btoa[b] = a, 1;
  }
  return 0;
}

ll hopcroftKarp(vector<vi>& g, vi& btoa) {
  ll res = 0;
  vi A(g.size()), B(btoa.size()), cur, next;
  for (;;) {
    fill(ALL(A), 0);
    fill(ALL(B), 0);
    cur.clear();
    for (ll a : btoa) if (a != -1) A[a] = -1;
    fore(a,0,SZ(g)) if (A[a] == 0) cur.push_back(a);
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


ull solve(vu& as) {
  ull n = as.size();
  ull m = 60;

  vector<vi> g(n);
  fore(i, 0, n) {
    ull ai = as[i];
    fore(j, 0, m) if (ai & (1ull << j)) {
      g[i].push_back(j);
    }
  }

  vi btoa(m, -1);
  ull ans = hopcroftKarp(g, btoa);
  ans = n - ans;

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu as(n);
    fore(j, 0, n) {
      cin >> as[j];
    }

    auto ans = solve(as);
    cout << ans << '\n';
  }
}
