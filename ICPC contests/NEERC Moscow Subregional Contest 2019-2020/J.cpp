// https://codeforces.com/gym/104847/problem/J

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
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()

const ull inf = 1ull << 60;

struct T {
  ull sz;
  ull count;
  ull left_sz, right_sz;
  bool left, right;

  T(bool b) {
    sz = count = left_sz = right_sz = 1;
    left = right = b;
  }
  T() {
    sz = count = left_sz = right_sz = 0;
  }
};

static const T unit = T();

T f(T a, T b) {
  if (a.sz == 0) {
    return b;
  }
  if (b.sz == 0) {
    return a;
  }

  T ans;
  ans.sz = a.sz + b.sz;
  ans.count = a.count + b.count;
  if (a.right == b.left) {
    ans.count += a.right_sz * b.left_sz;
  }

  ans.left_sz = a.left_sz;
  ans.left = a.left;
  if (a.left_sz == a.sz && a.left == b.left) {
    ans.left_sz += b.left_sz;
  }

  ans.right_sz = b.right_sz;
  ans.right = b.right;
  if (b.right_sz == b.sz && b.right == a.right) {
    ans.right_sz += a.right_sz;
  }

  return ans;
}; // (any associative fn)

struct Tree {
  vector<T> s;
  int n;
  Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) const { // query [b, e)
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2)
        ra = f(ra, s[b++]);
      if (e % 2)
        rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

ull solve(const vu& ps) {
  ull n = ps.size() + 1;

  ull total = 0;
  total += n * (n + 1) / 2;

  vector<vu> suns(n);
  fore(i, 1, n) {
    suns[ps[i - 1]].push_back(i);
  }

  vu sub_tree_size(n, 0);

  function<void(ull)> dfs = [&](ull u) {
    for (ull v : suns[u]) {
      dfs(v);
      sub_tree_size[u] += sub_tree_size[v];
    }
    sub_tree_size[u]++;
  };

  dfs(0);

  Tree t(n);

  fore(i, 0, n) {
    t.update(i, T(false));
  }

  function<void(ull, bool)> paint = [&](ull u, bool b) {
    t.update(u, T(b));
    for (ull v : suns[u]) {
      paint(v, b);
    }
  };

  ull ans = 0;

  function<void(ull)> dfs_ = [&](ull u) {
    ans += total - t.query(0, n).count;

    t.update(u, T(true));

    if (sub_tree_size[u] > 1) {
      ull i = 0;
      fore(j, 1, suns[u].size()) {
        if (sub_tree_size[suns[u][j]] > sub_tree_size[suns[u][i]]) {
          i = j;
        }
      }

      fore(j, 0, suns[u].size()) {
        if (i != j) {
          paint(suns[u][j], true);
        }
      }

      dfs_(suns[u][i]);

      fore(j, 0, suns[u].size()) {
        if (i != j) {
          paint(suns[u][j], false);
          dfs_(suns[u][j]);
        }
      }
    }
  };

  dfs_(0);

  return ans + n * (n + 1) / 2;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;
  vu ps(n - 1);
  for (ull& p : ps) {
    cin >> p;
    p--;
  }

  ull ans = solve(ps);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
