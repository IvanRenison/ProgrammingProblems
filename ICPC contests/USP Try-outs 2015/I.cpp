// https://codeforces.com/gym/101047/problem/I
#include <bits/stdc++.h>
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef tuple<ull, ull, ull> uuu;
typedef tuple<ll, ll, ll> iii;
typedef vector<uuu> vuuu;
typedef vector<iii> viii;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<uuuu> vuuuu;
typedef vector<iiii> viiii;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<uuuuu> vuuuuu;
typedef vector<iiiii> viiiii;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

/*
Usar link cut tree
Clase de tranning camp por Mati Huniquen

*/


struct T {
  ll val, e_id;

  T operator+(T o) const { // + is max
    if (val >= o.val) {
      return *this;
    } else {
      return o;
    }
  }
};

/*
Link cut tree from:
https://github.com/ngthanhtrung23/ACM_Notebook_new/blob/master/DataStructure/LinkCutTree.h
*/

// copied from https://codeforces.com/blog/entry/75885
// - Index from 1
// - T needs to support + operation
//   For subtree queries -> requires - operation
//   --> see this comment for how to handle it: https://codeforces.com/blog/entry/67637?#comment-650424
// - Not using template here, since inheritance becomes very ugly
// - Doesn't support lazy update (so no subtree updates)
// - For query on *edge* weights (instead of vertex weights)
//   --> for each edge, add a new node in LinkCut tree.
//       See https://oj.vnoi.info/problem/icpc22_mn_b for example
//
// Tested:
// - https://judge.yosupo.jp/problem/dynamic_tree_subtree_add_subtree_sum
// - https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite
// - https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum
// - (edge weights) https://oj.vnoi.info/problem/icpc22_mn_b
// - (link, cut, connected) https://www.spoj.com/problems/DYNACON1/

// Add this for path queries only
#define PATH_QUERIES_ONLY

// TODO: Specify T
// using T = long long;
// Link Cut Tree {{{
// SplayTree {{{
struct SplayTree { // can we replace SplayTreeById and use this only?
    struct Node {
        array<int, 2> child = {0, 0};
        int parent = 0;

        // Path aggregates
        // - path[0] = go from left -> right
        // - path[1] = go from right -> left
        array<T, 2> path;  // default to T constructor
        T self;

        // Subtree aggregates
        T sub, vir;

        bool reverse = false;
    };
    vector<Node> nodes;

    SplayTree(int n) : nodes(n + 1) {}

    void splay(int x) {
        for (pushDown(x); ~getDirection(x); ) {
            int y = nodes[x].parent;
            int z = nodes[y].parent;
            pushDown(z);
            pushDown(y);
            pushDown(x);
            int dx = getDirection(x);
            int dy = getDirection(y);
            if (~dy) rotate(dx != dy ? x : y);
            rotate(x);
        }
    }

// private:
    // Return t where nodes[parent(x)].child[t] == x
    int getDirection(int x) {
        int p = nodes[x].parent;
        if (!p) return -1;
        return nodes[p].child[0] == x ? 0 : nodes[p].child[1] == x ? 1 : -1;
    }

    /**
     * Before:
     *    z
     *    |
     *    y
     *   /
     *  x
     *   \
     *   xchild
     *
     * After:
     *    z
     *    |
     *    x
     *     \
     *      y
     *     /
     *   xchild
     */
    void rotate(int x) {
        int y = nodes[x].parent, dx = getDirection(x);
        int z = nodes[y].parent, dy = getDirection(y);

        setChild(y, nodes[x].child[!dx], dx);
        setChild(x, y, !dx);
        if (~dy) setChild(z, x, dy);
        nodes[x].parent = z;
    }

    void pushDown(int x) {
        if (!x) return;
        if (nodes[x].reverse) {
            auto [l, r] = nodes[x].child;
            nodes[l].reverse ^= 1;
            nodes[r].reverse ^= 1;

            swap(nodes[x].child[0], nodes[x].child[1]);
            swap(nodes[x].path[0], nodes[x].path[1]);
            nodes[x].reverse = false;
        }
    }

    void pushUp(int x) {
        auto [l, r] = nodes[x].child;
        pushDown(l); pushDown(r);

        nodes[x].path[0] = nodes[l].path[0] + nodes[x].self + nodes[r].path[0];
        nodes[x].path[1] = nodes[r].path[1] + nodes[x].self + nodes[l].path[1];

        nodes[x].sub = nodes[x].vir + nodes[l].sub + nodes[r].sub + nodes[x].self;
    }

    void setChild(int x, int y, int dir) {
        nodes[x].child[dir] = y;
        nodes[y].parent = x;
        pushUp(x);
    }
};
// }}}

struct LinkCut : SplayTree {
    LinkCut(int n) : SplayTree(n) {}

    bool is_connected(int u, int v) {
        return LCA(u, v) > 0;
    }

    void link(int u, int v) {
        reroot(u);
        access(v);

        nodes[v].vir = nodes[v].vir + nodes[u].sub;
        nodes[u].parent = v;
        pushUp(v);
    }

    void cut(int u, int v) {
        reroot(u);
        access(v);

        nodes[v].child[0] = nodes[u].parent = 0;
        pushUp(v);
    }

    // Returns 0 if u and v are not connected
    int LCA(int u, int v) {
        if (u == v) return u;
        access(u);
        int ret = access(v);
        return nodes[u].parent ? ret : 0;
    }

    T getPath(int u, int v) {
        reroot(u);
        access(v);
        return nodes[v].path[1];
    }

    void set(int u, T val) {
        access(u);
        nodes[u].self = val;
        pushUp(u);
    }

    T get(int u) {
        return nodes[u].self;
    }

    // Get aggregate of subtree(u). v is parent of u. There must exist edge(v, u) (?)
    T getSubtree(int u, int v) {
        reroot(v); access(u);
        return nodes[u].vir + nodes[u].self;
    }

// private:
    void reroot(int x) {
        access(x);
        nodes[x].reverse ^= 1;
        pushDown(x);
    }

    int access(int x) {
        int u = x, v = 0;
        for (; u; v = u, u = nodes[u].parent) {
            splay(u);
            int& ov = nodes[u].child[1];
            nodes[u].vir = nodes[u].vir + nodes[ov].sub;
#ifndef PATH_QUERIES_ONLY
            // T requires subtract for subtree queries
            nodes[u].vir -= nodes[v].sub;
#endif

            ov = v; pushUp(u);
        }
        return splay(x), v;
    }
};
// }}}

// Example for custom type: // https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite {{{
// Since T doesn't support subtract -> comment out line
//   nodes[u].vir -= nodes[v].sub
/**
struct T {
    modular a, b;

    T() : a(1), b(0) {}
    T(modular _a, modular _b) : a(_a), b(_b) {}

    // return f(g())
    T operator + (const T& g) const {
        return T {
            a * g.a,
            a * g.b + b,
        };
    }

    T operator += (const T& g) {
        b = a * g.b + b;
        a = a * g.a;
        return *this;
    }
};
*/
// }}}

/* End Link cut tree */

vu solve1(ull N, vuuu initial, vuuu added) {
  ull M = initial.size(), Q = added.size();

  vuuu c_initial(M);
  fore(i, 0, M) {
    auto [a, b, c] = initial[i];
    c_initial[i] = {c, a, b};
  }

  sort(all(c_initial));

  LinkCut lct((int)(N + M + Q));
  fore(i, 0, N) {
    lct.set(i, {-1, -1});
  }

  ull total_cost = 0;
  fore(i, 0, M) {
    auto [c, a, b] = c_initial[i];
    if (!lct.is_connected(a + 1, b + 1)) {
      lct.link(a + 1, N + i + 1);
      lct.link(N + i + 1, b + 1);
      lct.set(N + i + 1, {(ll)c, (ll)i});
      total_cost += c;
    }
  }

  vu ans(Q);
  fore(i, 0, Q) {
    auto [a, b, c] = added[i];
    auto [c_max, j] = lct.getPath(a + 1, b + 1);
    if (c_max > c) {
      ull aj, bj;
      if (j < M) {
        aj = get<1>(c_initial[j]);
        bj = get<2>(c_initial[j]);
      } else {
        aj = get<0>(added[j - M]);
        bj = get<1>(added[j - M]);
      }
      lct.cut(aj + 1, N + j + 1);
      lct.cut(N + j + 1, bj + 1);
      lct.link(a + 1, N + M + i + 1);
      lct.link(N + M + i + 1, b + 1);
      lct.set(N + M + i + 1, {(ll)c, (ll)(M + i)});
      total_cost += c - c_max;
    }
    ans[i] = total_cost;
  }

  return ans;
}

/*
struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

ull msp(ull N, const vuuu& edges) {
  ull M = edges.size();
  vuuu c_edges(M);
  fore(i, 0, M) {
    auto [a, b, c] = edges[i];
    c_edges[i] = {c, a, b};
  }
  sort(all(c_edges));

  UF uf(N);

  ull ans = 0;
  fore(i, 0, M) {
    auto [c, a, b] = c_edges[i];
    if (uf.join(a, b)) {
      ans += c;
    }
  }

  return ans;
}

vu force(ull N, vuuu initial, vuuu added) {
  ull M = initial.size(), Q = added.size();

  vu ans(Q);

  fore(i, 0, Q) {
    auto [a, b, c] = added[i];
    initial.push_back({a, b, c});
    ans[i] = msp(N, initial);
  }

  return ans;
} */



int main() {
  FIN;

  ull T;
  cin >> T;
  while (T--) {
    ull N, M, Q;
    cin >> N >> M >> Q;
    vuuu initial(M), added(Q);
    for (auto& [a, b, c] : initial) {
      cin >> a >> b >> c;
      a--, b--;
    }
    for (auto& [a, b, c] : added) {
      cin >> a >> b >> c;
      a--, b--;
    }

    auto x = solve1(N, initial, added);
    for (ull y : x) {
      cout << y << '\n';
    }
  }

/*   ull N = 2, M = 1, Q = 2;
  fore(i, 0, 1000) {
    vuuu initial(M), added(Q);
    fore(i, 0, N - 1) {
      ull c = rand() % 8 + 1;
      initial[i] = {i, i + 1, c};
    }
    fore(i, N - 1, M) {
      ull a = rand() % N, b = rand() % N;
      ull c = rand() % 8 + 1;
      initial[i] = {a, b, c};
    }

    fore(i, 0, Q) {
      ull a = rand() % N, b = rand() % N;
      ull c = rand() % 8 + 1;
      added[i] = {a, b, c};
    }

    cout << N << ' ' << M << ' ' << Q << '\n';
    for (auto& [a, b, c] : initial) {
      cout << a + 1 << ' ' << b + 1 << ' ' << c << '\n';
    }
    for (auto& [a, b, c] : added) {
      cout << a + 1 << ' ' << b + 1 << ' ' << c << '\n';
    }
    cout << endl;

    vu ans = solve1(N, initial, added);
    vu ansf = force(N, initial, added);

    if (ans != ansf) {
      cout << "WA\n";
      cout << "ans: ";
      for (ull y : ans) {
        cout << y << ' ';
      }
      cout << '\n';
      cout << "ansf: ";
      for (ull y : ansf) {
        cout << y << ' ';
      }
      cout << endl;
      return EXIT_FAILURE;
    }
  } */

  return 0;
}
