// https://codeforces.com/contest/2026/problem/A

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
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;


optional<ull> sqrt(ull x) {
  if (x <= 1) {
    return x;
  }
  ull l = 0, r = x;
  while (l < r) {
    ull m = l + (r - l) / 2;
    if (m * m == x) {
      return m;
    } else if (m * m < x) {
      l = m;
    } else {
      r = m;
    }
  }
  return {};
}

pair<uuuu,uuuu> solve(ull X, ull Y, ull K) {

  ull L = min(X, Y);

  return {{0, 0, L, L}, {L, 0, 0, L}};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull X, Y, K;
    cin >> X >> Y >> K;

    auto [AB, CD] = solve(X, Y, K);
    auto [Ax, Ay, Bx, By] = AB;
    auto [Cx, Cy, Dx, Dy] = CD;
    cout << Ax << " " << Ay << " " << Bx << " " << By << '\n';
    cout << Cx << " " << Cy << " " << Dx << " " << Dy << '\n';

    assert(Ax <= X && Ay <= Y && Bx <= X && By <= Y);
    assert(Cx <= X && Cy <= Y && Dx <= X && Dy <= Y);
  }

}
