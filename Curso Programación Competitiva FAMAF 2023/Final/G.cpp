// https://codeforces.com/group/id8eYTCwzg/contest/447739/problem/G

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

struct Matrix {
  ull n, m;

  vector<char> data;

  Matrix(ull n, ull m) {
    this->n = n;
    this->m = m;
    data = vector<char>(n * m);
  }

  Matrix(ull n, ull m, char val) {
    this->n = n;
    this->m = m;
    data = vector<char>(n * m, val);
  }

  Matrix() {
    cin >> n >> m;
    data = vector<char>(n * m);
    fore(i, 0, n) {
      fore(j, 0, m) {
        cin >> (*this)[{i, j}];
      }
    }
  }

  char& operator[](pair<ull, ull> p) {
    auto [i, j] = p;
    assert(i < n && j < m);
    return data[j * n + i];
  }

  char operator[](pair<ull, ull> p) const {
    auto [i, j] = p;
    assert(i < n && j < m);
    return data[j * n + i];
  }

  /*   void assign(ull i, ull j, char val) {
    data[j * n + i] = val;
  } */

  vector<pair<ull, ull>> neighbors(pair<ull, ull> p) const {
    auto [i, j] = p;
    assert(i < n && j < m);
    vector<pair<ull, ull>> ans;
    if (i > 0 && (*this)[{i - 1, j}] == '.') {
      ans.push_back({i - 1, j});
    }
    if (i < n - 1 && (*this)[{i + 1, j}] == '.') {
      ans.push_back({i + 1, j});
    }
    if (j > 0 && (*this)[{i, j - 1}] == '.') {
      ans.push_back({i, j - 1});
    }
    if (j < m - 1 && (*this)[{i, j + 1}] == '.') {
      ans.push_back({i, j + 1});
    }
    return ans;
  }
};

void solve(Matrix& mat, ull k) {
  if (k == 0) {
    return;
  }
  ull n = mat.n, m = mat.m;
  ull p_count = 0;
  fore(j, 0, m) {
    fore(i, 0, n) {
      if (mat[{i, j}] == '.') {
        p_count++;
      }
    }
  }

  ull c_count = 0;

  fore(j, 0, m) {
    fore(i, 0, n) {
      if (mat[{i, j}] == '.') {
        vector<pair<ull, ull>> s = {{i, j}};
        while (!s.empty()) {
          auto p = s.back();
          s.pop_back();

          if (mat[p] == '.') {
            mat[p] = 'c';
            c_count++;
            if (c_count + k == p_count) {
              goto end;
            }

            for (auto q : mat.neighbors(p)) {
              s.push_back(q);
            }
          }
        }
      }
    }
  }

end:
  fore(j, 0, m) {
    fore(i, 0, n) {
      char c = mat[{i, j}];
      if (c == '.') {
        mat[{i, j}] = 'X';
      } else if (c == 'c') {
        mat[{i, j}] = '.';
      }
    }
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, m, k;
  cin >> n >> m >> k;
  Matrix mat(m, n);
  fore(j, 0, n) {
    fore(i, 0, m) {
      cin >> mat[{i, j}];
    }
  }

  solve(mat, k);

  ull count = 0;

  fore(j, 0, n) {
    fore(i, 0, m) {
      cout << mat[{i, j}];
      char c = mat[{i, j}];
      if (c == 'X') {
        count++;
      } else {
        assert(c == '.' || c == '#');
      }
    }
    cout << '\n';
  }
  assert(count == k);

  return EXIT_SUCCESS;
}
