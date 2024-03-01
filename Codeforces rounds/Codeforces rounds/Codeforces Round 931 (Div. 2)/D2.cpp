// https://codeforces.com/contest/1934/problem/D2

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef pair<ull, ull> uu;
typedef long long ll;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
//#define assert(x) while (!(x)) {}

uu play(ull p0, ull p1) {
  cout << p0 << ' ' << p1 << endl;
  ll q0, q1;
  cin >> q0 >> q1;
  assert(q0 >= 0 && q1 >= 0);
  return {q0, q1};
}

void first() {
  cout << "first" <<  endl;
}

uu second() {
  cout << "second" << endl;
  ll p0, p1;
  cin >> p0 >> p1;
  assert(p0 >= 0 && p1 >= 0);
  return {p0, p1};
}

void solve1(ull n) {
  ull c = __builtin_popcountll(n);

  if (c % 2 == 0) {
    first();
  } else {
    auto [p0, p1] = second();

    if (p0 == 0) {
      return;
    }

    ull cp0 = __builtin_popcountll(p0);
    ull cp1 = __builtin_popcountll(p1);

    if (cp0 % 2 == 0) {
      n = p0;
    } else {
      n = p1;
    }
  }

  while (true) {
    ull p0 = bit_floor(n);
    ull p1 = n ^ p0;

    assert(p0 != 0);
    assert(p1 != 0);

    auto [q0, q1] = play(p0, p1);
    if (q0 == 0) {
      return;
    }

    ull cq0 = __builtin_popcountll(q0);
    ull cq1 = __builtin_popcountll(q1);

    if (cq0 % 2 == 0) {
      n = q0;
    } else {
      n = q1;
    }
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;

    solve1(n);
  }

  return EXIT_SUCCESS;
}
