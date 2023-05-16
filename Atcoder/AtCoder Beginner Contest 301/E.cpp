// https://atcoder.jp/contests/abc301/tasks/abc301_e
// NOT WORKING
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

/*

Plantear un grafo completo dirigido con cada caramelo mas el inicio y el final
Calcular la distancia de ir de cada caramelo e inicio y final a cada otro (en la matriz original)

Luego el problema consiste en tratar de pasar por la mayor cantidad de caramelos posibles en t pasos
Este problema es np-completo (Traveling salesman problem)

Como c es hasta 20 se puede igual

Haciendo una función que te diga que saliendo desde x y pasando por (x1, x2, x3, ...) cual es el mínimo costo
Y probar esa función con las 2^18 posibilidades de x1, x2, x3, ...

(esa función creo que es cuadratica)
*/

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

  /*   T& operator[](pair<ull, ull> p) {
    auto [i, j] = p;
    return data[j * n + i];
  } */

  T operator[](pair<ull, ull> p) const {
    auto [i, j] = p;
    return data[j * n + i];
  }

  void assign(pair<ull, ull> ij, T val) {
    auto [i, j] = ij;
    data[j * n + i] = val;
  }

  vector<pair<ull, ull>> neighbors(pair<ull, ull> ij) const {
    auto [i, j] = ij;
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

/* Make bfs from (i, j) and return distances to each candy and S and G */
vector<ull>
bfs(const Matrix<char> mat, pair<ull, ull> ij,
    const vector<pair<ull, ull>> candies) {

  vector<ull> ans(candies.size() + 2);

  Matrix<bool> visited(mat.n, mat.m, false);
  visited.assign(ij, true);

  ull level = 0;
  vector<pair<ull, ull>> next_level = {ij};

  while (!next_level.empty()) {
    vector<pair<ull, ull>> this_level = next_level;
    next_level = {};

    for (auto nij : this_level) {
      char n = mat[nij];
      if (n == 'S') {
        ans[0] = level;
      } else if (n == 'G') {
        ans[candies.size() + 1] = level;
      } else if (n != '.' && n != '#') {
        ans[1 + n - 'a'] = level;
      }

      for (auto ij : mat.neighbors(nij)) {
        if (!visited[ij] && mat[ij] != '#') {
          visited.assign(ij, true);

          next_level.push_back(ij);
        }
      }
    }
    level++;
  }

  return ans;
}

/* Distance between candies */
struct Graph {
  ull n;

  // 0 is S, n-1 is G
  vector<vector<ull>> adj;
};

Graph buildGraph(
    Matrix<char> mat, vector<pair<ull, ull>> candies, pair<ull, ull> S,
    pair<ull, ull> G
) {

  ull n = candies.size() + 2;

  vector<vector<ull>> adj(n);

  adj[0] = bfs(mat, S, candies);
  fore(i, 0, candies.size()) {
    adj[i + 1] = bfs(mat, candies[i], candies);
  }
  adj[n - 1] = bfs(mat, G, candies);

  return {n, adj};
}

struct DP {
  Graph g;

  // For each bitmask, the solution
  vector<vector<optional<ull>>> dp;
  ull n;

  DP(Graph g) : g(g), dp(g.n, vector<optional<ull>>(1ULL << g.n)), n(g.n) {}

  // Solve starting from x and passing by bits in one in bits
  ull solveFor(ull bits, ull x) {
    bits &= ~(1ULL << x);

    optional<ull> stored = dp[x][bits];

    if (stored.has_value()) {
      return stored.value();
    }

    if (x == n - 1) {
      if (bits == 0) {
        dp[x][bits] = 0;
        return 0;
      } else {
        dp[x][bits] = 1000000000;
        return 1000000000;
      }
    }

    ull ans = 1000000000;
    fore(i, 0, n) {
      if ((bits & (1ULL << i)) != 0) {
        ans = min(ans, g.adj[x][i] + solveFor(bits, i));
      }
    }

    dp[x][bits] = ans;
    return ans;
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull H, W, T;
  cin >> H >> W >> T;

  Matrix<char> mat(W, H);
  vector<pair<ull, ull>> candies;

  char next_candie_number = 'a';

  pair<ull, ull> S;
  pair<ull, ull> G;

  fore(j, 0, H) {
    fore(i, 0, W) {
      char c;
      cin >> c;
      if (c == 'o') {
        mat.assign({i, j}, next_candie_number);
        next_candie_number++;
        candies.push_back({i, j});
      } else {
        mat.assign({i, j}, c);
      }

      if (c == 'S') {
        S = {i, j};
      } else if (c == 'G') {
        G = {i, j};
      }
    }
  }

  Graph g = buildGraph(mat, candies, S, G);

  DP dp(g);

  ull ans = dp.solveFor((1ULL << g.n) - 1, g.n - 1);

  if (ans <= T) {
    cout << g.n - 2 << '\n';
  }

  vector<ull> posibles(g.n - 2, false);

  fore(x, 0, (1ULL << g.n) - 1) {
    if ((x & 1) != 0) {
      ull x_ans = dp.solveFor(x, g.n - 1);
      if (x_ans <= T) {
        posibles[__builtin_popcount(x) - 2] = true;
      }
    }
  }

  for (ull x = g.n - 3; x < g.n; x--) {
    if (posibles[x]) {
      cout << x << '\n';
      return EXIT_SUCCESS;
    }
  }


  cout << -1 << '\n';
  return EXIT_SUCCESS;
}
