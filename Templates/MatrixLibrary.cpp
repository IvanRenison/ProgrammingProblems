#include <bits/stdc++.h>

using namespace std;

typedef long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

template <typename T> struct Matrix {
  ull n, m;

  vector<T> data;

  Matrix(ull n, ull m) {
    this->n = n;
    this->m = m;
    data = vector<T>(n * m);
  }

  Matrix(ull n, ull m, T val) {
    this->n = n;
    this->m = m;
    data = vector<T>(n * m, val);
  }

  Matrix() {
    cin >> n >> m;
    data = vector<T>(n * m);
    fore(i, 0, n) {
      fore(j, 0, m) {
        cin >> this[{i, j}];
      }
    }
  }

  T &operator[](pair<ull, ull> p) {
    auto [i, j] = p;
    return data[j*n + i];
  }

  T operator[](pair<ull, ull> p) const {
    auto [i, j] = p;
    return data[j * n + i];
  }

/*   void assign(ull i, ull j, T val) {
    data[j * n + i] = val;
  } */

  vector<pair<ull, ull>> neighbors(ull i, ull j) {
    vector<pair<ull, ull>> ans;
    if (i > 0) {
      ans.push_back({i - 1, j});
    }
    if (i < n - 1) {
      ans.push_back({i + 1, j});
    }
    if (j > 0) {
      ans.push_back({i, j - 1});
    }
    if (j < m - 1) {
      ans.push_back({i, j + 1});
    }
    return ans;
  }
};

/* Make dfs from (i, j) and return all the positions visited */
vector<pair<ull, ull>> dfs(Matrix<bool> mat, ull i, ull j) {
  Matrix<bool> visited(mat.n, mat.m, false);
  visited.assign(i, j, true);

  vector<pair<ull, ull>> ans = {{i, j}};
  vector<pair<ull, ull>> s = {{i, j}};

  while (!s.empty()) {
    auto [ni, nj] = s.back();
    s.pop_back();

    for (auto [i, j] : mat.neighbors(ni, nj)) {
      if (!visited[{i, j}] && mat[{i, j}]) {
        visited.assign(i, j, true);
        ans.push_back({i, j});
        s.push_back({i, j});
      }
    }
  }

  return ans;
}
