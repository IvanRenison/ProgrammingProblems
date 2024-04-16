// https://codeforces.com/gym/102916/problem/H

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef long long ll;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

ull my_pow(ull x, ull e, ull p) {
  if (e == 0) {
    return 1;
  }
  ull ans = 1;
  for (; e; e /= 2, x = (x * x) % p) {
    if (e & 1) {
      ans = (ans * x) % p;
    }
  }
  return ans;
}

ull invert(ull a, ull p) {
  return my_pow(a, p - 2, p);
}

struct A {
  ull a, c, x, y, z;
  ull x_inv;

  A(ull a, ull c, ull x, ull y, ull z) : a(a), c(c), x(x), y(y), z(z) {
    x_inv = invert(x, z);
  }


  void operator++() {
    a = (x * a + y) % z;
  }
  void operator--() {
    a = ((a + z - y) * x_inv) % z;
  }
};


ull solve(ull n, ull m, ull a0, vuuuu& cxyzs) {
  ull k = cxyzs.size();

  vector<A> As;
  As.reserve(k);
  fore(i, 0, k) {
    auto [c, x, y, z] = cxyzs[i];
    As.push_back(A(i == 0 ? a0 : As[i - 1].a, c, x, y, z));
    fore(_, 0, c) {
      ++As[i];
    }
  }

  ull ans = 0;
  ull j = n - 1;

  for(ull i = k - 1; i < k; i--) {
    auto [c, x, y, z] = cxyzs[i];

    fore(_, 0, c) {
      ull a = As[i].a;

      //cerr << a << ' ';

      if (a < m) {
        m--;
      } else if (j + 1 == m) {
        ans++;
        m--;
      }

      --As[i];
      j--;
    }
  }

  if (a0 < m) {
    m--;
  } else if (m == 1) {
    ans++;
    m--;
  }

  //cerr << '\n';


  return ans;
}

/** Author: Håkan Terelius
 * Date: 2009-08-26
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 * Description: Prime sieve for generating all primes up to a certain limit. isprime$[i]$ is true iff i$ is a prime.
 * Time: lim=100'000'000 $\approx$ 0.8 s. Runs 30\% faster if only odd indices are stored.
 * Status: Tested
 */
const ull MAX_PR = 5'000'000;
bitset<MAX_PR> isprime;
vu eratosthenesSieve(ull lim) {
  isprime.set(); isprime[0] = isprime[1] = 0;
  for (ull i = 4; i < lim; i += 2) isprime[i] = 0;
  for (ull i = 3; i*i < lim; i += 2) if (isprime[i])
    for (ull j = i*i; j < lim; j += i*2) isprime[j] = 0;
  vu pr;
  fore(i,2,lim) if (isprime[i]) pr.push_back(i);
  return pr;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, m;
  cin >> n >> m;
  ull a0, k;
  cin >> a0 >> k;
  vuuuu cxyzs(k);
  for (auto& [c, x, y, z] : cxyzs) {
    cin >> c >> x >> y >> z;
  }

  ull ans = solve(n, m, a0, cxyzs);
  cout << ans << '\n';

  /* vu primes = eratosthenesSieve(MAX_PR);
  ull n_primes = primes.size();

  fore(_, 0, 1000) {
    ull n = rand() % 10 + 1;
    ull m = rand() % n + 1;

    ull a0 = rand() % 10 + 1;
    vuuuu cxyzs;
    ull c_sum = 0;
    while (c_sum < n - 1) {
      ull c = 1;
      c = min(c, n - 1 - c_sum);
      ull x = rand() % 10 + 1, y = rand() % 10;
      ull z = primes[rand() % n_primes];

      cxyzs.push_back({c,x,y,z});
      c_sum += c;
    }

    cerr << n << ' ' << m << '\n' << a0 << ' ' << cxyzs.size() << '\n';
    for (auto [c, x, y, z] : cxyzs) {
      cerr << c << ' ' << x << ' ' << y << ' ' << z << '\n';
    }
    cerr << endl;

    solve(n, m, a0, cxyzs);
  } */

  return EXIT_SUCCESS;
}
