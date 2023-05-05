//

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

pair<ull, ull> parse1(void) {
  ull n, m;
  cin >> n >> m;
  return {n, m};
}

#define N 1000001
ull smallest_prime_factors[N];

/* For each number until N get the smallest prime that divides it */
void get_smallest_prime_factors() {
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
}

bool solve1(ull n, ull m) {
  if (n == 1 || m == 1) {
    return true;
  }
  if (n <= m) {
    return false;
  }
  if (n % m == 0) {
    return false;
  }

  if (smallest_prime_factors[n] <= m) {
    return false;
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  get_smallest_prime_factors();

  fore(i, 0, t) {
    auto [n, m] = parse1();
    if (solve1(n, m)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
