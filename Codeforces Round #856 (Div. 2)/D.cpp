// https://codeforces.com/contest/1794/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int ulong;

static inline pair<ulong, vector<ulong>> parse(void) {
  ulong n;
  cin >> n;

  vector<ulong> as(2 * n);
  for (ulong i = 0; i < 2 * n; ++i) {
    cin >> as[i];
  }

  return {n, as};
}

#define mod 998244353

static inline bool* primes_until(ulong N) {
  bool* primes = (bool*)(calloc(N, sizeof(bool)));

  memset(primes, true, N);

  primes[0] = false;
  primes[1] = false;

  for (ulong i = 2; i * i < N; i++) {
    if (primes[i]) {
      for (ulong j = i * i; j < N; j += i) {
        primes[j] = false;
      }
    }
  }

  return primes;
}

static inline ulong factorial_mod(ulong x) {
  ulong result = 1;
  for (ulong i = 2; i <= x; ++i) {
    result = (result * i) % mod;
  }
  return result;
}

static inline ulong pow_mod(ulong x, ulong y) {
  ulong res = 1;
  while (y > 0) {
    if (y % 2 == 1) {
      res = (res * x) % mod;
    }
    y = y / 2;
    x = (x * x) % mod;
  }
  return res;
}

static inline ulong inverse_mod(ulong x) {
  return pow_mod(x, mod - 2);
}

static inline ulong div_mod(ulong x, ulong y) {
  return ((x % mod) * (inverse_mod(y % mod))) % mod;
}

static inline ulong prod_mod(vector<ulong> xs) {
  ulong result = 1;
  for (ulong x : xs) {
    result = (result * x) % mod;
  }
  return result;
}

static inline ulong prod_facts_values_mod(map<ulong, ulong> xs) {
  ulong result = 1;
  for (pair<const ulong, ulong> x : xs) {
    result = (result * x.second) % mod;
  }
  return result;
}

ulong as_primes_combinations[4046][2023];

static inline ulong solve(ulong n, vector<ulong> as) {

  bool* primes = primes_until(1000005);

  map<ulong, ulong> as_primes = {};
  map<ulong, ulong> as_non_primes = {};

  for (ulong a : as) {
    if (primes[a]) {
      as_primes[a] += 1;
    } else {
      as_non_primes[a] += 1;
    }
  }

  ulong amount_primes = as_primes.size();
  if (amount_primes < n) {
    return 0;
  }

  ulong factorial_mod_n = factorial_mod(n);

  vector<ulong> as_primes_amounts = {};
  for (pair<const ulong, ulong> x : as_primes) {
    as_primes_amounts.push_back(x.second);
  }
  ulong prod_facts_amounts_non_primes = prod_facts_values_mod(as_non_primes);

  as_primes_combinations[0][0] =
      div_mod(factorial_mod_n, prod_facts_amounts_non_primes);
  for (ulong available_primes = 1; available_primes <= amount_primes;
       ++available_primes) {
    as_primes_combinations[available_primes][0] = div_mod(
        factorial_mod_n,
        prod_facts_amounts_non_primes *
            factorial_mod(as_primes_amounts[available_primes - 1])
    );
  }

  for (ulong needed_primes = 1; needed_primes <= n; needed_primes++) {
    as_primes_combinations[0][needed_primes] = 0;
  }

  for (ulong available_primes = 1; available_primes <= amount_primes;
       ++available_primes) {
    for (ulong needed_primes = 1; needed_primes <= min(n, available_primes);
         ++needed_primes) {
      as_primes_combinations[available_primes][needed_primes] =
          (div_mod(
               as_primes_combinations[available_primes - 1][needed_primes - 1],
               factorial_mod(as_primes_amounts[available_primes - 1] - 1)
           ) +
           div_mod(
               as_primes_combinations[available_primes - 1][needed_primes],
               factorial_mod(as_primes_amounts[available_primes - 1])
           )) %
          mod;
    }
  }

  return as_primes_combinations[amount_primes][n];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  pair<ulong, vector<ulong>> input = parse();
  ulong res = solve(input.first, input.second);
  cout << res << endl;

  return EXIT_SUCCESS;
}
