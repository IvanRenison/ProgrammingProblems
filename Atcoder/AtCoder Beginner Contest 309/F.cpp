// https://atcoder.jp/contests/abc309/tasks/abc309_f

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

struct Tree {
  typedef ull T;
  static constexpr T unit = ULLONG_MAX;
  T f(T a, T b) {
    return min(a, b);
  } // (any associative fn)
  vector<T> s;
  int n;
  Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) { // query [b, e)
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

// Sort, compress, and return the number of unique elements
array<ull, 3> sortAndCompress(vector<array<ull, 3>>& hwds) {
  ull N = hwds.size();

  array<vector<pair<ull, ull>>, 3> ks = {
      vector<pair<ull, ull>>(N), vector<pair<ull, ull>>(N),
      vector<pair<ull, ull>>(N)};

  fore(i, 0, N) {
    sort(hwds[i].begin(), hwds[i].end(), greater<ull>());

    fore(j, 0, 3) {
      ks[j][i] = {hwds[i][j], i};
    }
  }

  array<ull, 3> ans = {0, 0, 0};
  fore(j, 0, 3) {
    sort(ks[j].begin(), ks[j].end());
    ull this_ans = 0;
    ull last = ks[j][0].first;
    hwds[ks[j][0].second][j] = this_ans;
    fore(i, 1, N) {
      if (ks[j][i].first != last) {
        this_ans++;
        last = ks[j][i].first;
      }
      hwds[ks[j][i].second][j] = this_ans;
    }

    ans[j] = this_ans;
  }

  // Sort increasing by height, decreasing by width
  sort(hwds.begin(), hwds.end(), [](array<ull, 3>& a, array<ull, 3>& b) {
    if (a[0] == b[0]) {
      return a[1] > b[1];
    }
    return a[0] < b[0];
  });

  return ans;
}

bool solve(vector<array<ull, 3>>& hwds) {
  ull N = hwds.size();
  array<ull, 3> dims = sortAndCompress(hwds);
  auto [H, W, D] = dims;

  Tree tree(W + 1);

  fore(i, 0, N) {
    auto [h, w, d] = hwds[i];

    ull min_d = tree.query(0, w);
    if (min_d < d) {
      return true;
    }

    ull old_d = tree.query(w, w + 1);
    if (d < old_d) {
      tree.update(w, d);
    }
  }

  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vector<array<ull, 3>> hwds(N);
  fore(i, 0, N) {
    cin >> hwds[i][0] >> hwds[i][1] >> hwds[i][2];
  }

  if (solve(hwds)) {
    cout << "Yes\n";
  } else {
    cout << "No\n";
  }

  return EXIT_SUCCESS;
}
