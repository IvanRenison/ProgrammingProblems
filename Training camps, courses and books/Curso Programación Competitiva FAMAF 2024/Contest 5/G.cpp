// https://codeforces.com/group/gmV7IkT2pN/contest/528245/problem/G

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;
typedef __uint128_t u128;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

ull force(ull c, ull d, ull x) {
  ull ans = 0;

  fore(a, 1, 1e3) {
    fore(b, 1, 1e3) {
      ull g = gcd(a, b);
      ull l = a * b / g;

      if (c * l - d * g == x) {
        ans++;
      }
    }
  }

  return ans;
}

const ull primes_lim = 2e7;
vu primes(primes_lim + 1);
vu primes_counter(primes_lim + 1);

void init() {
  iota(primes.begin(), primes.end(), 0);
  fore(i, 2, primes_lim + 1) {
    if (primes[i] == i) {
      for (ull j = i * i; j <= primes_lim; j += i) {
        primes[j] = i;
      }
    }
  }

  fore(i, 2, primes_lim + 1) {
    ull p = primes[i];
    primes_counter[i] = primes_counter[i / p] + ((i / p) % p != 0);
  }
}



vuu factorize(ull x) {
  vuu fact;

  while (x > 1) {
    ull p = primes[x];
    ull e = 0;

    while (x % p == 0) {
      x /= p;
      e++;
    }

    fact.push_back({p, e});
  }

  return fact;
}

vu divisors(ull x) {
  vuu fact = factorize(x);

  vu divs;

  function<void(ull, ull)> rec = [&](ull i, ull acc) {
    if (i == 0) {
      divs.push_back(acc);
      return;
    }

    auto [p, e] = fact[i - 1];
    ull x = 1;
    fore(k, 0, e + 1) {
      rec(i - 1, acc * x);
      x *= p;
    }
  };

  rec(fact.size(), 1);

  return divs;
}

ull solve(ull c, ull d, ull x) {
  vu divs = divisors(x);

  vuu vals;

  for (ull g : divs) {
    if ((x + d * g) % c == 0) {
      ull l = (x + d * g) / c;
      if (g <= l && l % g == 0) {
        vals.push_back({g, l});
      }
    }
  }

  sort(vals.begin(), vals.end());

  ull ans = 0;

  fore(i, 0, vals.size()) {
    if (i == 0 || vals[i] != vals[i - 1]) {
      auto [g, l] = vals[i];
      ull this_ans = 1ull << primes_counter[l/g];

      ans += this_ans;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

#ifndef TEST
  ull t;
  cin >> t;

  while (t--) {
    ull c, d, x;
    cin >> c >> d >> x;

    ull ans = solve(c, d, x);
    cout << ans << '\n';
  }
#else
  fore(_, 0, 100) {
    ull c = rand() % 10 + 1;
    ull d = rand() % 10 + 1;
    ull x = rand() % 10 + 1;

    ull ans = solve(c, d, x);
    ull brute = force(c, d, x);

    if (ans != brute) {
      cout << c << ' ' << d << ' ' << x << '\n';
      cout << "ans: " << ans << '\n';
      cout << "brute: " << brute << '\n';
      return EXIT_FAILURE;
    }
  }
#endif

  return EXIT_SUCCESS;
}


/*

c * lcm - d * gcd = x
c * (lcm / gcd) - d = x / gcd
c * (lcm / gcd) = x / gcd + d
lcm = (x / gcd + d) * gcd / c


c * lcm - d * gcd = x
lcm = (x + d * gcd) / c


*/
