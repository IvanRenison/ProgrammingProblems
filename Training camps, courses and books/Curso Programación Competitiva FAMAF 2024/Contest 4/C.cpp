// https://codeforces.com/group/gmV7IkT2pN/contest/525522/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef vector<int> vi;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

/** Author: Pietro Palombini
 * Date: 2024-03-01
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure, with support for
 * storing additional data in each set.
 * Time: O(\alpha(N))$
 * Status: tested on CSES: Road Construction
 */
typedef ull D;
struct UFStore {
  void merge(D& large, const D& small) { large = min(large, small); }
  vi e;
  vector<D> d;
  UFStore(int n) : e(n, -1), d(n) {}
  UFStore(const vector<D>& d) : e(d.size(), -1), d(d) {}
  D& find(int x) { return d[repr(x)]; }
  int repr(int x) { return e[x] < 0 ? x : e[x] = repr(e[x]); }
  bool join(int a, int b) {
    a = repr(a), b = repr(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b], e[b] = a, merge(d[a], d[b]);
    return true;
  }
};

ull solve(const vu& cs, const vuu& edges) {
  ull n = cs.size();

  UFStore uf(cs);

  for (auto [u, v] : edges) {
    uf.join(u, v);
  }

  ull ans = 0;

  fore(i, 0, n) {
    if (uf.repr(i) == i) {
      ans += uf.find(i);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, m;
  cin >> n >> m;

  vu cs(n);
  for (ull& c : cs) {
    cin >> c;
  }

  vuu edges(m);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  ull ans = solve(cs, edges);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
