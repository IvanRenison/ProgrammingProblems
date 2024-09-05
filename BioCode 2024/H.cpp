// https://codeforces.com/gym/105123/problem/H

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
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

iii solve(const vii& points) {

  ii XY;

  auto f = [&](ll t) -> bool {
    ll m = -inf, M = inf, m_ = -inf, M_ = inf;

    for (auto [x, y] : points) {
      ll d = y - x, d_ = y + x;
      // y == x + d, y == -x + d_

      m = max(m, d - t);
      M = min(M, d + t);
      m_ = max(m_, d_ - t);
      M_ = min(M_, d_ + t);
    }

    bool val = m <= M && m_ <= M_;

    if (val) {
      if (m == M && m_ == M_ && abs(m) % 2 != abs(m_) % 2) {
        val = false;
      } else {
        ll X, Y;
        if (abs(m) % 2 == abs(m_) % 2) {
          /*
            m == Y - X
            m_ == Y + X

            m == Y - X
            m_ - m == 0 + 2X
          */
          X = (m_ - m) / 2;
          Y = X + m;
        } else if (m != M) {
          m++;
          X = (m_ - m) / 2;
          Y = X + m;
        } else {
          assert(m_ < M_);
          m_++;
          X = (m_ - m) / 2;
          Y = X + m;
        }

        XY = {X, Y};
      }
    }

    return val;
  };

  ull l = 1, r = 4e9 + 5;

  // l  → lower, r → upper
  while (l + 1 < r) {
    ull m = (l + r) / 2;
    bool a = f(m);
    if (a) {
      r = m;
    } else {
      l = m;
    }
  }

  //assert(f(r));

  auto [X, Y] = XY;

  for (auto [x, y] : points) {
    assert(abs(x - X) + abs(y - Y) <= r);
  }

  return {r, X, Y};
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef TEST
  ull n;
  cin >> n;
  vii points(n);
  for (auto& [X, Y] : points) {
    cin >> X >> Y;
    swap(X, Y);
  }

  auto [t, x, y] = solve(points);
  swap(x, y);
  cout << t <<  " " << x << " " << y << '\n';
#else
  fore(_, 0, 10000) {
    ll n = rand() % 5 + 1;
    vii points(n);
    for (auto& [X, Y] : points) {
      X = rand() % 20 - 10;
      Y = rand() % 20 - 10;
    }

    cerr << n << '\n';
    for (auto [X, Y] : points) {
      cerr << X << " " << Y << '\n';
      swap(X, Y);
    }
    cerr << endl;
    solve(points);
  }
#endif
}
