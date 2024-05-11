// https://codeforces.com/group/hzSLIARNBN/contest/464702/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define M_PI 3.14159265358979323846

double solve(ull n, double R, double r) {
  double α = 2 * M_PI / (double)n;
  double a = sqrt(2.0 * r * r - 2.0 * r * r * cos(α));

  double area = (double)n * (a * r / 2.0 + a * (R - r) / 2.0);
  return area;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, R, r;
  cin >> n >> R >> r;

  auto ans = solve(n, R, r);
  cout << setprecision(9) << ans << '\n';

  return EXIT_SUCCESS;
}
