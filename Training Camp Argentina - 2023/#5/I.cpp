// https://codeforces.com/group/hzSLIARNBN/contest/466528/problem/I

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef vector<iiii> viiii;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
constexpr double EPS = 1e-12;

typedef optional<pair<double, double>> I;

I intersect(I i, I j) {
  if (!i.has_value() || !j.has_value()) {
    return {};
  }
  auto [i0, i1] = i.value();
  auto [j0, j1] = j.value();

  if (i0 > j0) {
    swap(i0, j0), swap(i1, j1);
  }

  if (j0 + EPS >= i1) {
    return {};
  }

  return {{j0, min(i1, j1)}};
}


I solve1D(ll x0, ll x1, vii mises) {
  assert(x0 <= x1);
  if (x0 == x1) {
    return {};
  }
  I ans = {{0.0, 1e30}};

  for(auto [r, v] : mises) {
    /*
      x(t) = r + v * t

      x(t0) = x0 ⇔ t0 = (x0 - r) / v
      x(t1) = x1 ⇔ t1 = (x1 - r) / v
    */

    if (v == 0) {
      if (r <= x0 || r >= x1) {
        ans = {};
        break;
      } else {
        continue;
      }
    }

    double t0 = (double)(x0 - r) / (double) v;
    double t1 = (double)(x1 - r) / (double) v;

    if (abs(t0 - t1) < EPS) {
      ans = {};
      break;
    }

    if (t0 > t1) {
      swap(t0, t1);
    }

    ans = intersect(ans, {{t0, t1}});
  }

  return ans;
}

optional<double> solve(ii p0, ii p1, viiii mises) {
  ull n = mises.size();

  auto [x0, y0] = p0;
  auto [x1, y1] = p1;

  vii mises_x(n), mises_y(n);
  fore(i, 0, n) {
    auto [rx, ry, vx, vy] = mises[i];
    mises_x[i] = {rx, vx}, mises_y[i] = {ry, vy};
  }

  I ans_x = solve1D(x0, x1, mises_x);
  I ans_y = solve1D(y0, y1, mises_y);

  I ans = intersect(ans_x, ans_y);

  if (!ans.has_value()) {
    return {};
  }

  return ans.value().first;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;
  ii p0, p1;
  cin >> p0.first >> p0.second >> p1.first >> p1.second;
  viiii mises(n);
  for(auto& [rx, ry, vx, vy] : mises) {
    cin >> rx >> ry >> vx >> vy;
  }

  cout << setprecision(10);
  auto ans = solve(p0, p1, mises);
  if (ans.has_value()) {
    cout << ans.value() << '\n';
  } else {
    cout << "-1\n";
  }

  return EXIT_SUCCESS;
}
