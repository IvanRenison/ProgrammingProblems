// https://codeforces.com/gym/106682/problem/N
#include <bits/stdc++.h>
using namespace std;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define mset(a, v) memset((a), (v), sizeof(a))
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef unsigned long long ull;
typedef pair<ull, ull> uu;
typedef vector<ull> vu;

/** Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. Update mod.
 * Use commented code in invert if mod is not prime.
 */
const ll mod = 998244353; // change to something else
struct Mod {
  ll x;
  Mod(ll xx) : x(xx) {}
  Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
  Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
  Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
  Mod operator/(Mod b) { return *this * invert(b); }
  Mod invert(Mod a) {
    return a ^ (mod - 2);
    // ll x, y, g = euclid(a.x, mod, x, y);
    // assert(g == 1); return Mod((x + mod) % mod);
  }
  Mod operator^(ll e) {
    Mod ans(1);
    for (Mod b = *this; e; b = b * b, e >>= 1)
      if (e & 1) ans = ans * b;
    return ans;
  }
};

Mod fact(ull N) {
  Mod ans = 1;
  fore(i, 2, N + 1) {
    ans = ans * Mod(i);
  }
  return ans;
}

Mod comb(ull n, ull m) {
  return fact(n) / (fact(m) * fact(n - m));
}

Mod solve(ull N, ull K, ull A) {
  if (N <= 2 && K == 0) {
    return Mod(A) ^ N;
  }
  if (N <= 2 || K > N - 2) {
    return 0;
  }

  Mod p = Mod(A - 1) ^ ll(N - 2 - K);
  return Mod(A) * Mod(A) * comb(N - 2, K) * p;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

  ull N, K, A;
  cin >> N >> K >> A;

  auto ans = solve(N, K, A);
  cout << ans.x << '\n';

}

