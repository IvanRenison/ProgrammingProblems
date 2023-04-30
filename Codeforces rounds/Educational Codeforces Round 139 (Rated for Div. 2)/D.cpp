// https://codeforces.com/contest/1766/problem/D

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

typedef unsigned int uint;

static inline tuple<uint, uint> parse1(void) {
  uint x, y;
  cin >> x >> y;
  return {x, y};
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

static inline int solve1(uint* smallest_prime_factors, uint x, uint y) {
  vector<uint> factors_x = prime_factors(smallest_prime_factors, abs((int)x - (int)y));

  uint factors_amount = uint(factors_x.size());

  if (factors_amount == 0) {
    return -1;
  } else {
    uint* sum_x = (uint*)(malloc(sizeof(uint) * factors_amount));
    for (uint i = 0; i < factors_amount; i++) {
      uint p = factors_x[i];
      sum_x[i] = (p - x % p) % p;
    }

    // min element in sum_x
    uint min_sum_x = sum_x[0];
    for (uint i = 1; i < factors_amount; i++) {
      if (sum_x[i] < min_sum_x) {
        min_sum_x = sum_x[i];
      }
    }

    return int(min_sum_x);
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  uint* smallest_prime_factors = (uint*)(calloc(10000001, sizeof(uint)));

  for (uint i = 0; i < 10000001; i++) {
    smallest_prime_factors[i] = i;
  }

  for (uint i = 2; i * i < 10000001; i++) {
    if (smallest_prime_factors[i] == i) {
      smallest_prime_factors[i] = i;
      for (uint j = i * i; j < 10000001; j += i) {
        if (smallest_prime_factors[j] == j) {
          smallest_prime_factors[j] = i;
        }
      }
    }
  }

  uint n;
  cin >> n;
  for (uint i = 0; i < n; i++) {
    uint x, y;
    tie(x, y) = parse1();
    cout << solve1(smallest_prime_factors, x, y) << "\n";
  }

  return EXIT_SUCCESS;
}
