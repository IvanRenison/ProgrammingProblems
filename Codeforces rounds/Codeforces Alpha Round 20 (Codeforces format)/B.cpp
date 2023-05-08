// https://codeforces.com/contest/20/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fore(i, a, b) for (ll i = a; i < b; i++)

ll sign(ll x) {
  if (x > 0) {
    return 1;
  } else if (x < 0) {
    return -1;
  } else {
    return 0;
  }
}

optional<vector<double>> solve(ll a, ll b, ll c) {
  double a_d = (double)a;
  double b_d = (double)b;
  double c_d = (double)c;

  if (a == 0) {
    if (b == 0) {
      if (c == 0) {
        // 0 = 0
        return {};
      } else {
        // c = 0
        return {{}};
      }
    } else {
      // bx + c = 0
      return {{-c_d / b_d}};
    }
  } else {
    if (b == 0) {
      if (c == 0) {
        // ax² = 0
        return {{0}};
      } else {
        // ax² + c = 0
        if (sign(a) == sign(c)) {
          return {{}};
        } else {
          double ans = sqrt(-c_d / a_d);
          return {{-ans, ans}};
        }
      }
    } else {
      if (c == 0) {
        // ax² + bx = 0
        double ans = -b_d / a_d;
        if (ans > 0) {
          return {{0, ans}};
        } else {
          return {{ans, 0}};
        }
      } else {
        // ax² + bx + c
        ll disc = b * b - 4.0 * a * c;
        if (disc < 0) {
          return {{}};
        }
        double disc_root = sqrt((double)disc);
        double root1 = (-b_d + disc_root) / (2.0 * a_d);
        double root2 = (-b_d - disc_root) / (2.0 * a_d);
        if (disc == 0) {
          return {{root1}};
        }
        return {{min(root1, root2), max(root1, root2)}};
      }
    }
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // Set decimal psession for cout
  cout << fixed << setprecision(6);

  ll a, b, c;
  cin >> a >> b >> c;

  optional<vector<double>> ans = solve(a, b, c);

  if (ans.has_value()) {
    cout << ans.value().size() << "\n";
    for (double x : ans.value()) {
      cout << x << "\n";
    }
  } else {
    cout << "-1\n";
  }

  return EXIT_SUCCESS;
}
