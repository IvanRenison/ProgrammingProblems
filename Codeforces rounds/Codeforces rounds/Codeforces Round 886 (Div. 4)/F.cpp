// https://codeforces.com/contest/1850/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#define MAXN ull(2 * 1e5)

vector<ull> primes;
ull n_primes = 0;
vector<bool> prime(MAXN, true);
void sieve(void) {
  prime[0] = false, prime[1] = false;
  for (ull i = 4; i < MAXN; i += 2) {
    prime[i] = false;
  }
  primes.push_back(2);

  for (ull i = 3; i * i < MAXN; i += 2) {
    if (prime[i]) {
      primes.push_back(i);
      for (ull j = i * i; j < MAXN; j += i) {
        prime[j] = false;
      }
    }
  }

  n_primes = primes.size();
}

ull solve1(vector<ull> as) {
  ull n = as.size();

  vector<ull> counts(n + 1);

  for (ull a : as) {
    if (a <= n) {
      counts[a]++;
    }
  }

  vector<ull> divs(n + 1);

  fore(i, 1, n + 1) {
    ull c = counts[i];
    if (c > 0) {
      for (ull j = i; j <= n; j += i) {
        divs[j] += c;
      }
    }
  }

  ull ans = 0;
  fore(i, 1, n + 1) {
    ans = max(ans, divs[i]);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  sieve();

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vector<ull> as(n);
    fore(j, 0, n) {
      cin >> as[j];
    }

    auto ans = solve1(as);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
