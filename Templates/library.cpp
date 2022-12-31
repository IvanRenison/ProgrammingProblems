

#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;

static inline uint* get_smallest_prime_factors(uint N) {
  uint* smallest_prime_factors = (uint*)(calloc(N, sizeof(uint)));

  for (uint i = 0; i < N; i++) {
    smallest_prime_factors[i] = i;
  }

  for (uint i = 2; i * i < N; i++) {
    if (smallest_prime_factors[i] == i) {
      smallest_prime_factors[i] = i;
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
