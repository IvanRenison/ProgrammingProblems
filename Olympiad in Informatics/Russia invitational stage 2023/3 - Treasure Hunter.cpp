// https://codeforces.com/gym/104441/problem/3

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;


ii solve(ll a, ull r1, ull r2) {
  /*
    ans = {x, y} such than:
      x² + y² = r1²                      (1)
      (a - x)² + y² = r2²                (2)

    From (1):
      y² = r1² - x²                      (3)

    Replacing (3) in (2):
      (a - x)² + r1² - x² = r2²
      a² - 2ax + x² + r1² - x² = r2²
      a² - 2ax + r1² = r2²
      a² + r1² - r2² = 2ax
      x = (a² + r1² - r2²)/(2a)          (4)
  */

  ll a_2 = a * a, r1_2 = r1 * r1, r2_2 = r2 * r2;

  ll x = (a_2 + r1_2 - r2_2) / (2ll * a);
  ll y = -sqrt(r1_2 - (ll)(x * x));

  return {x, y};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull a, r1, r2;
  cin >> a >> r1 >> r2;

  auto [x, y] = solve(a, r1, r2);
  cout << x << '\n' << y << '\n';

  return EXIT_SUCCESS;
}
