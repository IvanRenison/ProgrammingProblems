// https://atcoder.jp/contests/abc343/tasks/abc343_e

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef tuple<ull, ull, ull, ull, ull, ull, ull, ull, ull> uuuuuuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

ull diff(ull a, ull b) {
  return a > b ? a - b : b - a;
}

ull inter3(ull a, ull b, ull c) {
  // Intersection of [a, a + 7), [b, b + 7) and [c, c + 7)

  if (diff(a, b) >= 7 || diff(a, c) >= 7 || diff(b, c) >= 7) {
    return 0;
  }

  vu xs = {a, b, c};
  sort(all(xs));

  return 7 - diff(xs[0], xs[2]);
}

// Intersection of cubes of 7x7x7 with corners in C0 and C1
ull volInter(uuu C0, uuu C1) {
  auto [x0, y0, z0] = C0;
  auto [x1, y1, z1] = C1;

  ull ans = 1;

  if (diff(x0, x1) >= 7) {
    return 0;
  }
  if (diff(y0, y1) >= 7) {
    return 0;
  }
  if (diff(z0, z1) >= 7) {
    return 0;
  }

  ans *= 7 - diff(x0, x1);
  ans *= 7 - diff(y0, y1);
  ans *= 7 - diff(z0, z1);

  return ans;
}

ull volInter3(uuu C0, uuu C1, uuu C2) {
  if (volInter(C0, C1) == 0 || volInter(C0, C2) == 0 || volInter(C1, C2) == 0) {
    return 0;
  }

  auto [x0, y0, z0] = C0;
  auto [x1, y1, z1] = C1;
  auto [x2, y2, z2] = C2;

  ull ans = 1;

  ans *= inter3(x0, x1, x2);
  ans *= inter3(y0, y1, y2);
  ans *= inter3(z0, z1, z2);

  return ans;
}

optional<uuuuuuuuu> solve(ull V1, ull V2, ull V3) {
  if (V3 == 0 && V2 == 0) {
    if (V1 != 7 * 7 * 7 * 3) {
      return {};
    }
    return {{0, 0, 0, 8, 8, 8, 16, 16, 16}};
  }

  function<bool(uuu, uuu, uuu)> valid = [&](uuu C0, uuu C1, uuu C2) {
    auto [a0, b0, c0] = C0;
    auto [a1, b1, c1] = C1;
    auto [a2, b2, c2] = C2;

    ull v3 = volInter3({a0, b0, c0}, {a1, b1, c1}, {a2, b2, c2});
    ull v2 =
      volInter({a0, b0, c0}, {a1, b1, c1}) +
      volInter({a0, b0, c0}, {a2, b2, c2}) +
      volInter({a1, b1, c1}, {a2, b2, c2}) -
      3 * v3;

    ull v1 = 7*7*7*3 - 2 * v2 - 3 * v3;

    return v1 == V1 && v2 == V2 && v3 == V3;
  };

  ull a0 = 7, b0 = 7, c0 = 7;

  fore(a1, 0, 16) {
    fore(b1, 0, 16) {
      fore(c1, 0, 16) {
        fore(a2, 0, 16) {
          fore(b2, 0, 16) {
            fore(c2, 0, 16) {
              if (valid({a0, b0, c0}, {a1, b1, c1}, {a2, b2, c2})) {
                return {{a0, b0, c0, a1, b1, c1, a2, b2, c2}};
              }
            }
          }
        }


        {
          ull a2 = 30, b2 = 30, c2 = 30;
          if (valid({a0, b0, c0}, {a1, b1, c1}, {a2, b2, c2})) {
            return {{a0, b0, c0, a1, b1, c1, a2, b2, c2}};
          }
        }
      }
    }
  }

  return {};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull V1, V2, V3;
  cin >> V1 >> V2 >> V3;

  auto ans = solve(V1, V2, V3);

  if (ans.has_value()) {
    auto [a0, b0, c0, a1, b1, c1, a2, b2, c2] = *ans;
    cout << "Yes\n";
    cout << a0 << ' ' << b0 << ' ' << c0 << ' '
      << a1 << ' ' << b1 << ' ' << c1 << ' '
      << a2 << ' ' << b2 << ' ' << c2 << '\n';
  } else {
    cout << "No\n";
  }

  return EXIT_SUCCESS;
}
