// https://codeforces.com/contest/1832/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

/*
Hacer b[i][k], y ver que con k's anteriores e i's anteriores se puede calcular el actual

Usando la formula de (n k) = (n-1 k-1) + (n-1 k)

*/

#define MOD 998244353

vector<ull> solve(vector<ull> as, ull k) {
  ull n = as.size();

  vector<ull> bs_k_last(n);
  vector<ull> bs_k_this(n);

  bs_k_last[0] = as[0];
  fore(i, 1, n) {
    bs_k_last[i] = (bs_k_last[i - 1] + as[i]) % MOD;
  }

  bs_k_this[0] = as[0];
  fore(i, 1, n) {
    bs_k_this[i] = (bs_k_last[i - 1] + bs_k_this[i - 1] + as[i]) % MOD;
  }

  fore(j, 2, k + 1) {
    bs_k_last = bs_k_this;
    bs_k_this[0] = 0;
    fore(i, 1, n) {
      bs_k_this[i] = (bs_k_this[i - 1] + bs_k_last[i - 1]) % MOD;
    }
  }

  return bs_k_this;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, a1, x, y, m, k;
  cin >> n >> a1 >> x >> y >> m >> k;

  vector<ull> as(n);
  as[0] = a1;
  fore(i, 1, n) {
    as[i] = (as[i - 1] * x + y) % m;
  }

  vector<ull> bs = solve(as, k);

  ull ans = 0;
  fore(i, 0, n) {
    ull c = ((ull)bs[i]) * (i + 1);
    ans ^= c;
  }

  cout << ans << '\n';

  return EXIT_SUCCESS;
}
