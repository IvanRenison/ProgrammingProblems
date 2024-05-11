// https://codeforces.com/group/id8eYTCwzg/contest/445210/problem/G

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
#define fore(i, a, b) for (uint i = a; i < b; i++)

#define AMAX uint(1.5 * 1e7)

// Prime and index of the prime
vector<pair<uint, uint>> smallest_prime_factors(AMAX + 1);
vector<uint> primes;
uint n_primes;

/* sieve */
void init() {

  for (uint i = 0; i <= AMAX; i++) {
    smallest_prime_factors[i] = {i, 0};
  }

  uint p;
  for (p = 2; p * p <= AMAX; p++) {
    if (smallest_prime_factors[p].first == p) {
      uint p_i = primes.size();
      smallest_prime_factors[p].second = p_i;
      primes.push_back(p);
      for (uint j = p * p; j <= AMAX; j += p) {
        if (smallest_prime_factors[j].first == j) {
          smallest_prime_factors[j] = {p, p_i};
        }
      }
    }
  }

  if (p % 2 == 0) {
    p++;
  }

  for (; p <= AMAX; p += 2) {
    if (smallest_prime_factors[p].first == p) {
      uint p_i = primes.size();
      smallest_prime_factors[p].second = p_i;
      primes.push_back(p);
    }
  }

  n_primes = primes.size();
}

// Return for each prime the exponent
map<uint, uint> prime_factors(uint n) {
  map<uint, uint> factors;

  while (n != 1) {
    auto [p, p_i] = smallest_prime_factors[n];
    factors[p_i]++;
    n /= p;
  }
  return factors;
}

optional<uint> solve(vector<uint>& as) {
  uint n = as.size();

  uint GCD = as[0];
  fore(i, 1, n) {
    GCD = gcd(GCD, as[i]);
  }

  // Check that there are not all equal
  bool all_equal = true;
  for (uint a : as) {
    if (a != GCD) {
      all_equal = false;
      break;
    }
  }

  if (all_equal) {
    return {};
  }

  map<uint, uint> GCD_primes = prime_factors(GCD);
  vector<uint> amounts(n_primes);

  fore(i, 0, n) {
    map<uint, uint> factorization = prime_factors(as[i]);
    for (auto [p_i, c] : factorization) {
      if (c > GCD_primes[p_i]) {
        amounts[p_i]++;
      }
    }
  }

  uint ans = UINT32_MAX;

  fore(p_i, 0, n_primes) {
    uint this_ans = n - amounts[p_i];
    ans = min(ans, this_ans);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  init();

  uint n;
  cin >> n;

  vector<uint> as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }

  optional<uint> ans = solve(as);

  if (ans.has_value()) {
    cout << ans.value() << '\n';
  } else {
    cout << "-1\n";
  }

  return EXIT_SUCCESS;
}
