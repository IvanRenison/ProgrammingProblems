// https://codeforces.com/contest/2069/problem/B

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

template <typename T>
struct Matrix {
  ull n, m;
  vector<T> data;

  Matrix(ull n, ull m) {
    this->n = n, this->m = m;
    data = vector<T>(n * m);
  }

  Matrix(ull n, ull m, T val) {
    this->n = n, this->m = m;
    data = vector<T>(n * m, val);
  }

  vuu neighbors(ull i, ull j) {
    vuu ans;
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

  T operator[](uu p) const {
    auto [i, j] = p;
    return data[j * n + i];
  }

  void assign(ull i, ull j, T val) {
    data[j * n + i] = val;
  }

/*   T& operator[](uu p) { // Only if T is not bool
    auto [i, j] = p;
    return data[j * n + i];
  } */
};

/* Make dfs from (i, j) and return all the positions visited */
vuu dfs(Matrix<bool> mat, ull i, ull j) {
  Matrix<bool> visited(mat.n, mat.m, false);
  visited.assign(i, j, true);

  vuu ans = {{i, j}};
  vuu s = {{i, j}};

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

ull solve(Matrix<ull>& mat) {
  ull n = mat.n, m = mat.m;

  vu needs(n * m);

  fore(i, 0, n) fore(j, 0, m) {
    needs[mat[{i, j}]] = max(1ull, needs[mat[{i, j}]]);
    for (auto [ni, nj] : mat.neighbors(i, j)) {
      if (mat[{i, j}] == mat[{ni, nj}]) {
        needs[mat[{i, j}]] = 2;
      }
    }
  }

  ull max_needs = *max_element(ALL(needs));
  ull sum_needs = accumulate(ALL(needs), 0ull);

  return sum_needs - max_needs;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m;
    cin >> n >> m;
    Matrix<ull> mat(n, m);
    fore(j, 0, n) {
      fore(k, 0, m) {
        ull x;
        cin >> x;
        x--;
        mat.assign(j, k, x);
      }
    }

    auto ans = solve(mat);
    cout << ans << '\n';
  }

}
