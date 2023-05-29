// https://codeforces.com/contest/1581/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#define MAXN (ull(1e5))
#define MOD (ull(1e9 + 7))

ull solutions[MAXN + 1];

void init(void) {
  solutions[1] = 1;
  fore(i, 2, MAXN + 1) {
    solutions[i] = ((solutions[i - 1] * (2 * i - 1)) % MOD * 2 * i) % MOD;
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  init();

  ull t;

  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    cout << solutions[n] << "\n";
  }

  return EXIT_SUCCESS;
}
