// https://atcoder.jp/contests/abc365/tasks/abc365_f

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

ull diff(ull x, ull y) {
  return x < y ? y - x : x - y;
}

struct Interval {
  ull m, M;
  Interval(ull m = 0, ull M = 0) : m(m), M(M) {}

  bool interect(const Interval& other) {
    return m <= other.M && other.m <= M;
  }
  Interval intersection(const Interval& other) {
    assert(interect(other));
    return Interval(max(m, other.m), min(M, other.M));
  }

  ull Idiff(const Interval& other) {
    assert(!interect(other));
    return min(diff(m, other.M), diff(M, other.m));
  }
  bool in(ull x) {
    return m <= x && x <= M;
  }
  ull Idiff(ull x) {
    if (in(x)) return 0;
    return min(diff(m, x), diff(M, x));
  }
  bool operator<(const Interval& other) const {
    return M < other.m;
  }
};

/** Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right.
 * Can be changed by modifying T, f and neut.
 * Time: O(\log N)
 * Status: stress-tested
 */
struct T {
  bool neut;
  Interval inter;
  ull left, right;
  bool direct; // if direct inter is valid else left, right are valid
  ull cost;
};
const T neut = {true, Interval(), 0, 0, false, 0};
T f(T a, T b) {
  if (a.neut) return b;
  if (b.neut) return a;

  T res;
  res.neut = false;
  if (a.direct && b.direct) {
    if (a.inter.interect(b.inter)) {
      res.inter = a.inter.intersection(b.inter);
      res.direct = true;
      res.cost = a.cost + b.cost;
    } else if (a.inter < b.inter) {
      res.left = a.inter.M;
      res.right = b.inter.m;
      res.direct = false;
      res.cost = a.cost + b.cost + b.inter.m - a.inter.M;
    } else {
      assert(b.inter < a.inter);
      res.left = a.inter.m;
      res.right = b.inter.M;
      res.direct = false;
      res.cost = a.cost + b.cost + a.inter.m - b.inter.M;
    }
  } else if (a.direct) {
    res.direct = false;
    if (a.inter.in(b.left)) {
      res.left = b.left;
      res.right = b.right;
      res.cost = a.cost + b.cost;
    } else if (b.left < a.inter.m) {
      res.left = a.inter.m;
      res.right = b.right;
      res.cost = a.cost + b.cost + a.inter.m - b.left;
    } else {
      assert(a.inter.M < b.left);
      res.left = a.inter.M;
      res.right = b.right;
      res.cost = a.cost + b.cost + b.left - a.inter.M;
    }
  } else if (b.direct) {
    res.direct = false;
    if (b.inter.in(a.right)) {
      res.left = a.left;
      res.right = a.right;
      res.cost = a.cost + b.cost;
    } else if (a.right < b.inter.m) {
      res.left = a.left;
      res.right = b.inter.m;
      res.cost = a.cost + b.cost + b.inter.m - a.right;
    } else {
      assert(b.inter.M < a.right);
      res.left = a.left;
      res.right = b.inter.M;
      res.cost = a.cost + b.cost + a.right - b.inter.M;
    }
  } else {
    res.direct = false;
    res.left = a.left;
    res.right = b.right;
    res.cost = a.cost + b.cost + abs((ll)a.right - (ll)b.left);
  }
  res.cost++;

  return res;
} // (any associative fn)
struct Tree {
  vector<T> s; ll n;
  Tree(ll n = 0, T def = neut) : s(2*n, def), n(n) {}
  void upd(ll pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ll b, ll e) { // query [b, e)
    T ra = neut, rb = neut;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

vu solve(const vuu& LUs, const vuuuu& queries) {
  ull N = SZ(LUs), Q = SZ(queries);

  Tree tree(N);
  fore(i, 0, N) {
    auto [L, U] = LUs[i];
    tree.upd(i, {false, Interval(L, U), 0, 0, true, 0});
  }

  vu ans(Q);
  fore(i, 0, Q) {
    auto [sx, sy, tx, ty] = queries[i];
    if (sx > tx) {
      swap(sx, tx);
      swap(sy, ty);
    }
    if (sx != tx) {
      T res = tree.query(sx, tx + 1);
      ans[i] = res.cost;
      if (res.direct) {
        if (res.inter.M < sy && res.inter.M < ty) {
          ans[i] += sy - res.inter.M + ty - res.inter.M;
        } else if (res.inter.m > sy && res.inter.m > ty) {
          ans[i] += res.inter.m - sy + res.inter.m - ty;
        } else {
          ans[i] += diff(sy, ty);
        }
      } else {
        ans[i] += diff(sy, res.left) + diff(ty, res.right);
      }
    } else {
      ans[i] = diff(sy, ty);
    }
  }

  return ans;
}

vuu neights(uu xy) {
  auto [x, y] = xy;
  vuu ans = {{x + 1, y}, {x, y + 1}};
  if (x > 0) ans.push_back({x - 1, y});
  if (y > 0) ans.push_back({x, y - 1});
  return ans;
}

vu force(const vuu& LUs, const vuuuu& queries) {
  ull N = SZ(LUs), Q = SZ(queries);

  set<uu> nodes;

  fore(x, 0, N) {
    auto [L, U] = LUs[x];
    fore(y, L, U + 1) {
      nodes.insert({x, y});
    }
  }

  vu ans(Q);
  fore(i, 0, Q) {
    auto [sx, sy, tx, ty] = queries[i];

    queue<uu> q;
    map<uu, ull> dist;
    q.push({sx, sy});
    dist[{sx, sy}] = 0;
    while (!q.empty()) {
      auto [x, y] = q.front();
      q.pop();
      if (x == tx && y == ty) {
        ans[i] = dist[{x, y}];
        break;
      }
      for (auto [nx, ny] : neights({x, y})) {
        if (nodes.count({nx, ny}) && !dist.count({nx, ny})) {
          dist[{nx, ny}] = dist[{x, y}] + 1;
          q.push({nx, ny});
        }
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N;
  cin >> N;
  vuu LUs(N);
  for (auto& [l, u] : LUs) {
    cin >> l >> u;
    l--, u--;
  }
  ull Q;
  cin >> Q;
  vuuuu queries(Q);
  for (auto& [sx, sy, tx, ty] : queries) {
    cin >> sx >> sy >> tx >> ty;
    sx--, sy--, tx--, ty--;
  }

  auto ans = solve(LUs, queries);
  for (auto x : ans) {
    cout << x << '\n';
  }


  /* fore(_, 0, 1000) {
    ull N = rand() % 10 + 2;
    ull last_L = 0, last_U = 100;
    vuu LUs(N);
    for (auto& [l, u] : LUs) {
      while (true) {
        l = rand() % 10;
        u = l + rand() % 10;
        if (l > last_U || u < last_L) continue;
        break;
      }
      last_L = l, last_U = u;
    }

    set<uu> nodes;
    fore(x, 0, N) {
      auto [L, U] = LUs[x];
      fore(y, L, U + 1) {
        nodes.insert({x, y});
      }
    }

    ull Q = 1;
    vuuuu queries(Q);

    for (auto& [sx, sy, tx, ty] : queries) {
      // Chose two random nodes
      auto it = nodes.begin();
      advance(it, rand() % SZ(nodes));
      tie(sx, sy) = *it;
      it = nodes.begin();
      advance(it, rand() % SZ(nodes));
      tie(tx, ty) = *it;
    }

    vu ans = solve(LUs, queries);
    vu ansf = force(LUs, queries);
    if (ans != ansf) {
      cerr << "FAIL" << endl;
      cerr << N << endl;
      for (auto [l, u] : LUs) {
        cerr << l << ' ' << u << endl;
      }
      cerr << Q << endl;
      for (auto [sx, sy, tx, ty] : queries) {
        cerr << sx << ' ' << sy << ' ' << tx << ' ' << ty << endl;
      }
      cerr << "SOLVE: ";
      for (auto x : ans) {
        cerr << x << ' ';
      }
      cerr << endl;
      cerr << "FORCE: ";
      for (auto x : ansf) {
        cerr << x << ' ';
      }
      cerr << endl;
      return 1;
    }
  } */

}
