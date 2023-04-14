

#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;

/* For each number until N get the smallest prime that divides it */
static inline uint* get_smallest_prime_factors(uint N) {
  uint* smallest_prime_factors = (uint*)(calloc(N, sizeof(uint)));

  for (uint i = 0; i < N; i++) {
    smallest_prime_factors[i] = i;
  }

  for (uint i = 2; i * i < N; i++) {
    if (smallest_prime_factors[i] == i) {
      for (uint j = i * i; j < N; j += i) {
        if (smallest_prime_factors[j] == j) {
          smallest_prime_factors[j] = i;
        }
      }
    }
  }

  return smallest_prime_factors;
}

static inline vector<uint> prime_factors(uint* smallest_prime_factors, uint n) {
  if (n == 1) {
    return {};
  } else {
    vector<uint> factors = {smallest_prime_factors[n]};
    n = uint(n / smallest_prime_factors[n]);
    while (n != 1) {
      if (smallest_prime_factors[n] != factors.back()) {
        factors.push_back(smallest_prime_factors[n]);
      }
      n = uint(n / smallest_prime_factors[n]);
    }
    return factors;
  }
}

#define mod 5 // Has to be prime for inverse_mod and div_mod

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

class segmentsWeights {
  map<ull, ull> weights;

  void add(ull l, ull r, ull w) {
    if (l > r) {
      return;
    }

    auto l_pos = weights.lower_bound(l);
    auto r_pos = weights.lower_bound(r);

    if ((*l_pos).first != l) {
      l_pos--;
      weights.insert({l, (*l_pos).second});
      l_pos++;
    }

    if ((*r_pos).first != r) {
      r_pos--;
      weights.insert({r, (*r_pos).second});
      r_pos++;
    }

    for (auto it = l_pos; it != r_pos; it++) {
      (*it).second += w;
    }
  }
};
