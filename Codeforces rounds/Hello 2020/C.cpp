// https://codeforces.com/contest/1284/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#define MAXN 250000

static ull mod;
struct Mod {
  ull x;
  Mod(ull xx) : x(xx) {}
  Mod() : x(0) {}
  Mod operator+(Mod b) {
    return Mod((x + b.x) % mod);
  }
  Mod operator-(Mod b) {
    return Mod((x + mod - b.x) % mod);
  }
  Mod operator*(Mod b) {
    return Mod((x * b.x) % mod);
  }
};

Mod fact[MAXN + 1];

ull solve(Mod n, ull p) {
  mod = p;
  fact[0] = 1;
  fore(i, 1, n.x + 1) {
    fact[i] = (fact[i - 1] * i);
  }

  Mod ans = 0;

  fore(i, 0, n.x) {
    ans = ans + (n - i)                 // Pleases from where to start
                    * (n - i)           // Number from where to start
                    * fact[i + 1]       // Internal permutations
                    * fact[n.x - i - 1] // External permutation
        ;
  }

  return ans.x;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, p;

  cin >> n >> p;

  cout << solve(Mod(n), p) << '\n';

  return EXIT_SUCCESS;
}
