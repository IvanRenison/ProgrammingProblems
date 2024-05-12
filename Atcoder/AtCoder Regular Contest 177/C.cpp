// https://atcoder.jp/contests/arc177/tasks/arc177_c

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

  Matrix(istream& in) {
    in >> n >> m;
    data = vector<T>(n * m);
    fore(i, 0, n) {
      fore(j, 0, m) {
        in >> this[{i, j}];
      }
    }
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


};

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

/* Make dfs from (i, j) and return all the positions visited */
ull dij(Matrix<char>& mat, ull i, ull j, ull i_last, ull j_last) {
  char c = mat[{i, j}];
  Matrix<bool> visited(mat.n, mat.m, false);
  visited.assign(i, j, true);


  rpriority_queue<uuu> s;// = {{i, j}};
  s.push({0, i, j});

  while (!s.empty()) {
    auto [d, ni, nj] = s.top();
    s.pop();

    if (ni == i_last && nj == j_last) {
      return d;
    }

    for (auto [i_, j_] : mat.neighbors(ni, nj)) {
      if (!visited[{i_, j_}]) {
        if (mat[{i_, j_}] == c) {
          visited.assign(i_, j_, true);
          s.push({d, i_, j_});
        } else {
          visited.assign(i_, j_, true);
          s.push({d + 1, i_, j_});
        }
      }
    }
  }

  assert(false);
}

ull solve(const vector<string>& css) {
  ull N = SZ(css);

  Matrix<char> mat(N, N);
  fore(i, 0, N) {
    fore(j, 0, N) {
      mat.assign(i, j, css[i][j]);
    }
  }

  ull ans = 0;
  ans += dij(mat, 0, 0, N - 1, N - 1);
  ans += dij(mat, 0, N - 1, N - 1, 0);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N;
  cin >> N;
  vector<string> Css(N);
  fore(i, 0, N) {
    cin >> Css[i];
  }

  auto ans = solve(Css);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
