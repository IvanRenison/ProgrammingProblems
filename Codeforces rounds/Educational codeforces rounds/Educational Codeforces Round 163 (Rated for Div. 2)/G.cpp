// https://codeforces.com/contest/1948/problem/G

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef uint8_t u8;
typedef int8_t i8;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;
typedef vector<uu> vuu;
typedef tuple<uint, uint, uint> uuu;
typedef vector<uuu> vuuu;
typedef vector<int> vi;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()

const uint inf = 1ull << 30;

/** Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: O(\alpha(N))$
 */
struct UF {
  vector<i8> e;
  UF(int n) : e(n, -1) {}
  bool sameSet(i8 a, i8 b) { return find(a) == find(b); }
  i8 size(i8 x) { return -e[find(x)]; }
  i8 find(i8 x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(i8 a, i8 b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b]; e[b] = a;
    return true;
  }
};

uint solve(uint c, const vector<vu>& adj) {
  uint n = adj.size();

  uint ans = inf;

  UF uf(n);
  vector<tuple<uint, u8, u8>> edges;

  fore(x, 1, 1 << n) {
    if (c * __builtin_popcount(x) + n - 1 >= ans) {
      continue;
    }
    edges.clear();
    for (u8 i = 0; i < n; i++) {
      if (x & (1 << i)) {
        for (u8 j = 0; j < i; j++) if (!(x & (1 << j))) {
          if (adj[i][j] > 0) {
            edges.push_back({adj[i][j], j, i});
          }
        }
        for (u8 j = i + 1; j < n; j++){
          if (adj[i][j] > 0) {
            edges.push_back({adj[i][j], i, j});
          }
        }
      }
    }

    sort(ALL(edges), [](const tuple<uint, u8, u8>& i, const tuple<uint, u8, u8>& j) {
      return get<0>(i) < get<0>(j);
    });

    fore(i, 0, n) {
      uf.e[i] = -1;
    }

    uint W = 0;
    for (auto [w, i, j] : edges) {
      if (uf.join(i, j)) {
        W += w;
        if (uf.size(i) == n) {
          uint this_ans = c * __builtin_popcount(x) + W;
          ans = min(ans, this_ans);
          break;
        }
      }
    }

  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  uint n, c;
  cin >> n >> c;
  vector<vu> adj(n, vu(n));
  for (vu& ws : adj) {
    for (uint& w : ws) {
      cin >> w;
    }
  }

  auto ans = solve(c, adj);
  cout << ans << '\n';

/*   uint n = 20, c = 1;
  vector<vu> adj(n, vu(n));
  fore(i, 0, n) {
    fore(j, i + 1, n) {
      uint w = rand() % 100;
      adj[i][j] = adj[j][i] = w;
    }
  }
  cerr << n << ' ' << c << '\n';
  for (const vu& ws : adj) {
    for (uint w : ws) {
      cerr << w << ' ';
    }
    cerr << '\n';
  } */

  return EXIT_SUCCESS;
}
