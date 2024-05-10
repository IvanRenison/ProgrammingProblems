// https://codeforces.com/gym/103495/problem/D
#include <bits/stdc++.h>
#define fst fist
#define snd second
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll(x.size()))
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

typedef array<array<ll, 2>, 2> Mat;
Mat R90 = {{{0, -1}, {1, 0}}};
Mat R180 = {{{-1, 0}, {0, -1}}};
Mat R270 = {{{0, 1}, {-1, 0}}};
Mat EspHor = {{{-1, 0}, {0, 1}}};
Mat EspVer = {{{1, 0}, {0, -1}}};
Mat Inter = {{{0, 1}, {1, 0}}};

bool noPoints(ii p0, ii p1) {
  ll x = abs(p1.first - p0.first);
  ll y = abs(p1.second - p0.second);

  if (x == 0) {
    return y == 1;
  }
  if (y == 0) {
    return x == 1;
  }

  ll g = gcd(x, y);

  return g == 1;
}

bool angle_le_90(ii p0, ii p1, ii p2) {
  ll x0 = p0.first - p1.first, y0 = p0.second - p1.second;
  ll x2 = p2.first - p1.first, y2 = p2.second - p1.second;

  ll dot = x0 * x2 + y0 * y2;

  return dot > 0;
}

bool check(ll n, ll m, const vii& r) {
  vector<vi> vis(m, vi(n, -1));
  ll k = r.size();

  if (k != n * m) {
    cerr << "bad size\n";
    return false;
  }

  fore(i, 0, k) {
    auto [x, y] = r[i];
    if (vis[x][y] != -1) {
      cerr << "Point " << x << ' ' << y << " visited in " << vis[x][y] << " and in " << i << endl;
      return false;
    }
    if (i > 0) {
      if (!noPoints(r[i-1], r[i])) {
        cerr << "Points in the middle of " << i - 1 << ' ' << i << endl;
        return false;
      }
      if (i + 1 < k) {
        if (!angle_le_90(r[i-1], r[i], r[i+1])) {
          cerr << "Bad angle " << i << endl;
          return false;
        }
      }
    }
  }

  return true;
}



vii star = {{1, -1}, {1, 0}, {2, -2}, {0, -1}, {2, 0}, {1, -2}, {0, 0}, {2, -1}, {0, -2}};

vii gen(ll n) {
  vii r;
  r.reserve(1 + 2 * (n - 1));
  r.pb({0, -1});
  fore(i, 1, n) {
    r.pb({i, 0});
    r.pb({i, -1});
  }
  r.pb({0, 0});
  reverse(ALL(r));
  assert(SZ(r) == 2*n);
  return r;
}

void translate(vii &v, ll dx, ll dy) {
  for (auto &[x, y] : v) {
    x += dx;
    y += dy;
  }
}

void transform(vii &v, Mat m) {
  for (auto &[x, y] : v) {
    ll nx = x * m[0][0] + y * m[0][1];
    ll ny = x * m[1][0] + y * m[1][1];
    x = nx;
    y = ny;
  }
}

vii solveEx(ll n, ll m) {
  assert(n % 2 == 0);
  vii r;
  fore(i, 0, n / 2) {
    vii v = gen(m);
    translate(v, 0, -2 * i);
    if (i % 2 == 1) {
      transform(v, EspHor);
      translate(v, m - 1, 0);
    }
    r.insert(r.end(), ALL(v));
  }
  assert(SZ(r) == n*m);
  return r;
}

vii solve3O(ll m) {
  vii r = star;
  if (m == 3) return r;
  vii v = solveEx(m - 3, 3);
  transform(v, EspHor);
  translate(v, 2, -3);
  r.insert(r.end(), ALL(v));
  return r;
}

vii solveOO(ll n, ll m) {
  assert(n % 2 == 1);
  assert(m % 2 == 1);
  if (m == 3) {
    vii r = solve3O(n);
    return r;
  }
  vii r = solve3O(m);
  transform(r, R90);
  translate(r, 0, -2);
  if (n == 3) {
    return r;
  }

  vii v = solveEx(n - 3, m);
  if (m % 4 == 1) {
    transform(r, EspVer);
    translate(r, 0, -2);
  }

  translate(v, 0, -3);
  r.insert(r.end(), ALL(v));

  assert(9 + (m-3)*3 + (n-3)*m);
  assert(SZ(r) == n*m);
  return r;
}

vii solve(ll n, ll m) {
  if (n == 2) {
    return gen(m);
  }
  if (m == 2) {
    vii r = gen(n);
    transform(r, R90);
    translate(r, 0, -n + 1);
    return r;
  }
  if (n % 2 == 0) return solveEx(n, m);
  if (m % 2 == 0) {
    vii r = solveEx(m, n);
    transform(r, R90);
    translate(r, 0, -(n - 1));
    return r;
  }
  return solveOO(n, m);
}

vii solveFinal(ll n, ll m) {
  vii r = solve(n, m);
  transform(r, EspVer);
  assert(SZ(r) == n * m);
  return r;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

#ifndef TEST
  ll n, m;
  cin >> n >> m;
  vii r = solveFinal(n, m);
  for (auto [x, y] : r) cout << y + 1 << ' ' << x + 1 << '\n';

#else
  fore(n, 2, 100) {
    fore(m, 2, 100) {
      vii r = solveFinal(n, m);
      bool c = check(n, m, r);
      if (!c) {
        cerr << n << ' ' << m << endl;
        ll i = 0;
        for (auto [x, y] : r) {
          cerr << i << ' ' << x << ' ' << y << endl;
          i++;
        }
        return 1;
      }
    }
  }

#endif
}