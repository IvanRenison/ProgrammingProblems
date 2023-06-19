#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

#define MAXN 100001

/* For each number until N get the smallest prime that divides it */
vector<ull> smallest_prime_factors(MAXN);
void sieve(void) {
  for (ull i = 0; i < MAXN; i++) {
    smallest_prime_factors[i] = i;
  }

  for (ull i = 2; i * i < MAXN; i++) {
    if (smallest_prime_factors[i] == i) {
      for (ull j = i * i; j < MAXN; j += i) {
        if (smallest_prime_factors[j] == j) {
          smallest_prime_factors[j] = i;
        }
      }
    }
  }
}

/* smallest_prime_factors has to have the smallest prime factor of each number until x */
vector<pair<ull, ull>> prime_factors(ull x) {
  if (x == 1) {
    return {};
  } else {
    vector<pair<ull, ull>> factors = {{smallest_prime_factors[x], 1}};
    x = ull(x / smallest_prime_factors[x]);
    while (x != 1) {
      if (smallest_prime_factors[x] != factors.back().first) {
        factors.push_back({smallest_prime_factors[x], 0});
      }
      factors.back().second++;
      x = ull(x / smallest_prime_factors[x]);
    }
    return factors;
  }
}

#define MOD 5 // Has to be prime for inverse_mod and div_mod

ull add_mod(ull x, ull y) {
  return x + y < MOD ? x + y : x + y - MOD;
}

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
