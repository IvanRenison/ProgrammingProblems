// https://redprogramacioncompetitiva.com/contests/2023/11

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long double ld;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(a) (a).begin(), (a).end()

ll b, c, h;

ld f(ld x) {
  ld bot = (ld)(b * x) / 2.0;
  ld top = (ld)(c * (h - x)) / 2.0;
  ld tr = (ld)(h * c) + (ld)((b - c) * h) / 2.0;
  ld side = (tr - bot - top) / 2.0;

  return max({top, bot, side}) - min({top, bot, side});
}

ld gss(ld a, ld b, ld (*f)(ld)) {
  ld r = (sqrtl(5) - 1) / 2, eps = 1e-12;
  ld x1 = b - r * (b - a), x2 = a + r * (b - a);
  ld f1 = f(x1), f2 = f(x2);
  while (b - a > eps)
    if (f1 < f2) { //change to > to find maximum
      b = x2;
      x2 = x1;
      f2 = f1;
      x1 = b - r * (b - a);
      f1 = f(x1);
    } else {
      a = x1;
      x1 = x2;
      f1 = f2;
      x2 = a + r * (b - a);
      f2 = f(x2);
    }
  return a;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  cin >> b >> c >> h;

  ld ans = gss(0.0, (ld)h, f);

  cout << setprecision(9) << fixed << f(ans) << "\n";

  return EXIT_SUCCESS;
}
