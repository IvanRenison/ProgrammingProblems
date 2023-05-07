#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

/* For each number until N get the smallest prime that divides it */
vector<ull> get_smallest_prime_factors(ull N) {
  vector<ull> smallest_prime_factors(N);

  for (ull i = 0; i < N; i++) {
    smallest_prime_factors[i] = i;
  }

  for (ull i = 2; i * i < N; i++) {
    if (smallest_prime_factors[i] == i) {
      for (ull j = i * i; j < N; j += i) {
        if (smallest_prime_factors[j] == j) {
          smallest_prime_factors[j] = i;
        }
      }
    }
  }

  return smallest_prime_factors;
}

/* smallest prime factor has to have the smallest ptime factor of each number until n */
vector<ull> prime_factors(vector<ull> smallest_prime_factors, ull n) {
  if (n == 1) {
    return {};
  } else {
    vector<ull> factors = {smallest_prime_factors[n]};
    n = ull(n / smallest_prime_factors[n]);
    while (n != 1) {
      if (smallest_prime_factors[n] != factors.back()) {
        factors.push_back(smallest_prime_factors[n]);
      }
      n = ull(n / smallest_prime_factors[n]);
    }
    return factors;
  }
}

#define MOD 5 // Has to be prime for inverse_mod and div_mod

ull factorial_mod(ull x) {
  ull result = 1;
  for (ull i = 2; i <= x; ++i) {
    result = (result * i) % MOD;
  }
  return result;
}

ull pow_mod(ull x, ull y) {
  ull res = 1;
  while (y > 0) {
    if (y % 2 == 1) {
      res = (res * x) % MOD;
    }
    y = y / 2;
    x = (x * x) % MOD;
  }
  return res;
}

// With MOD prime
ull inverse_mod(ull x) {
  return pow_mod(x, MOD - 2);
}

// With MOD prime
ull div_mod(ull x, ull y) {
  return ((x % MOD) * (inverse_mod(y % MOD))) % MOD;
}

ull prod_mod(vector<ull> xs) {
  ull result = 1;
  for (ull x : xs) {
    result = (result * x) % MOD;
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

/* Find the minimum index for witch f is true or or it.size() if none if true */
template <typename T> ull binary_search(function<bool(T)> f, vector<T> it) {
  ull lower = 0;
  ull upper = it.size();
  if (f(it[lower])) {
    return lower;
  }
  if (!f(it[upper - 1])) {
    return upper;
  }
  while (lower + 1 < upper) {
    ull m = (lower + upper) / 2;
    if (f(it[m])) {
      upper = m;
    } else {
      lower = m;
    }
  }

  return upper;
}
/* Find the minimum index for witch f is true or or upper if none if true */
ull binary_search(function<bool(ull)> f, ull lower, ull upper) {
  if (f(lower)) {
    return lower;
  }
  if (!f(upper - 1)) {
    return upper;
  }
  while (lower + 1 < upper) {
    ull m = (lower + upper) / 2;
    if (f(m)) {
      upper = m;
    } else {
      lower = m;
    }
  }

  return upper;
}
