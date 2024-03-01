// https://codeforces.com/contest/1934/problem/C

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
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

ull diff(ull a, ull b) {
  return a > b ? a - b : b - a;
}

ull manhattanDist(ull x0, ull y0, ull x1, ull y1) {
  return diff(x0, x1) + diff(y0, y1);
}

//ull _i_x0, _i_y0, _i_x1, _i_y1;

ull query(ull x, ull y) {
  cout << "? " << x + 1 << " " << y + 1 << endl;
  ull ans;
  cin >> ans;

  //ull ans = min(manhattanDist(_i_x0, _i_y0, x, y), manhattanDist(_i_x1, _i_y1, x, y));

  return ans;
}


uu solve1(ull n, ull m) {
  ull q0 = query(0, 0);

  if (q0 == 0) {
    return {0, 0};
  }

  ull r_x = q0 < m ? 0 : q0 - m + 1;
  ull r_y = q0 < m ? q0 : m - 1;

  ull l_x = q0 < n ? q0 : n - 1;
  ull l_y = q0 < n ? 0 : q0 - n + 1;

  ull qr = query(r_x, r_y);
  ull ql = query(l_x, l_y);

  if (qr == 0) {
    return {r_x, r_y};
  }
  if (ql == 0) {
    return {l_x, l_y};
  }

  ull dlr = manhattanDist(r_x, r_y, l_x, l_y);

  assert(qr < dlr);
  assert(ql < dlr);

  if (qr == dlr - ql) {
    assert(qr % 2 == 0);
    ull x = r_x + qr / 2;
    ull y = r_y - qr / 2;
    assert(manhattanDist(x, y, l_x, l_y) == ql);
    assert(manhattanDist(x, y, r_x, r_y) == qr);
    assert(x + y == q0);
    return {x, y};
  }

  if (qr % 2 == 1) {
    assert(ql % 2 == 0);
    ull x = l_x - ql/2;
    ull y = l_y + ql/2;
    assert(manhattanDist(x, y, l_x, l_y) == ql);
    assert(x + y == q0);
    return {x, y};
  }

  if (ql % 2 == 1) {
    assert(qr % 2 == 0);
    ull x = r_x + qr / 2;
    ull y = r_y - qr / 2;
    assert(manhattanDist(x, y, r_x, r_y) == qr);
    assert(x + y == q0);
    return {x, y};
  }

  ull m_x = r_x + qr / 2;
  ull m_y = r_y - qr / 2;

  ull qm = query(m_x, m_y);

  if (qm == 0) {
    return {m_x, m_y};
  }

  ull x = l_x - ql/2;
  ull y = l_y + ql/2;

  return {x, y};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m;
    cin >> n >> m;

    auto ans = solve1(n, m);
    cout << "! " << ans.first + 1 << " " << ans.second + 1 << endl;
  }

/*   fore(_, 0, 1000) {
    ull n = 4, m = 3;
    _i_x0 = rand() % n;
    _i_y0 = rand() % m;
    _i_x1 = rand() % n;
    _i_y1 = rand() % m;
    if (_i_x0 == _i_x1 && _i_y0 == _i_y1) {
      continue;
    }

    auto [x, y] = solve1(n, m);

    if (!(x == _i_x0 && y == _i_y0) && !(x == _i_x1 && y == _i_y1)) {
      cerr << "ERROR: " << endl;
      cerr << "n = " << n << " m = " << m << endl;
      cerr << "x0 = " << _i_x0 << " y0 = " << _i_y0 << endl;
      cerr << "x1 = " << _i_x1 << " y1 = " << _i_y1 << endl;
      cerr << "ans = " << x << " " << y << endl;
      return EXIT_FAILURE;
    }
  } */

  return EXIT_SUCCESS;
}
