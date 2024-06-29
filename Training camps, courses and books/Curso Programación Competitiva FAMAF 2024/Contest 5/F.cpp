// https://codeforces.com/group/gmV7IkT2pN/contest/528245/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;

const ull mod = 998244353;

/** Author: chilli, Ramchandra Apte, Noam527, Simon Lindholm
 * Date: 2019-04-24
 * License: CC0
 * Source: https://github.com/RamchandraApte/OmniTemplate/blob/master/src/number_theory/modulo.hpp
 * Description: Calculate a\cdot b\bmod c$ (or a^b \bmod c$) for  \le a, b \le c \le 7.2\cdot 10^{18}$.
 * Time: O(1) for \texttt{modmul}, O(\log b) for \texttt{modpow}
 * Status: stress-tested, proven correct
 * Details:
 * This runs ~2x faster than the naive (__int128_t)a * b % M.
 * A proof of correctness is in doc/modmul-proof.tex. An earlier version of the proof,
 * from when the code used a * b / (long double)M, is in doc/modmul-proof.md.
 * The proof assumes that long doubles are implemented as x87 80-bit floats; if they
 * are 64-bit, as on e.g. MSVC, the implementation is only valid for
 *  \le a, b \le c < 2^{52} \approx 4.5 \cdot 10^{15}$.
 */
typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
  ll ret = a * b - M * ull(1.L / M * a * b);
  return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
  ull ans = 1;
  for (; e; b = modmul(b, b, mod), e /= 2)
    if (e & 1) ans = modmul(ans, b, mod);
  return ans;
}

/** Author: chilli, c1729, Simon Lindholm
 * Date: 2019-03-28
 * License: CC0
 * Source: Wikipedia, https://miller-rabin.appspot.com/
 * Description: Deterministic Miller-Rabin primality test.
 * Guaranteed to work for numbers up to  \cdot 10^{18}$; for larger numbers, use Python and extend A randomly.
 * Time: 7 times the complexity of a^b \mod c$.
 * Status: Stress-tested
 */
bool isPrime(ull n) {
  if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
  ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
      s = __builtin_ctzll(n-1), d = n >> s;
  for (ull a : A) {   // ^ count trailing zeroes
    ull p = modpow(a%n, d, n), i = s;
    while (p != 1 && p != n - 1 && a % n && i--)
      p = modmul(p, p, n);
    if (p != n-1 && i != s) return 0;
  }
  return 1;
}

/** Author: chilli, SJTU, pajenegod
 * Date: 2020-03-04
 * License: CC0
 * Source: own
 * Description: Pollard-rho randomized factorization algorithm. Returns prime
 * factors of a number, in arbitrary order (e.g. 2299 -> \{11, 19, 11}).
 * Time: O(n^{1/4})$, less for numbers with small factors.
 * Status: stress-tested
 *
 * Details: This implementation uses the improvement described here
 * (https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm#Variants), where
 * one can accumulate gcd calls by some factor (40 chosen here through
 * exhaustive testing). This improves performance by approximately 6-10x
 * depending on the inputs and speed of gcd. Benchmark found here:
 * (https://ideone.com/nGGD9T)
 *
 * GCD can be improved by a factor of 1.75x using Binary GCD
 * (https://lemire.me/blog/2013/12/26/fastest-way-to-compute-the-greatest-common-divisor/).
 * However, with the gcd accumulation the bottleneck moves from the gcd calls
 * to the modmul. As GCD only constitutes ~12% of runtime, speeding it up
 * doesn't matter so much.
 *
 * This code can probably be sped up by using a faster mod mul - potentially
 * montgomery reduction on 128 bit integers.
 * Alternatively, one can use a quadratic sieve for an asymptotic improvement,
 * which starts being faster in practice around 1e13.
 *
 * Brent's cycle finding algorithm was tested, but doesn't reduce modmul calls
 * significantly.
 *
 * Subtle implementation notes:
 * - prd starts off as 2 to handle the case n = 4; it's harmless for other n
 *   since we're guaranteed that n > 2. (Pollard rho has problems with prime
 *   powers in general, but all larger ones happen to work.)
 * - t starts off as 30 to make the first gcd check come earlier, as an
 *   optimization for small numbers.
 * - we vary f between restarts because the cycle finding algorithm does not
 *   find the first element in the cycle but rather one at distance k*|cycle|
 *   from the start, and that can result in continual failures if all cycles
 *   have the same size for all prime factors. E.g. fixing f(x) = x^2 + 1 would
 *   loop infinitely for n = 352523 * 352817, where all cycles have size 821.
 * - we operate on residues in [i, n + i) which modmul is not designed to
 *   handle, but specifically modmul(x, x) still turns out to work for small
 *   enough i. (With reference to the proof in modmul-proof.tex, the argument
 *   for "S is in [-c, 2c)" goes through unchanged, while S < 2^63 now follows
 *   from S < 2c and S = x^2 (mod c) together implying S < c + i^2.)
 */
ull pollard(ull n) {
  ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  auto f = [&](ull x) { return modmul(x, x, n) + i; };
  while (t++ % 40 || __gcd(prd, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
    x = f(x), y = f(f(y));
  }
  return __gcd(prd, n);
}
vector<ull> factor(ull n) {
  if (n == 1) return {};
  if (isPrime(n)) return {n};
  ull x = pollard(n);
  auto l = factor(x), r = factor(n / x);
  l.insert(l.end(), r.begin(), r.end());
  return l;
}

ull solve(const vu& as) {
  map<ull, ull> primes;

  for (ull a : as) {
    vu ps = factor(a);
    for (ull p : ps) {
      primes[p]++;
    }
  }

  ull ans = 1;
  for (auto [p, e] : primes) {
    ans = modmul(ans, e + 1, mod);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;
  vu as(n);
  for (ull& a : as) {
    cin >> a;
  }

  ull ans = solve(as);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
