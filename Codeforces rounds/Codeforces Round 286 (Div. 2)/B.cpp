// https://codeforces.com/contest/505/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

class UnionFind {
public:
  ull n;
  vector<ull> reprs; // representants

  UnionFind(ull n) {
    this->n = n;
    reprs = vector<ull>(n);

    fore(i, 0, n) {
      reprs[i] = i;
    }
  }

  /* Find the repentant of a element */
  ull find(ull x) {
    assert(x < n);
    if (reprs[x] == x) {
      return x;
    } else {
      ull r = find(reprs[x]);
      reprs[x] = r;
      return r;
    }
  }

  /* Return true iff they have the same representant */
  bool are_same(ull x, ull y) {
    return find(x) == find(y);
  }

  /* Change the representant of the group of a element and return the old representant */
  ull find_assign(ull x, ull n_r) {
    assert(x < n);
    if (reprs[x] == x) {
      reprs[x] = n_r;
      return x;
    } else {
      ull old_r = reprs[x];
      reprs[x] = n_r;
      return find_assign(old_r, n_r);
    }
  }

  /* Join to parts, if they were already connected return true, else return false */
  bool join(ull x, ull y) {
    ull r_x = find(x);
    ull r_y = find_assign(y, r_x);
    return r_x == r_y;
  }
};

typedef ull Vertex;
typedef ull Color;
typedef tuple<Vertex, Vertex, Color> cEdge;

pair<ull, vector<cEdge>> readColoredGraph() {
  ull n, m;
  cin >> n >> m;

  vector<cEdge> edges(m);
  fore(i, 0, m) {
    ull u, v, c;
    cin >> u >> v >> c;
    edges[i] = {u - 1, v - 1, c - 1};
  }

  return {n, edges};
}

/* Return a UnionFind for each color */
vector<UnionFind> init(ull n, vector<cEdge> edges) {
  ull m = edges.size();

  // There are up to m colors
  vector<UnionFind> ufs(m, UnionFind(n));

  for (auto [u, v, c] : edges) {
    ufs[c].join(u, v);
  }

  return ufs;
}

ull query(vector<UnionFind> ufs, ull u, ull v) {
  ull m = ufs.size();
  ull ans = 0;
  fore(i, 0, m) {
    if (ufs[i].are_same(u, v)) {
      ans++;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  auto [n, edges] = readColoredGraph();
  vector<UnionFind> ufs = init(n, edges);

  ull q;

  cin >> q;
  fore(i, 0, q) {
    ull u, v;
    cin >> u >> v;
    cout << query(ufs, u - 1, v - 1) << "\n";
  }

  return EXIT_SUCCESS;
}
