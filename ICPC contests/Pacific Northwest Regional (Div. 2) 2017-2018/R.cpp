// https://codeforces.com/gym/101652

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef tuple<ull, ull, double> uud;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef vector<uud> vuud;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define M_PI 3.14159265358979323846
constexpr double eps = 1e-6;

double calcEnd(ull X, double v, const vuud& lrvs, double a) {
  double vx = v * cos(a);
  double vy = v * sin(a);

  double rx = 0.0, ry = 0.0;

  for (auto [l, r, v] : lrvs) {
    {
      double dt = ((double)l - rx) / vx;
      ry += dt * vy;
      rx = l;
    }
    {
      double dt = (double)(r - l) / vx;
      ry += dt * (vy + v);
      rx = r;
    }
  }
  {
    double dt = (X - rx) / vx;
    ry += dt * vy;
    rx = X;
  }

  return ry;
}

optional<double> solve(ull X, double v, const vuud& lrvs) {
  double base = calcEnd(X, v, lrvs, 0.0);

  if (abs(base) < eps) {
    return (double)X / v;
  }


  double lower, upper;

  if (base < 0.0) {
    lower = 0.0;
    upper = M_PI / 2.0;

    if (calcEnd(X, v, lrvs, upper) < 0.0) {
      return {};
    }
  } else {
    lower = - M_PI / 2.0;
    upper = 0.0;

    if (calcEnd(X, v, lrvs, lower) > 0.0) {
      return {};
    }
  }

  double a_ans;

  while (true) {
    double m = (lower + upper) / 2.0;
    double end = calcEnd(X, v, lrvs, m);

    if (abs(end) < eps) {
      a_ans = m;
      break;
    }

    if (end < 0.0) {
      lower = m;
    } else {
      upper = m;
    }
  }

  double ans = (double)X / (cos(a_ans) * v);
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, X;
  double v;
  cin >> n >> X >> v;

  vuud lrvs(n);
  for(auto& [l, r, v] : lrvs) {
    cin >> l >> r >> v;
  }

  auto ans = solve(X, v, lrvs);
  if (ans.has_value()) {
    cout << setprecision(3) << fixed;
    cout << *ans << '\n';
  } else {
    cout << "Too hard\n";
  }

  return EXIT_SUCCESS;
}
