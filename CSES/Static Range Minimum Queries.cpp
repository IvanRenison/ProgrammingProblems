// https://cses.fi/problemset/task/1647

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

struct SpT {
#define op min

  ull n;
  vector<vector<ull>> table;

  SpT(vector<ull> xs) {
    n = xs.size();

    ull k = 33 - __builtin_clz(n);

    table = vector<vector<ull>>(k, vector<ull>(n));

    table[0] = xs;

    fore(i, 1, k) {
      fore(j, 0, n) {
        table[i][j] =
            op(table[i - 1][j], table[i - 1][min(n - 1, j + (1 << (i - 1)))]);
      }
    }
  }

  // Query [a, b) range
  ull query(ull a, ull b) {
    assert(a <= b && b <= n);
    ull i = 31 - __builtin_clz(b - a);
    return op(table[i][a], table[i][b - (1 << i)]);
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, q;
  cin >> n >> q;
  vector<ull> xs(n);
  fore(i, 0, n) {
    cin >> xs[i];
  }

  SpT st(xs);

  fore(i, 0, q) {
    ull a, b;
    cin >> a >> b;
    cout << st.query(a - 1, b) << '\n';
  }

  return EXIT_SUCCESS;
}
