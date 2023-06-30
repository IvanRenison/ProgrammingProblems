// https://atcoder.jp/contests/dp/tasks/dp_r

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

constexpr ull mod = 1e9 + 7;

typedef vector<vector<ull>> Matrix;
Matrix ones(ull n) {
  Matrix r(n, vector<ull>(n));
  fore(i, 0, n) r[i][i] = 1;
  return r;
}
Matrix operator*(Matrix& a, Matrix& b) {
  ull n = a.size(), m = b[0].size(), z = a[0].size();
  Matrix r(n, vector<ull>(m));
  fore(i, 0, n) fore(j, 0, m) fore(k, 0, z) r[i][j] += a[i][k] * b[k][j],
      r[i][j] %= mod;
  return r;
}
Matrix be(Matrix b, ull e) {
  Matrix r = ones(b.size());
  while (e) {
    if (e & 1LL)
      r = r * b;
    b = b * b;
    e /= 2;
  }
  return r;
}

ull solve(ull K, vector<vector<ull>> A) {
  ull N = A.size();
  Matrix B = be(A, K);
  ull ans = 0;
  fore(i, 0, N) {
    fore(j, 0, N) {
      ans = (ans + B[i][j]) % mod;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, K;
  cin >> N >> K;
  vector<vector<ull>> A(N, vector<ull>(N));
  fore(i, 0, N) {
    fore(j, 0, N) {
      cin >> A[i][j];
    }
  }

  cout << solve(K, A) << '\n';

  return EXIT_SUCCESS;
}
