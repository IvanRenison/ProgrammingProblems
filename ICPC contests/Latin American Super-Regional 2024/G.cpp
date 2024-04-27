// https://codeforces.com/gym/105053/problem/G

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

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
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

const ull MAXN = 1e5;

/* For each number until N get the smallest prime that divides it */
vu small_primes(MAXN + 1);
void sieve(void) {
  for (ull i = 1; i < MAXN + 1; i++) {
    if (i % 2 == 0) {
      small_primes[i] = 2;
    } else {
      small_primes[i] = i;
    }
  }

  for (ull i = 3; i * i < MAXN + 1; i += 2) {
    if (small_primes[i] == i) {
      for (ull j = i * i; j < MAXN + 1; j += i) {
        if (small_primes[j] == j) {
          small_primes[j] = i;
        }
      }
    }
  }
}

/* small_primes has to have the smallest prime factor of each number until x */
vuu prime_factors(ull x) {
  if (x == 1) {
    return {};
  } else {
    vuu factors = {{small_primes[x], 1}};
    x = ull(x / small_primes[x]);
    while (x != 1) {
      if (small_primes[x] != factors.back().first) {
        factors.push_back({small_primes[x], 0});
      }
      factors.back().second++;
      x = ull(x / small_primes[x]);
    }
    return factors;
  }
}

ull exp(ull x, ull e) {
  ull ans = 1;
  while(e) {
    if (e % 2) {
      ans *= x;
    }
    x *= x;
    e /= 2;
  }
  return ans;
}

vuu lcm_comps(ull z) {
  vuu facts = prime_factors(z);

  ull n = facts.size();

  vuu ans;


  function<void(ull, ull, ull)> rec = [&](ull i, ull x, ull y) {
    if (i >= n) {
      ans.push_back({min(x, y), max(x, y)});
    } else {
      auto [p, e] = facts[i];

      ull pe = exp(p, e);

      ull x_ = x * pe, y_ = y;
      rec(i + 1, x_, y_);
      fore(k, 0, e) {
        y_ *= p;
        rec(i + 1, x_, y_);
      }

      x_ = x, y_ = y * pe;
      rec(i + 1, x_, y_);
      fore(k, 0, e - 1) {
        x_ *= p;
        rec(i + 1, x_, y_);
      }
    }
  };

  rec(0, 1, 1);

  sort(ALL(ans));
  ans.erase(unique(ALL(ans)), ans.end());

  return ans;
}

ld solve(const vu& Ws) {
  ull N = Ws.size();

  ull W_sum = accumulate(ALL(Ws), 0ull);

  vd W_probs(N);
  fore(i, 0, N) {
    W_probs[i] = (ld) Ws[i] / (ld) W_sum;
  }

  vd dp(N, 0.0);

  for (ull i = N - 1; i < N; i--) {
    ull z = i + 1;

    vuu lcms = lcm_comps(z);
    ld self_prob = 0.0;
    for (auto [x, y] : lcms) {
      if (y == z) {
        self_prob += W_probs[x - 1];
      }
    }

    dp[i] = (dp[i] + self_prob) / (1.0 - self_prob);

    for (auto [x, y] : lcms) {
      if (x != z) {
        dp[x - 1] += W_probs[y - 1] * (dp[z - 1] + 1.0);
      }
      if (y != z) {
        dp[y - 1] += W_probs[x - 1] * (dp[z - 1] + 1.0);
      }
    }
  }

  return dp[0];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  sieve();

  ull N;
  cin >> N;

  vu Ws(N);
  for (ull& W : Ws) {
    cin >> W;
  }

  ld ans = solve(Ws);
  cout << fixed << setprecision(10);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
