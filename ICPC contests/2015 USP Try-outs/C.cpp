// https://codeforces.com/gym/101047/problem/C
#include <bits/stdc++.h>
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; ++i)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

#define M_PI 3.14159265358979323846

/*

x(x(x(xv + u) + u) + u) + u
=
x(x(xxv + xu + u) + u) + u
=
x(xxxv + xxu + xu + u) + u
=
xxxxv + xxxu + xxu + xu + u
=
u(xxxx + xxx + xx + x + 1)


(x^n v) + ∑(i = 1 to (n-1)) (x^i u)
=
(x^n v) + u ∑(i = 1 to (n-1)) x^i
= {v = 0}
(∑(i = 1 to (n-1)) x^i)u
=
((x^n - Id) * (x - Id)^(-1))u

*/

typedef vector<vector<double>> Matrix;
Matrix ones(ull n) {
  Matrix r(n, vector<double>(n));
  fore(i, 0, n) r[i][i] = 1;
  return r;
}
Matrix operator*(const Matrix& a, const Matrix& b) {
  ull n = a.size(), m = b[0].size(), z = a[0].size();
  Matrix r(n, vector<double>(m));
  fore(i, 0, n) fore(j, 0, m) fore(k, 0, z) {
    r[i][j] += a[i][k] * b[k][j];
  }
  return r;
}
Matrix be(Matrix b, ull e) {
  Matrix r = ones(b.size());
  while (e) {
    if (e & 1ull)
      r = r * b;
    b = b * b;
    e /= 2;
  }
  return r;
}

int matInv(vector<vector<double>>& A) {
  int n = A.size();
  vector<int> col(n);
  vector<vector<double>> tmp(n, vector<double>(n));
  fore(i, 0, n) tmp[i][i] = 1, col[i] = i;

  fore(i, 0, n) {
    int r = i, c = i;
    fore(j, i, n) fore(k, i, n) if (fabs(A[j][k]) > fabs(A[r][c])) r = j, c = k;
    if (fabs(A[r][c]) < 1e-12)
      return i;
    A[i].swap(A[r]);
    tmp[i].swap(tmp[r]);
    fore(j, 0, n) swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
    swap(col[i], col[c]);
    double v = A[i][i];
    fore(j, i + 1, n) {
      double f = A[j][i] / v;
      A[j][i] = 0;
      fore(k, i + 1, n) A[j][k] -= f * A[i][k];
      fore(k, 0, n) tmp[j][k] -= f * tmp[i][k];
    }
    fore(j, i + 1, n) A[i][j] /= v;
    fore(j, 0, n) tmp[i][j] /= v;
    A[i][i] = 1;
  }

  /// forget A at this point, just eliminate tmp backward
  for (int i = n - 1; i > 0; --i)
    fore(j, 0, i) {
      double v = A[j][i];
      fore(k, 0, n) tmp[j][k] -= v * tmp[i][k];
    }

  fore(i, 0, n) fore(j, 0, n) A[col[i]][col[j]] = tmp[i][j];
  return n;
}

pair<double, double> solve1(ull n, double α, double l) {
  if (n == 0) {
    return {0.0, 0.0};
  }
  if (α == 0.0) {
    return {l * n, 0.0};
  }
  Matrix M = {{cos(α), sin(α)}, {-sin(α), cos(α)}};

  Matrix Neg_M_id = {{cos(α) - 1, sin(α)}, {-sin(α), cos(α) - 1}};
  matInv(Neg_M_id);

  M = be(M, n);
  M[0][0] -= 1.0, M[1][1] -= 1.0;

  Matrix L = M * Neg_M_id;

  return {L[1][1] * l, L[0][1] * l};
}

int main() {
  FIN;

  cout << setprecision(8);

  ull T;
  cin >> T;
  while (T--) {

    ull n;
    double α, l;
    cin >> α >> l >> n;

    auto [x, y] = solve1(n, α / 360.0 * 2.0 * M_PI, l);
    cout << (abs(x) < 1e-5 ? 0 : x) << " " << (abs(y) < 1e-5 ? 0 : y) << "\n";
  }

  return 0;
}
