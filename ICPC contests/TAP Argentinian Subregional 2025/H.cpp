// https://codeforces.com/gym/106054/problem/H
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, teo = b; i < teo; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef __uint128_t u128;


const ll X_lim = 1000000000000000001;

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
  ll s = __builtin_ctzll(n-1), d = n >> s;
  for (ull a : {2,325,9375,28178,450775,9780504,1795265022}) {
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
  while (t++ % 40 || gcd(prd, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
    x = f(x), y = f(f(y));
  }
  return gcd(prd, n);
}
vector<ull> factor(ull n) {
  if (n == 1) return {};
  if (isPrime(n)) return {n};
  ull x = pollard(n);
  auto l = factor(x), r = factor(n / x);
  l.insert(l.end(), ALL(r));
  return l;
}


/** Author: Pietro Palombini
 * Date: 2024-10-11
 * License: CC0
 * Description: Given the prime factorization of a number,
 * returns all its divisors.
 * Time: O(d), where d$ is the number of divisors.
 * Status: stress-tested
 */
vi divisors(vector<ii>& f) {
  vi res = {1};
  for (auto& [p, k] : f) {
    ll sz = SZ(res);
    fore(i,0,sz) for(ll j=0,x=p;j<k;j++,x*=p) res.pb(res[i]*x);
  }
  return res;
}

optional<pair<ull, ull>> solve(vi Xs) {
  ll N = Xs.size();

  if (N == 0) {
    return {{1, 1}};
  }

  sort(ALL(Xs));

  fore(i, 0, N - 1) {
    assert(Xs[i] != Xs[i + 1]);
  }

  ull M = 1;
  for (ll X : Xs) {
    u128 newM = (u128)X * (u128)M / (u128)gcd(X, M);
    if (newM >= (u128)X_lim) {
      return {};
    } else {
      M = newM;
    }
  }

  if (M == 1) {
    return {};
  }


  vector<ull> ps = factor(M);

  sort(ALL(ps));

  vii pes = {{ps[0], 1}};
  fore(i, 1, ps.size()) {
    ll p = ps[i];
    if (p == pes.back().first) {
      pes.back().second++;
    } else {
      pes.push_back({p, 1});
    }
  }

  if (pes.size() == 1 && Xs.size() > 1 && Xs[1] == pes[0].first) {
    bool all_cons = true;
    fore(i, 0, N - 1) {
      if (Xs[i + 1] / pes[0].first != Xs[i]) {
        all_cons = false;
        break;
      }
    }

    if (all_cons) {
      M = Xs.back() * pes[0].first;
      return {{M, M}};
    }
  }

  vi divs = divisors(pes);

  sort(ALL(divs));

  if (Xs.size() + 1 != divs.size()) {
    return {};
  }

  ll ans = -1;

  fore(i, 0, Xs.size()) {
    ll j = i + (ans != -1);
    if (Xs[i] != divs[j]) {
      if (ans != -1) {
        return {};
      }
      ans = divs[j];
    }
  }

  if (ans == -1) {
    return {{M, M}};
  } else {
    return {{M, ans}};
  }
}


optional<ll> diff_of_one(vi Xs, vi Ys) {
  sort(ALL(Xs));
  sort(ALL(Ys));

  if (Xs.size() + 1 != Ys.size()) {
    return {};
  }

  for (ll Y : Ys) {
    vi Xs_copy = Xs;
    Xs_copy.push_back(Y);
    sort(ALL(Xs_copy));
    if (Xs_copy == Ys) {
      return Y;
    }
  }

  return {};
}

optional<pair<ull, ull>> force(vi Xs) {

  ll ans_X = -1, ans_falt = -1;

  fore(X, 1, 10000) {

    vi divs_X;
    fore(d, 1, X + 1) {
      if (X % d == 0) {
        divs_X.push_back(d);
      }
    }

    auto may = diff_of_one(Xs, divs_X);
    if (may.has_value()) {
      if (ans_X != -1) { // dos respuestas
        return {};
      }

      ans_X = X;
      ans_falt = *may;
    }
  }

  if (ans_X == -1) {
    return {};
  }

  return {{ans_X, ans_falt}};
}



ostream& operator<<(ostream& os, __uint128_t value) {
  if (value >= 10) {
    os << (value / 10);
  }
  os << (char)(value % 10 + '0');
  return os;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#ifndef TEST
  ll N;
  cin >> N;
  vi Xs(N);
  for (ll& X : Xs) {
    cin >> X;
  }

  auto ans = solve(Xs);
  if (!ans.has_value()) {
    cout << "*\n";
  } else {
    cout << ans->first << ' ' << ans->second << '\n';
  }

#else
  fore(_, 0, 10000) {
    ll X = rand() % 100 + 1;

    vi divs;
    fore(d, 1, X + 1) {
      if (X % d == 0) {
        divs.push_back(d);
      }
    }

    ll elim = rand() % divs.size();
    vi Xs;
    fore(i, 0, divs.size()) if (i != elim) {
      Xs.push_back(divs[i]);
    }

    if (Xs.size() == 1 && Xs[0] == 1) {
      continue;
    }

    auto ans = solve(Xs);
    if (!ans.has_value() || ans->second != divs[elim] || ans->first != X) {
      for (ll p : Xs) {
        cout << p << ' ';
      }
      cout << '\n';
      if (!ans.has_value()) {
        cout << "No ans\n" ;
      } else {
        cout << "my ans:\n" << ans->first << ' ' << ans->second << endl;
      }

      cout << "Real ans: \n";
      cout << X << ' ';
      cout << divs[elim] << '\n';
      return 1;
    }

  }

  fore(_, 0, 10000) {
    cout << _ << endl;
    ll N = rand() % 10 + 1;
    vi Xs(N);
    for (ll& X : Xs) {
      X = rand() % 20 + 1;
    }

    sort(ALL(Xs));

    bool rep = false;
    fore(i, 0, N - 1) {
      if (Xs[i] == Xs[i + 1]) {
        rep = true;
        break;
      }
    }

    if (rep) {
      continue;
    }


    auto ans = solve(Xs);
    auto ansf = force(Xs);

    if (ans != ansf) {
      cout << N << '\n';
      for (ll X : Xs) {
        cout << X << ' ';
      }
      cout << '\n';

      cout << "ans:\n";
      if (!ans.has_value()) {
        cout << "*\n";
      } else {
        cout << ans->first << ' ' << ans->second << '\n';
      }

      cout << "ansf:\n";
      if (!ansf.has_value()) {
        cout << "*\n";
      } else {
        cout << ansf->first << ' ' << ansf->second << '\n';
      }

      return 1;
    }
  }

#endif
}
